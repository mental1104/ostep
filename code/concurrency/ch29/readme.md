# Chapter 29 Lock-based Concurrent Data Structures  

## Homework  

---
### 1. We’ll start by redoing the measurements within this chapter. Use the call gettimeofday() to measure time within your program. How accurate is this timer? What is the smallest interval it can measure? Gain confidence in its workings, as we will need it in all subsequent questions. You can also look into other timers, such as the cycle counter available on x86 via the rdtsc instruction.

> [How to Benchmark Code Execution Times on Intel®IA-32 and IA-64 Instruction Set Architectures](https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf)

> microseconds  

### 2. Now, build a simple concurrent counter and measure how long it takes to increment the counter many times as the number of threads increases. How many CPUs are available on the system you are using? Does this number impact your measurements at all?    

[simple_concurrent_counter.c](./simple_concurrent_counter.c)

```shell
1 cpus, 1 threads
global count: 1000000
Time (seconds): 0.019574

1 cpus, 2 threads
global count: 2000000
Time (seconds): 0.030325

1 cpus, 3 threads
global count: 3000000
Time (seconds): 0.045276

1 cpus, 4 threads
global count: 4000000
Time (seconds): 0.060612

1 cpus, 5 threads
global count: 5000000
Time (seconds): 0.075492

1 cpus, 6 threads
global count: 6000000
Time (seconds): 0.090392

2 cpus, 1 threads
global count: 1000000
Time (seconds): 0.015172

2 cpus, 2 threads
global count: 2000000
Time (seconds): 0.080684

2 cpus, 3 threads
global count: 3000000
Time (seconds): 0.103790

2 cpus, 4 threads
global count: 4000000
Time (seconds): 0.157934

2 cpus, 5 threads
global count: 5000000
Time (seconds): 0.190643

2 cpus, 6 threads
global count: 6000000
Time (seconds): 0.225990

3 cpus, 1 threads
global count: 1000000
Time (seconds): 0.015280

3 cpus, 2 threads
global count: 2000000
Time (seconds): 0.079916

3 cpus, 3 threads
global count: 3000000
Time (seconds): 0.099597

3 cpus, 4 threads
global count: 4000000
Time (seconds): 0.120570

3 cpus, 5 threads
global count: 5000000
Time (seconds): 0.177724

3 cpus, 6 threads
global count: 6000000
Time (seconds): 0.200259

4 cpus, 1 threads
global count: 1000000
Time (seconds): 0.015219

4 cpus, 2 threads
global count: 2000000
Time (seconds): 0.080567

4 cpus, 3 threads
global count: 3000000
Time (seconds): 0.100293

4 cpus, 4 threads
global count: 4000000
Time (seconds): 0.169260

4 cpus, 5 threads
global count: 5000000
Time (seconds): 0.190118

4 cpus, 6 threads
global count: 6000000
Time (seconds): 0.253199

5 cpus, 1 threads
global count: 1000000
Time (seconds): 0.015115

5 cpus, 2 threads
global count: 2000000
Time (seconds): 0.078926

5 cpus, 3 threads
global count: 3000000
Time (seconds): 0.100228

5 cpus, 4 threads
global count: 4000000
Time (seconds): 0.169933

5 cpus, 5 threads
global count: 5000000
Time (seconds): 0.255883

5 cpus, 6 threads
global count: 6000000
Time (seconds): 0.273681

6 cpus, 1 threads
global count: 1000000
Time (seconds): 0.015164

6 cpus, 2 threads
global count: 2000000
Time (seconds): 0.079798

6 cpus, 3 threads
global count: 3000000
Time (seconds): 0.099881

6 cpus, 4 threads
global count: 4000000
Time (seconds): 0.169040

6 cpus, 5 threads
global count: 5000000
Time (seconds): 0.256552

6 cpus, 6 threads
global count: 6000000
Time (seconds): 0.342295
```

### 3. Next, build a version of the sloppy counter. Once again, measure its performance as the number of threads varies, as well as the threshold. Do the numbers match what you see in the chapter?  

