//===--------- ur_level_zero_platform.cpp - Level Zero Adapter --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===-----------------------------------------------------------------===//

#include "ur_level_zero_platform.hpp"
#include "ur_level_zero.hpp"

UR_APIEXPORT ur_result_t UR_APICALL urInit(
    ur_device_init_flags_t
        DeviceFlags ///< [in] device initialization flags.
                    ///< must be 0 (default) or a combination of
                    ///< ::ur_device_init_flag_t.
) {
  std::ignore = DeviceFlags;

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urTearDown(
    void *Params ///< [in] pointer to tear down parameters
) {
  std::ignore = Params;
  // reclaim pi_platform objects here since we don't have piPlatformRelease.
  for (ur_platform_handle_t Platform : *PiPlatformsCache) {
    delete Platform;
  }
  delete PiPlatformsCache;
  delete PiPlatformsCacheMutex;

  bool LeakFound = false;
  // Print the balance of various create/destroy native calls.
  // The idea is to verify if the number of create(+) and destroy(-) calls are
  // matched.
  if (ZeCallCount && (UrL0Debug & UR_L0_DEBUG_CALL_COUNT) != 0) {
    // clang-format off
    //
    // The format of this table is such that each row accounts for a
    // specific type of objects, and all elements in the raw except the last
    // one are allocating objects of that type, while the last element is known
    // to deallocate objects of that type.
    //
    std::vector<std::vector<const char *>> CreateDestroySet = {
      {"zeContextCreate",      "zeContextDestroy"},
      {"zeCommandQueueCreate", "zeCommandQueueDestroy"},
      {"zeModuleCreate",       "zeModuleDestroy"},
      {"zeKernelCreate",       "zeKernelDestroy"},
      {"zeEventPoolCreate",    "zeEventPoolDestroy"},
      {"zeCommandListCreateImmediate", "zeCommandListCreate", "zeCommandListDestroy"},
      {"zeEventCreate",        "zeEventDestroy"},
      {"zeFenceCreate",        "zeFenceDestroy"},
      {"zeImageCreate",        "zeImageDestroy"},
      {"zeSamplerCreate",      "zeSamplerDestroy"},
      {"zeMemAllocDevice", "zeMemAllocHost", "zeMemAllocShared", "zeMemFree"},
    };

    // A sample output aimed below is this:
    // ------------------------------------------------------------------------
    //                zeContextCreate = 1     \--->        zeContextDestroy = 1
    //           zeCommandQueueCreate = 1     \--->   zeCommandQueueDestroy = 1
    //                 zeModuleCreate = 1     \--->         zeModuleDestroy = 1
    //                 zeKernelCreate = 1     \--->         zeKernelDestroy = 1
    //              zeEventPoolCreate = 1     \--->      zeEventPoolDestroy = 1
    //   zeCommandListCreateImmediate = 1     |
    //            zeCommandListCreate = 1     \--->    zeCommandListDestroy = 1  ---> LEAK = 1
    //                  zeEventCreate = 2     \--->          zeEventDestroy = 2
    //                  zeFenceCreate = 1     \--->          zeFenceDestroy = 1
    //                  zeImageCreate = 0     \--->          zeImageDestroy = 0
    //                zeSamplerCreate = 0     \--->        zeSamplerDestroy = 0
    //               zeMemAllocDevice = 0     |
    //                 zeMemAllocHost = 1     |
    //               zeMemAllocShared = 0     \--->               zeMemFree = 1
    //
    // clang-format on

    fprintf(stderr, "ZE_DEBUG=%d: check balance of create/destroy calls\n",
            UR_L0_DEBUG_CALL_COUNT);
    fprintf(stderr,
            "----------------------------------------------------------\n");
    for (const auto &Row : CreateDestroySet) {
      int diff = 0;
      for (auto I = Row.begin(); I != Row.end();) {
        const char *ZeName = *I;
        const auto &ZeCount = (*ZeCallCount)[*I];

        bool First = (I == Row.begin());
        bool Last = (++I == Row.end());

        if (Last) {
          fprintf(stderr, " \\--->");
          diff -= ZeCount;
        } else {
          diff += ZeCount;
          if (!First) {
            fprintf(stderr, " | \n");
          }
        }

        fprintf(stderr, "%30s = %-5d", ZeName, ZeCount);
      }

      if (diff) {
        LeakFound = true;
        fprintf(stderr, " ---> LEAK = %d", diff);
      }
      fprintf(stderr, "\n");
    }

    ZeCallCount->clear();
    delete ZeCallCount;
    ZeCallCount = nullptr;
  }
  if (LeakFound)
    return UR_RESULT_ERROR_INVALID_MEM_OBJECT;

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGet(
    uint32_t NumEntries, ///< [in] the number of platforms to be added to
                         ///< phPlatforms. If phPlatforms is not NULL, then
                         ///< NumEntries should be greater than zero, otherwise
                         ///< ::UR_RESULT_ERROR_INVALID_SIZE, will be returned.
    ur_platform_handle_t
        *Platforms, ///< [out][optional][range(0, NumEntries)] array of handle
                    ///< of platforms. If NumEntries is less than the number of
                    ///< platforms available, then
                    ///< ::urPlatformGet shall only retrieve that number of
                    ///< platforms.
    uint32_t *NumPlatforms ///< [out][optional] returns the total number of
                           ///< platforms available.
) {
  static std::once_flag ZeCallCountInitialized;
  try {
    std::call_once(ZeCallCountInitialized, []() {
      if (UrL0Debug & UR_L0_DEBUG_CALL_COUNT) {
        ZeCallCount = new std::map<const char *, int>;
      }
    });
  } catch (const std::bad_alloc &) {
    return UR_RESULT_ERROR_OUT_OF_HOST_MEMORY;
  } catch (...) {
    return UR_RESULT_ERROR_UNKNOWN;
  }

  // Setting these environment variables before running zeInit will enable the
  // validation layer in the Level Zero loader.
  if (UrL0Debug & UR_L0_DEBUG_VALIDATION) {
    setEnvVar("ZE_ENABLE_VALIDATION_LAYER", "1");
    setEnvVar("ZE_ENABLE_PARAMETER_VALIDATION", "1");
  }

  // Enable SYSMAN support for obtaining the PCI address
  // and maximum memory bandwidth.
  if (getenv("SYCL_ENABLE_PCI") != nullptr) {
    setEnvVar("ZES_ENABLE_SYSMAN", "1");
  }

  // TODO: We can still safely recover if something goes wrong during the init.
  // Implement handling segfault using sigaction.

  // We must only initialize the driver once, even if piPlatformsGet() is called
  // multiple times.  Declaring the return value as "static" ensures it's only
  // called once.
  static ze_result_t ZeResult = ZE_CALL_NOCHECK(zeInit, (0));

  // Absorb the ZE_RESULT_ERROR_UNINITIALIZED and just return 0 Platforms.
  if (ZeResult == ZE_RESULT_ERROR_UNINITIALIZED) {
    UR_ASSERT(NumEntries != 0, UR_RESULT_ERROR_INVALID_VALUE);
    if (NumPlatforms)
      *NumPlatforms = 0;
    return UR_RESULT_SUCCESS;
  }

  if (ZeResult != ZE_RESULT_SUCCESS) {
    urPrint("zeInit: Level Zero initialization failure\n");
    return ze2urResult(ZeResult);
  }

  // Cache pi_platforms for reuse in the future
  // It solves two problems;
  // 1. sycl::platform equality issue; we always return the same pi_platform.
  // 2. performance; we can save time by immediately return from cache.
  //

  const std::lock_guard<SpinLock> Lock{*PiPlatformsCacheMutex};
  if (!PiPlatformCachePopulated) {
    try {
      // Level Zero does not have concept of Platforms, but Level Zero driver is
      // the closest match.
      uint32_t ZeDriverCount = 0;
      ZE2UR_CALL(zeDriverGet, (&ZeDriverCount, nullptr));
      if (ZeDriverCount == 0) {
        PiPlatformCachePopulated = true;
      } else {
        std::vector<ze_driver_handle_t> ZeDrivers;
        ZeDrivers.resize(ZeDriverCount);

        ZE2UR_CALL(zeDriverGet, (&ZeDriverCount, ZeDrivers.data()));
        for (uint32_t I = 0; I < ZeDriverCount; ++I) {
          auto Platform = new ur_platform_handle_t_(ZeDrivers[I]);
          // Save a copy in the cache for future uses.
          PiPlatformsCache->push_back(Platform);

          UR_CALL(Platform->initialize());
        }
        PiPlatformCachePopulated = true;
      }
    } catch (const std::bad_alloc &) {
      return UR_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    } catch (...) {
      return UR_RESULT_ERROR_UNKNOWN;
    }
  }

  // Populate returned platforms from the cache.
  if (Platforms) {
    UR_ASSERT(NumEntries <= PiPlatformsCache->size(),
              UR_RESULT_ERROR_INVALID_PLATFORM);
    std::copy_n(PiPlatformsCache->begin(), NumEntries, Platforms);
  }

  if (NumPlatforms) {
    if (*NumPlatforms == 0)
      *NumPlatforms = PiPlatformsCache->size();
    else
      *NumPlatforms = std::min(PiPlatformsCache->size(), (size_t)NumEntries);
  }

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetInfo(
    ur_platform_handle_t Platform, ///< [in] handle of the platform
    ur_platform_info_t ParamName,  ///< [in] type of the info to retrieve
    size_t Size,      ///< [in] the number of bytes pointed to by pPlatformInfo.
    void *ParamValue, ///< [out][optional] array of bytes holding the info.
                      ///< If Size is not equal to or greater to the real number
                      ///< of bytes needed to return the info then the
                      ///< ::UR_RESULT_ERROR_INVALID_SIZE error is returned and
                      ///< pPlatformInfo is not used.
    size_t *SizeRet   ///< [out][optional] pointer to the actual number of bytes
                      ///< being queried by pPlatformInfo.
) {
  UrReturnHelper ReturnValue(Size, ParamValue, SizeRet);

  switch (ParamName) {
  case UR_PLATFORM_INFO_NAME:
    // TODO: Query Level Zero driver when relevant info is added there.
    return ReturnValue("Intel(R) oneAPI Unified Runtime over Level-Zero");
  case UR_PLATFORM_INFO_VENDOR_NAME:
    // TODO: Query Level Zero driver when relevant info is added there.
    return ReturnValue("Intel(R) Corporation");
  case UR_PLATFORM_INFO_EXTENSIONS:
    // Convention adopted from OpenCL:
    //     "Returns a space-separated list of extension names (the extension
    // names themselves do not contain any spaces) supported by the platform.
    // Extensions defined here must be supported by all devices associated
    // with this platform."
    //
    // TODO: Check the common extensions supported by all connected devices and
    // return them. For now, hardcoding some extensions we know are supported by
    // all Level Zero devices.
    return ReturnValue(ZE_SUPPORTED_EXTENSIONS);
  case UR_PLATFORM_INFO_PROFILE:
    // TODO: figure out what this means and how is this used
    return ReturnValue("FULL_PROFILE");
  case UR_PLATFORM_INFO_VERSION:
    // TODO: this should query to zeDriverGetDriverVersion
    // but we don't yet have the driver handle here.
    //
    // From OpenCL 2.1: "This version string has the following format:
    // OpenCL<space><major_version.minor_version><space><platform-specific
    // information>. Follow the same notation here.
    //
    return ReturnValue(Platform->ZeDriverApiVersion.c_str());
  case UR_PLATFORM_INFO_BACKEND:
    return ReturnValue(UR_PLATFORM_BACKEND_LEVEL_ZERO);
  default:
    urPrint("urPlatformGetInfo: unrecognized ParamName\n");
    return UR_RESULT_ERROR_INVALID_VALUE;
  }

  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetApiVersion(
    ur_platform_handle_t Driver, ///< [in] handle of the platform
    ur_api_version_t *Version    ///< [out] api version
) {
  std::ignore = Driver;
  *Version = UR_API_VERSION_0_6;
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetNativeHandle(
    ur_platform_handle_t Platform,     ///< [in] handle of the platform.
    ur_native_handle_t *NativePlatform ///< [out] a pointer to the native
                                       ///< handle of the platform.
) {
  // Extract the Level Zero driver handle from the given PI platform
  *NativePlatform = reinterpret_cast<ur_native_handle_t>(Platform->ZeDriver);
  return UR_RESULT_SUCCESS;
}

UR_APIEXPORT ur_result_t UR_APICALL urPlatformCreateWithNativeHandle(
    ur_native_handle_t
        NativePlatform, ///< [in] the native handle of the platform.
    const ur_platform_native_properties_t
        *Properties, ///< [in][optional] pointer to native platform properties
                     ///< struct.
    ur_platform_handle_t *Platform ///< [out] pointer to the handle of the
                                   ///< platform object created.
) {
  std::ignore = Properties;
  auto ZeDriver = ur_cast<ze_driver_handle_t>(NativePlatform);

  uint32_t NumPlatforms = 0;
  UR_CALL(urPlatformGet(0, nullptr, &NumPlatforms));

  if (NumPlatforms) {
    std::vector<ur_platform_handle_t> Platforms(NumPlatforms);
    UR_CALL(urPlatformGet(NumPlatforms, Platforms.data(), nullptr));

    // The SYCL spec requires that the set of platforms must remain fixed for
    // the duration of the application's execution. We assume that we found all
    // of the Level Zero drivers when we initialized the platform cache, so the
    // "NativeHandle" must already be in the cache. If it is not, this must not
    // be a valid Level Zero driver.
    for (const ur_platform_handle_t &CachedPlatform : Platforms) {
      if (CachedPlatform->ZeDriver == ZeDriver) {
        *Platform = CachedPlatform;
        return UR_RESULT_SUCCESS;
      }
    }
  }

  return UR_RESULT_ERROR_INVALID_VALUE;
}

UR_APIEXPORT ur_result_t UR_APICALL urGetLastResult(
    ur_platform_handle_t Platform, ///< [in] handle of the platform instance
    const char **Message ///< [out] pointer to a string containing adapter
                         ///< specific result in string representation.
) {
  std::ignore = Platform;
  std::ignore = Message;
  urPrint("[UR][L0] %s function not implemented!\n", __FUNCTION__);
  return UR_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

ur_result_t ur_platform_handle_t_::initialize() {
  // Cache driver properties
  ZeStruct<ze_driver_properties_t> ZeDriverProperties;
  ZE2UR_CALL(zeDriverGetProperties, (ZeDriver, &ZeDriverProperties));
  uint32_t DriverVersion = ZeDriverProperties.driverVersion;
  // Intel Level-Zero GPU driver stores version as:
  // | 31 - 24 | 23 - 16 | 15 - 0 |
  // |  Major  |  Minor  | Build  |
  auto VersionMajor = std::to_string((DriverVersion & 0xFF000000) >> 24);
  auto VersionMinor = std::to_string((DriverVersion & 0x00FF0000) >> 16);
  auto VersionBuild = std::to_string(DriverVersion & 0x0000FFFF);
  ZeDriverVersion = VersionMajor + "." + VersionMinor + "." + VersionBuild;

  ZE2UR_CALL(zeDriverGetApiVersion, (ZeDriver, &ZeApiVersion));
  ZeDriverApiVersion = std::to_string(ZE_MAJOR_VERSION(ZeApiVersion)) + "." +
                       std::to_string(ZE_MINOR_VERSION(ZeApiVersion));

  // Cache driver extension properties
  uint32_t Count = 0;
  ZE2UR_CALL(zeDriverGetExtensionProperties, (ZeDriver, &Count, nullptr));

  std::vector<ze_driver_extension_properties_t> ZeExtensions(Count);

  ZE2UR_CALL(zeDriverGetExtensionProperties,
             (ZeDriver, &Count, ZeExtensions.data()));

  for (auto &extension : ZeExtensions) {
    // Check if global offset extension is available
    if (strncmp(extension.name, ZE_GLOBAL_OFFSET_EXP_NAME,
                strlen(ZE_GLOBAL_OFFSET_EXP_NAME) + 1) == 0) {
      if (extension.version == ZE_GLOBAL_OFFSET_EXP_VERSION_1_0) {
        ZeDriverGlobalOffsetExtensionFound = true;
      }
    }
    // Check if extension is available for "static linking" (compiling multiple
    // SPIR-V modules together into one Level Zero module).
    if (strncmp(extension.name, ZE_MODULE_PROGRAM_EXP_NAME,
                strlen(ZE_MODULE_PROGRAM_EXP_NAME) + 1) == 0) {
      if (extension.version == ZE_MODULE_PROGRAM_EXP_VERSION_1_0) {
        ZeDriverModuleProgramExtensionFound = true;
      }
    }
    zeDriverExtensionMap[extension.name] = extension.version;
  }

  // Check if import user ptr into USM feature has been requested.
  // If yes, then set up L0 API pointers if the platform supports it.
  ZeUSMImport.setZeUSMImport(this);

  return UR_RESULT_SUCCESS;
}

// Get the cached PI device created for the L0 device handle.
// Return NULL if no such PI device found.
ur_device_handle_t
ur_platform_handle_t_::getDeviceFromNativeHandle(ze_device_handle_t ZeDevice) {

  ur_result_t Res = populateDeviceCacheIfNeeded();
  if (Res != UR_RESULT_SUCCESS) {
    return nullptr;
  }

  // TODO: our sub-sub-device representation is currently [Level-Zero device
  // handle + Level-Zero compute group/engine index], so there is now no 1:1
  // mapping from L0 device handle to PI device assumed in this function. Until
  // Level-Zero adds unique ze_device_handle_t for sub-sub-devices, here we
  // filter out PI sub-sub-devices.
  std::shared_lock<ur_shared_mutex> Lock(PiDevicesCacheMutex);
  auto it = std::find_if(PiDevicesCache.begin(), PiDevicesCache.end(),
                         [&](std::unique_ptr<ur_device_handle_t_> &D) {
                           return D.get()->ZeDevice == ZeDevice &&
                                  (D.get()->RootDevice == nullptr ||
                                   D.get()->RootDevice->RootDevice == nullptr);
                         });
  if (it != PiDevicesCache.end()) {
    return (*it).get();
  }
  return nullptr;
}

// Check the device cache and load it if necessary.
ur_result_t ur_platform_handle_t_::populateDeviceCacheIfNeeded() {
  std::scoped_lock<ur_shared_mutex> Lock(PiDevicesCacheMutex);

  if (DeviceCachePopulated) {
    return UR_RESULT_SUCCESS;
  }

  uint32_t ZeDeviceCount = 0;
  ZE2UR_CALL(zeDeviceGet, (ZeDriver, &ZeDeviceCount, nullptr));

  try {
    std::vector<ze_device_handle_t> ZeDevices(ZeDeviceCount);
    ZE2UR_CALL(zeDeviceGet, (ZeDriver, &ZeDeviceCount, ZeDevices.data()));

    for (uint32_t I = 0; I < ZeDeviceCount; ++I) {
      std::unique_ptr<ur_device_handle_t_> Device(
          new ur_device_handle_t_(ZeDevices[I], (ur_platform_handle_t)this));
      UR_CALL(Device->initialize());

      // Additionally we need to cache all sub-devices too, such that they
      // are readily visible to the piextDeviceCreateWithNativeHandle.
      //
      uint32_t SubDevicesCount = 0;
      ZE2UR_CALL(zeDeviceGetSubDevices,
                 (Device->ZeDevice, &SubDevicesCount, nullptr));

      auto ZeSubdevices = new ze_device_handle_t[SubDevicesCount];
      ZE2UR_CALL(zeDeviceGetSubDevices,
                 (Device->ZeDevice, &SubDevicesCount, ZeSubdevices));

      // Wrap the Level Zero sub-devices into PI sub-devices, and add them to
      // cache.
      for (uint32_t I = 0; I < SubDevicesCount; ++I) {
        std::unique_ptr<ur_device_handle_t_> UrSubDevice(
            new ur_device_handle_t_(ZeSubdevices[I], (ur_platform_handle_t)this,
                                    Device.get()));
        auto Result = UrSubDevice->initialize();
        if (Result != UR_RESULT_SUCCESS) {
          delete[] ZeSubdevices;
          return Result;
        }

        // collect all the ordinals for the sub-sub-devices
        std::vector<int> Ordinals;

        uint32_t numQueueGroups = 0;
        ZE2UR_CALL(zeDeviceGetCommandQueueGroupProperties,
                   (UrSubDevice->ZeDevice, &numQueueGroups, nullptr));
        if (numQueueGroups == 0) {
          return UR_RESULT_ERROR_UNKNOWN;
        }
        std::vector<ZeStruct<ze_command_queue_group_properties_t>>
            QueueGroupProperties(numQueueGroups);
        ZE2UR_CALL(zeDeviceGetCommandQueueGroupProperties,
                   (UrSubDevice->ZeDevice, &numQueueGroups,
                    QueueGroupProperties.data()));

        for (uint32_t i = 0; i < numQueueGroups; i++) {
          if (QueueGroupProperties[i].flags &
                  ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE &&
              QueueGroupProperties[i].numQueues > 1) {
            Ordinals.push_back(i);
          }
        }

        // If isn't PVC, then submissions to different CCS can be executed on
        // the same EUs still, so we cannot treat them as sub-sub-devices.
        if (UrSubDevice->isPVC() || ExposeCSliceInAffinityPartitioning) {
          // Create PI sub-sub-devices with the sub-device for all the ordinals.
          // Each {ordinal, index} points to a specific CCS which constructs
          // a sub-sub-device at this point.
          //
          // FIXME: Level Zero creates multiple PiDevices for a single physical
          // device when sub-device is partitioned into sub-sub-devices.
          // Sub-sub-device is technically a command queue and we should not
          // build program for each command queue. PiDevice is probably not the
          // right abstraction for a Level Zero command queue.
          for (uint32_t J = 0; J < Ordinals.size(); ++J) {
            for (uint32_t K = 0;
                 K < QueueGroupProperties[Ordinals[J]].numQueues; ++K) {
              std::unique_ptr<ur_device_handle_t_> PiSubSubDevice(
                  new ur_device_handle_t_(ZeSubdevices[I],
                                          (ur_platform_handle_t)this,
                                          UrSubDevice.get()));
              UR_CALL(PiSubSubDevice->initialize(Ordinals[J], K));

              // save pointers to sub-sub-devices for quick retrieval in the
              // future.
              UrSubDevice->SubDevices.push_back(PiSubSubDevice.get());
              PiDevicesCache.push_back(std::move(PiSubSubDevice));
            }
          }
        }

        // save pointers to sub-devices for quick retrieval in the future.
        Device->SubDevices.push_back(UrSubDevice.get());
        PiDevicesCache.push_back(std::move(UrSubDevice));
      }
      delete[] ZeSubdevices;

      // Save the root device in the cache for future uses.
      PiDevicesCache.push_back(std::move(Device));
    }
  } catch (const std::bad_alloc &) {
    return UR_RESULT_ERROR_OUT_OF_HOST_MEMORY;
  } catch (...) {
    return UR_RESULT_ERROR_UNKNOWN;
  }
  DeviceCachePopulated = true;
  return UR_RESULT_SUCCESS;
}

// Returns plugin specific backend option.
// Current support is only for optimization options.
// Return '-ze-opt-disable' for frontend_option = -O0.
// Return '-ze-opt-level=1' for frontend_option = -O1 or -O2.
// Return '-ze-opt-level=2' for frontend_option = -O3.
UR_APIEXPORT ur_result_t UR_APICALL urPlatformGetBackendOption(
    ur_platform_handle_t Platform, ///< [in] handle of the platform instance.
    const char *FrontendOption, ///< [in] string containing the frontend option.
    const char *
        *PlatformOption ///< [out] returns the correct platform specific
                        ///< compiler option based on the frontend option.
) {
  std::ignore = Platform;
  using namespace std::literals;
  if (FrontendOption == nullptr) {
    return UR_RESULT_SUCCESS;
  }
  if (FrontendOption == ""sv) {
    *PlatformOption = "";
    return UR_RESULT_SUCCESS;
  }
  if (FrontendOption == "-O0"sv) {
    *PlatformOption = "-ze-opt-disable";
    return UR_RESULT_SUCCESS;
  }
  if (FrontendOption == "-O1"sv || FrontendOption == "-O2"sv) {
    *PlatformOption = "-ze-opt-level=1";
    return UR_RESULT_SUCCESS;
  }
  if (FrontendOption == "-O3"sv) {
    *PlatformOption = "-ze-opt-level=2";
    return UR_RESULT_SUCCESS;
  }
  return UR_RESULT_ERROR_INVALID_VALUE;
}
