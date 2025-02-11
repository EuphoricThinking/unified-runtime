
# Summary
(<ins>Emphasized values</ins> are the best results)

<details>
<summary>
Improved 10 (threshold 2.00%)
</summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/size:10000/100000/4096/iterations:200000/threads:4 umfProxy | 567.155 ns | <ins>370.937000</ins> ns | 52.90% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 scalable_pool<os_provider> | 68584.300 ns | <ins>51584.600000</ins> ns | 32.95% | 
| alloc/size:10000/0/4096/iterations:200000/threads:4 umfProxy | 487.258 ns | <ins>366.902000</ins> ns | 32.80% | 
| alloc/size:10000/0/4096/iterations:200000/threads:4 scalable_pool<os_provider> | 914.206 ns | <ins>709.620000</ins> ns | 28.83% | 
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 umfProxy | 3691.010 ns | <ins>3026.150000</ins> ns | 21.97% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 os_provider | 387.368 ns | <ins>344.714000</ins> ns | 12.37% | 
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 scalable_pool<os_provider> | 5559.820 ns | <ins>5196.400000</ins> ns | 6.99% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 umfProxy | 126494.000 ns | <ins>120114.000000</ins> ns | 5.31% | 
| alloc/size:10000/0/4096/iterations:200000/threads:4 glibc | 8003.700 ns | <ins>7704.290000</ins> ns | 3.89% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 jemalloc_pool<os_provider> | 260.303 ns | <ins>251.786000</ins> ns | 3.38% | 

</details>
<details>
<summary>
Regressed 43 (threshold 2.00%)
</summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 jemalloc_pool<os_provider> | <ins>696.923000</ins> ns | 957.531 ns | -27.22% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 jemalloc_pool<os_provider> | <ins>41695.600000</ins> ns | 56658.700 ns | -26.41% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 jemalloc_pool<os_provider> | <ins>112172.000000</ins> ns | 149329.000 ns | -24.88% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:4 proxy_pool<os_provider> | <ins>4297.990000</ins> ns | 5513.340 ns | -22.04% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 jemalloc_pool<os_provider> | <ins>226.071000</ins> ns | 288.532 ns | -21.65% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 glibc | <ins>9561.710000</ins> ns | 12021.200 ns | -20.46% | 
| alloc/size:10000/0/4096/iterations:200000/threads:4 proxy_pool<os_provider> | <ins>3798.550000</ins> ns | 4677.650 ns | -18.79% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 proxy_pool<os_provider> | <ins>487.464000</ins> ns | 594.583 ns | -18.02% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 disjoint_pool<os_provider> | <ins>968.475000</ins> ns | 1169.030 ns | -17.16% | 
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 scalable_pool<os_provider> | <ins>7660.760000</ins> ns | 9240.880 ns | -17.10% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 proxy_pool<os_provider> | <ins>1506480.000000</ins> ns | 1807170.000 ns | -16.64% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 scalable_pool<os_provider> | <ins>426.596000</ins> ns | 504.071 ns | -15.37% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 disjoint_pool<os_provider> | <ins>6014270.000000</ins> ns | 7071940.000 ns | -14.96% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 disjoint_pool<os_provider> | <ins>467168.000000</ins> ns | 544351.000 ns | -14.18% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 jemalloc_pool<os_provider> | <ins>762763.000000</ins> ns | 883286.000 ns | -13.64% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 os_provider | <ins>1473150.000000</ins> ns | 1694820.000 ns | -13.08% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 os_provider | <ins>216043.000000</ins> ns | 246988.000 ns | -12.53% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 glibc | <ins>565627.000000</ins> ns | 636463.000 ns | -11.13% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 scalable_pool<os_provider> | <ins>18719.300000</ins> ns | 21050.100 ns | -11.07% | 
| alloc/size:10000/0/4096/iterations:200000/threads:4 disjoint_pool<os_provider> | <ins>14567.100000</ins> ns | 16335.000 ns | -10.82% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 glibc | <ins>58911.300000</ins> ns | 65803.200 ns | -10.47% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:4 disjoint_pool<os_provider> | <ins>14802.400000</ins> ns | 16395.900 ns | -9.72% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 umfProxy | <ins>1286180.000000</ins> ns | 1423310.000 ns | -9.63% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:4 jemalloc_pool<os_provider> | <ins>3108.130000</ins> ns | 3433.540 ns | -9.48% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 umfProxy | <ins>374.881000</ins> ns | 413.541 ns | -9.35% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 os_provider | <ins>300.868000</ins> ns | 331.153 ns | -9.15% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:4 os_provider | <ins>2863.130000</ins> ns | 3150.700 ns | -9.13% | 
| alloc/size:10000/0/4096/iterations:200000/threads:4 os_provider | <ins>2751.330000</ins> ns | 3011.060 ns | -8.63% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 proxy_pool<os_provider> | <ins>328183.000000</ins> ns | 358209.000 ns | -8.38% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 jemalloc_pool<os_provider> | <ins>461063.000000</ins> ns | 500663.000 ns | -7.91% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:4 glibc | <ins>3656.210000</ins> ns | 3952.830 ns | -7.50% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 umfProxy | <ins>155063.000000</ins> ns | 166857.000 ns | -7.07% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 umfProxy | <ins>220.443000</ins> ns | 235.016 ns | -6.20% | 
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 glibc | <ins>2418.250000</ins> ns | 2567.860 ns | -5.83% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 glibc | <ins>1487.250000</ins> ns | 1564.700 ns | -4.95% | 
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 scalable_pool<os_provider> | <ins>57336.900000</ins> ns | 60273.200 ns | -4.87% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 scalable_pool<os_provider> | <ins>557.696000</ins> ns | 585.886 ns | -4.81% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 disjoint_pool<os_provider> | <ins>1140.120000</ins> ns | 1195.780 ns | -4.65% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:4 scalable_pool<os_provider> | <ins>731.828000</ins> ns | 765.068 ns | -4.34% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 scalable_pool<os_provider> | <ins>136337.000000</ins> ns | 141010.000 ns | -3.31% | 
| alloc/size:10000/0/4096/iterations:200000/threads:1 proxy_pool<os_provider> | <ins>612.585000</ins> ns | 632.468 ns | -3.14% | 
| alloc/size:10000/100000/4096/iterations:200000/threads:1 glibc | <ins>1436.590000</ins> ns | 1471.770 ns | -2.39% | 
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 umfProxy | <ins>1229910.000000</ins> ns | 1258230.000 ns | -2.25% | 

