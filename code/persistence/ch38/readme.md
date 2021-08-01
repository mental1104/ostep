# Chapter 38 Redundant Arrays of Inexpensive Disks (RAIDs)

This section introduces raid.py, a simple RAID simulator you can use to shore up your knowledge of how RAID systems work. See the README for details.  

## Questions

### 1. Use the simulator to perform some basic RAID mapping tests. Run with different levels (0, 1, 4, 5) and see if you can figure out the mappings of a set of requests. For RAID-5, see if you can figure out the difference between left-symmetric and left-asymmetric layouts. Use some different random seeds to generate different problems than above.

```shell
./raid.py -L 5 -5 LS -c -W seq
./raid.py -L 5 -5 LA -c -W seq

left-symmetric    left-asymmetric
0 1 2 P           0 1 2 P
4 5 P 3           3 4 P 5
8 P 6 7           6 P 7 8
```
### 2. Do the same as the first problem, but this time vary the chunk size with -C. How does chunk size change the mappings?

`./raid.py -L 5 -5 LS -c -W seq -C 8K -n 12`  

```shell
0  2  4  P
1  3  5  P
8 10  P  6
9 11  P  7
```

### 3. Do the same as above, but use the -r flag to reverse the nature of each problem.  

`./raid.py -L 5 -5 LS -W seq -C 8K -n 12 -r -c`  

### 4. Now use the reverse flag but increase the size of each request with the -S flag. Try specifying sizes of 8k, 12k, and 16k, while varying the RAID level. What happens to the underlying I/O pattern when the size of the request increases? Make sure to try this with the sequential workload too (-W sequential); for what request sizes are RAID-4 and RAID-5 much more I/O efficient?

```shell
$ ./raid.py -L 4 -S 4k -c -W seq
$ ./raid.py -L 4 -S 8k -c -W seq
$ ./raid.py -L 4 -S 12k -c -W seq
$ ./raid.py -L 4 -S 16k -c -W seq
$ ./raid.py -L 5 -S 4k -c -W seq
$ ./raid.py -L 5 -S 8k -c -W seq
$ ./raid.py -L 5 -S 12k -c -W seq
$ ./raid.py -L 5 -S 16k -c -W seq
```