</details>

## Performance change in benchmark groups
<details><summary>UMF</summary>


<details>
<summary> Relative perf in group alloc/size:10000/0/4096/iterations:200000/threads:4 (7): 102.622% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/size:10000/0/4096/iterations:200000/threads:4 umfProxy | 487.258 ns | <ins>366.902000</ins> ns | 32.80%
| alloc/size:10000/0/4096/iterations:200000/threads:4 scalable_pool<os_provider> | 914.206 ns | <ins>709.620000</ins> ns | 28.83%
| alloc/size:10000/0/4096/iterations:200000/threads:4 glibc | 8003.700 ns | <ins>7704.290000</ins> ns | 3.89%
| alloc/size:10000/0/4096/iterations:200000/threads:4 jemalloc_pool<os_provider> | 3280.580 ns | <ins>3219.100000</ins> ns | 1.91%
| alloc/size:10000/0/4096/iterations:200000/threads:4 os_provider | <ins>2751.330000</ins> ns | 3011.060 ns | -8.63%
| alloc/size:10000/0/4096/iterations:200000/threads:4 disjoint_pool<os_provider> | <ins>14567.100000</ins> ns | 16335.000 ns | -10.82%
| alloc/size:10000/0/4096/iterations:200000/threads:4 proxy_pool<os_provider> | <ins>3798.550000</ins> ns | 4677.650 ns | -18.79%

</details>


<details>
<summary> Relative perf in group alloc/size:10000/0/4096/iterations:200000/threads:1 (7): 90.469% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/size:10000/0/4096/iterations:200000/threads:1 proxy_pool<os_provider> | <ins>612.585000</ins> ns | 632.468 ns | -3.14%
| alloc/size:10000/0/4096/iterations:200000/threads:1 disjoint_pool<os_provider> | <ins>1140.120000</ins> ns | 1195.780 ns | -4.65%
| alloc/size:10000/0/4096/iterations:200000/threads:1 glibc | <ins>1487.250000</ins> ns | 1564.700 ns | -4.95%
| alloc/size:10000/0/4096/iterations:200000/threads:1 umfProxy | <ins>220.443000</ins> ns | 235.016 ns | -6.20%
| alloc/size:10000/0/4096/iterations:200000/threads:1 os_provider | <ins>300.868000</ins> ns | 331.153 ns | -9.15%
| alloc/size:10000/0/4096/iterations:200000/threads:1 scalable_pool<os_provider> | <ins>426.596000</ins> ns | 504.071 ns | -15.37%
| alloc/size:10000/0/4096/iterations:200000/threads:1 jemalloc_pool<os_provider> | <ins>226.071000</ins> ns | 288.532 ns | -21.65%

</details>


<details>
<summary> Relative perf in group alloc/size:10000/100000/4096/iterations:200000/threads:4 (7): 96.569% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/size:10000/100000/4096/iterations:200000/threads:4 umfProxy | 567.155 ns | <ins>370.937000</ins> ns | 52.90%
| alloc/size:10000/100000/4096/iterations:200000/threads:4 scalable_pool<os_provider> | <ins>731.828000</ins> ns | 765.068 ns | -4.34%
| alloc/size:10000/100000/4096/iterations:200000/threads:4 glibc | <ins>3656.210000</ins> ns | 3952.830 ns | -7.50%
| alloc/size:10000/100000/4096/iterations:200000/threads:4 os_provider | <ins>2863.130000</ins> ns | 3150.700 ns | -9.13%
| alloc/size:10000/100000/4096/iterations:200000/threads:4 jemalloc_pool<os_provider> | <ins>3108.130000</ins> ns | 3433.540 ns | -9.48%
| alloc/size:10000/100000/4096/iterations:200000/threads:4 disjoint_pool<os_provider> | <ins>14802.400000</ins> ns | 16395.900 ns | -9.72%
| alloc/size:10000/100000/4096/iterations:200000/threads:4 proxy_pool<os_provider> | <ins>4297.990000</ins> ns | 5513.340 ns | -22.04%

</details>


<details>
<summary> Relative perf in group alloc/size:10000/100000/4096/iterations:200000/threads:1 (7): 94.330% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/size:10000/100000/4096/iterations:200000/threads:1 os_provider | 387.368 ns | <ins>344.714000</ins> ns | 12.37%
| alloc/size:10000/100000/4096/iterations:200000/threads:1 jemalloc_pool<os_provider> | 260.303 ns | <ins>251.786000</ins> ns | 3.38%
| alloc/size:10000/100000/4096/iterations:200000/threads:1 glibc | <ins>1436.590000</ins> ns | 1471.770 ns | -2.39%
| alloc/size:10000/100000/4096/iterations:200000/threads:1 scalable_pool<os_provider> | <ins>557.696000</ins> ns | 585.886 ns | -4.81%
| alloc/size:10000/100000/4096/iterations:200000/threads:1 umfProxy | <ins>374.881000</ins> ns | 413.541 ns | -9.35%
| alloc/size:10000/100000/4096/iterations:200000/threads:1 disjoint_pool<os_provider> | <ins>968.475000</ins> ns | 1169.030 ns | -17.16%
| alloc/size:10000/100000/4096/iterations:200000/threads:1 proxy_pool<os_provider> | <ins>487.464000</ins> ns | 594.583 ns | -18.02%

</details>


<details>
<summary> Relative perf in group alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 (4): 104.895% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 umfProxy | 3691.010 ns | <ins>3026.150000</ins> ns | 21.97%
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 scalable_pool<os_provider> | 5559.820 ns | <ins>5196.400000</ins> ns | 6.99%
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 jemalloc_pool<os_provider> | <ins>5739.810000</ins> ns | 5826.580 ns | -1.49%
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 glibc | <ins>2418.250000</ins> ns | 2567.860 ns | -5.83%

</details>


<details>
<summary> Relative perf in group alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 (4): 88.514% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 glibc | 203.066 ns | <ins>200.433000</ins> ns | 1.31%
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 umfProxy | 1414.900 ns | <ins>1409.060000</ins> ns | 0.41%
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 scalable_pool<os_provider> | <ins>7660.760000</ins> ns | 9240.880 ns | -17.10%
| alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 jemalloc_pool<os_provider> | <ins>696.923000</ins> ns | 957.531 ns | -27.22%

</details>


<details>
<summary> Relative perf in group multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 (7): 88.839% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 scalable_pool<os_provider> | <ins>57336.900000</ins> ns | 60273.200 ns | -4.87%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 jemalloc_pool<os_provider> | <ins>461063.000000</ins> ns | 500663.000 ns | -7.91%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 umfProxy | <ins>1286180.000000</ins> ns | 1423310.000 ns | -9.63%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 glibc | <ins>58911.300000</ins> ns | 65803.200 ns | -10.47%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 os_provider | <ins>1473150.000000</ins> ns | 1694820.000 ns | -13.08%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 disjoint_pool<os_provider> | <ins>6014270.000000</ins> ns | 7071940.000 ns | -14.96%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 proxy_pool<os_provider> | <ins>1506480.000000</ins> ns | 1807170.000 ns | -16.64%

</details>


<details>
<summary> Relative perf in group multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 (7): 86.992% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 umfProxy | 126494.000 ns | <ins>120114.000000</ins> ns | 5.31%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 proxy_pool<os_provider> | <ins>328183.000000</ins> ns | 358209.000 ns | -8.38%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 scalable_pool<os_provider> | <ins>18719.300000</ins> ns | 21050.100 ns | -11.07%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 os_provider | <ins>216043.000000</ins> ns | 246988.000 ns | -12.53%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 disjoint_pool<os_provider> | <ins>467168.000000</ins> ns | 544351.000 ns | -14.18%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 glibc | <ins>9561.710000</ins> ns | 12021.200 ns | -20.46%
| multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 jemalloc_pool<os_provider> | <ins>41695.600000</ins> ns | 56658.700 ns | -26.41%

</details>


<details>
<summary> Relative perf in group multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 (4): 92.285% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 umfProxy | <ins>1229910.000000</ins> ns | 1258230.000 ns | -2.25%
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 scalable_pool<os_provider> | <ins>136337.000000</ins> ns | 141010.000 ns | -3.31%
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 glibc | <ins>565627.000000</ins> ns | 636463.000 ns | -11.13%
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 jemalloc_pool<os_provider> | <ins>762763.000000</ins> ns | 883286.000 ns | -13.64%

</details>


<details>
<summary> Relative perf in group multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 (4): 98.108% </summary>

| Benchmark | baseline | feather | Change |
|---|---|---|---|
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 scalable_pool<os_provider> | 68584.300 ns | <ins>51584.600000</ins> ns | 32.95%
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 glibc | <ins>65814.600000</ins> ns | 65934.100 ns | -0.18%
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 umfProxy | <ins>155063.000000</ins> ns | 166857.000 ns | -7.07%
| multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 jemalloc_pool<os_provider> | <ins>112172.000000</ins> ns | 149329.000 ns | -24.88%

</details>

</details>


# Details

<details>
<summary>Benchmark details - environment, command...</summary>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 os_provider</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 os_provider</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 os_provider</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 os_provider</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 proxy_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 proxy_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 proxy_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 proxy_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 disjoint_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 disjoint_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 disjoint_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 disjoint_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 glibc</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 proxy_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 proxy_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 os_provider</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 os_provider</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 disjoint_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 disjoint_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 jemalloc_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 scalable_pool<os_provider></summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv


</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:4 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>alloc/size:10000/0/4096/iterations:200000/threads:1 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:4 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>alloc/size:10000/100000/4096/iterations:200000/threads:1 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:4 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>alloc/min size:10000/max size:0/granularity:8/65536/8/iterations:200000/threads:1 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:4 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>multiple_malloc_free/size:10000/4096/iterations:2000/threads:1 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:4 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


<details>
<summary>multiple_malloc_free/min size:10000/max size:8/granularity:65536/8/iterations:2000/threads:1 umfProxy</summary>

#### Command:
/home/amomot/gits/unified-memory-framework/build/benchmark/umf-benchmark --benchmark_format=csv --benchmark_filter=glibc

#### Environment Variables:
 LD_PRELOAD=/home/amomot/gits/unified-memory-framework/build/lib/libumf_proxy.so

</details>


</details>

