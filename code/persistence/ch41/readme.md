# Chapter 41 Locality and The Fast File System

## Homework (Simulation)  

This section introduces ffs.py, a simple FFS simulator you can use to understand better how FFS-based file and directory allocation work. See the README for details on how to run the simulator.  

## Questions  

### 1. Examine the file in.largefile, and then run the simulator with flag -f in.largefile and -L 4. The latter sets the large-file exception to 4 blocks. What will the resulting allocation look like? Run with -c to check.

`./ffs.py -f in.largefile -L 4 -c`  

```
group inodes     data
    0 /a-------- /aaaa----- ---------- ---------- 
    1 ---------- aaaa------ ---------- ---------- 
    2 ---------- aaaa------ ---------- ---------- 
    3 ---------- aaaa------ ---------- ---------- 
    4 ---------- aaaa------ ---------- ---------- 
    5 ---------- aaaa------ ---------- ---------- 
    6 ---------- aaaa------ ---------- ---------- 
    7 ---------- aaaa------ ---------- ---------- 
    8 ---------- aaaa------ ---------- ---------- 
    9 ---------- aaaa------ ---------- ---------- 
```

### 2. Now run with -L 30. What do you expect to see? Once again, turn on -c to see if you were right. You can also use -S to see exactly which blocks were allocated to the file /a. 

> It's the same without `-L 4`.  

### 3. Now we will compute some statistics about the file. The first is something we call filespan, which is the max distance between any two data blocks of the file or between the inode and any data block. Calculate the filespan of /a. Run ffs.py -f in.largefile -L 4 -T -c to see what it is. Do the same with -L 100. What difference do you expect in filespan as the large-file exception parameter changes from low values to high values? 

```
group inodes     data
    0 /a-------- /aaaa----- ---------- ---------- 
    1 ---------- aaaa------ ---------- ---------- 
    2 ---------- aaaa------ ---------- ---------- 
    3 ---------- aaaa------ ---------- ---------- 
    4 ---------- aaaa------ ---------- ---------- 
    5 ---------- aaaa------ ---------- ---------- 
    6 ---------- aaaa------ ---------- ---------- 
    7 ---------- aaaa------ ---------- ---------- 
    8 ---------- aaaa------ ---------- ---------- 
    9 ---------- aaaa------ ---------- ---------- 

span: files
  file:         /a  filespan: 372
               avg  filespan: 372.00

span: directories
  dir:           /  dirspan: 373
               avg  dirspan: 373.00
```  

`./ffs.py -f in.largefile -L 100 -T -c`  

```
group inodes     data
    0 /a-------- /aaaaaaaaa aaaaaaaaaa aaaaaaaaaa 
    1 ---------- aaaaaaaaaa a--------- ---------- 
    2 ---------- ---------- ---------- ---------- 
    3 ---------- ---------- ---------- ---------- 
    4 ---------- ---------- ---------- ---------- 
    5 ---------- ---------- ---------- ---------- 
    6 ---------- ---------- ---------- ---------- 
    7 ---------- ---------- ---------- ---------- 
    8 ---------- ---------- ---------- ---------- 
    9 ---------- ---------- ---------- ---------- 

span: files
  file:         /a  filespan:  59
               avg  filespan:  59.00

span: directories
  dir:           /  dirspan:  60
               avg  dirspan:  60.00
```  
It should decrease.  

### 4. Now let’s look at a new input file, in.manyfiles. How do you think the FFS policy will lay these files out across groups? (you can run with -v to see what files and directories are created, or just cat in.manyfiles). Run the simulator with -c to see if you were right.  

`./ffs.py -f in.manyfiles -c`  

```
group inodes     data
    0 /abcdefghi /aabbccdde effgghhii- ---------- 
    1 jlmnopqrC- jlmnopqrCC C--------- ---------- 
    2 tuvwxyzAB- tuuuvvvwww xxxyyyzzzA AABBB----- 
    3 ---------- ---------- ---------- ---------- 
    4 ---------- ---------- ---------- ---------- 
    5 ---------- ---------- ---------- ---------- 
    6 ---------- ---------- ---------- ---------- 
    7 ---------- ---------- ---------- ---------- 
    8 ---------- ---------- ---------- ---------- 
    9 ---------- ---------- ---------- ---------- 
```

### 5. A metric to evaluate FFS is called dirspan. This metric calculates the spread of files within a particular directory, specifically the max distance between the inodes and data blocks of all files in the directory and the inode and data block of the directory itself. Run with in.manyfiles and the -T flag, and calculate the dirspan of the three directories. Run with -c to check. How good of a job does FFS do in minimizing dirspan?

`./ffs.py -f in.manyfiles -c -T`  

```
span: files
  file:       /t/A  filespan:  24
  file:       /t/B  filespan:  26
  file:       /j/n  filespan:  10
  file:       /j/o  filespan:  10
  file:       /j/l  filespan:  10
  file:         /h  filespan:  18
  file:         /g  filespan:  17
  file:         /f  filespan:  16
  file:         /e  filespan:  15
  file:         /d  filespan:  14
  file:         /c  filespan:  13
  file:         /b  filespan:  12
  file:         /a  filespan:  11
  file:       /t/x  filespan:  18
  file:       /t/y  filespan:  20
  file:       /t/z  filespan:  22
  file:       /j/C  filespan:  12
  file:       /j/r  filespan:  10
  file:       /j/p  filespan:  10
  file:       /t/u  filespan:  12
  file:       /t/v  filespan:  14
  file:       /t/w  filespan:  16
  file:       /j/q  filespan:  10
  file:         /i  filespan:  19
  file:       /j/m  filespan:  10
               avg  filespan:  14.76

span: directories
  dir:           /  dirspan:  28
  dir:          /t  dirspan:  34
  dir:          /j  dirspan:  20
               avg  dirspan:  27.33
```

### 6. Now change the size of the inode table per group to 5 (-i 5). How do you think this will change the layout of the files? Run with -c to see if you were right. How does it affect the dirspan?

`./ffs.py -f in.manyfiles -c -T -i 5`  


```
group inode data
    0 /abcd /aabbccdd- ---------- ---------- 
    1 efghi eeffgghhii ---------- ---------- 
    2 jlmno jlmno----- ---------- ---------- 
    3 tuvwx tuuuvvvwww xxx------- ---------- 
    4 ypzqA yyypzzzqAA A--------- ---------- 
    5 rBC-- rBBBCCC--- ---------- ---------- 
    6 ----- ---------- ---------- ---------- 
    7 ----- ---------- ---------- ---------- 
    8 ----- ---------- ---------- ---------- 
    9 ----- ---------- ---------- ---------- 

span: files
  file:       /t/A  filespan:  11
  file:       /t/B  filespan:   7
  file:       /j/n  filespan:   5
  file:       /j/o  filespan:   5
  file:       /j/l  filespan:   5
  file:         /h  filespan:   9
  file:         /g  filespan:   8
  file:         /f  filespan:   7
  file:         /e  filespan:   6
  file:         /d  filespan:   9
  file:         /c  filespan:   8
  file:         /b  filespan:   7
  file:         /a  filespan:   6
  file:       /t/x  filespan:  13
  file:       /t/y  filespan:   7
  file:       /t/z  filespan:   9
  file:       /j/C  filespan:   9
  file:       /j/r  filespan:   5
  file:       /j/p  filespan:   7
  file:       /t/u  filespan:   7
  file:       /t/v  filespan:   9
  file:       /t/w  filespan:  11
  file:       /j/q  filespan:   9
  file:         /i  filespan:  10
  file:       /j/m  filespan:   5
               avg  filespan:   7.76

span: directories
  dir:           /  dirspan:  49
  dir:          /t  dirspan:  78
  dir:          /j  dirspan: 116
               avg  dirspan:  81.00
```

### 7. Which group should FFS place inode of a new directory in? The default (simulator) policy looks for the group with the most free inodes. A different policy looks for a set of groups with the most free inodes. For example, if you run with -A 2, when allocating a new directory, the simulator will look at groups in pairs and pick the best pair for the allocation. Run ./ffs.py -f in.manyfiles -i 5 -A 2 -c to see how allocation changes with this strategy. How does it affect dirspan? Why might this policy be good?

`./ffs.py -f in.manyfiles -i 5 -A 2 -c -T`  

```
group inode data
    0 /abcd /aabbccdd- ---------- ---------- 
    1 efghi eeffgghhii ---------- ---------- 
    2 jlmno jlmno----- ---------- ---------- 
    3 pqrC- pqrCCC---- ---------- ---------- 
    4 tuvwx tuuuvvvwww xxx------- ---------- 
    5 yzAB- yyyzzzAAAB BB-------- ---------- 
    6 ----- ---------- ---------- ---------- 
    7 ----- ---------- ---------- ---------- 
    8 ----- ---------- ---------- ---------- 
    9 ----- ---------- ---------- ---------- 

span: files
  file:       /t/A  filespan:  11
  file:       /t/B  filespan:  13
  file:       /j/n  filespan:   5
  file:       /j/o  filespan:   5
  file:       /j/l  filespan:   5
  file:         /h  filespan:   9
  file:         /g  filespan:   8
  file:         /f  filespan:   7
  file:         /e  filespan:   6
  file:         /d  filespan:   9
  file:         /c  filespan:   8
  file:         /b  filespan:   7
  file:         /a  filespan:   6
  file:       /t/x  filespan:  13
  file:       /t/y  filespan:   7
  file:       /t/z  filespan:   9
  file:       /j/C  filespan:   7
  file:       /j/r  filespan:   5
  file:       /j/p  filespan:   5
  file:       /t/u  filespan:   7
  file:       /t/v  filespan:   9
  file:       /t/w  filespan:  11
  file:       /j/q  filespan:   5
  file:         /i  filespan:  10
  file:       /j/m  filespan:   5
               avg  filespan:   7.68

span: directories
  dir:           /  dirspan:  49
  dir:          /t  dirspan:  51
  dir:          /j  dirspan:  45
               avg  dirspan:  48.33
```

> Just like best search, it places the j and t dir into two big enough groups to decrase dirspan.  

### 8. One last policy change we will explore relates to file fragmentation. Run ./ffs.py -f in.fragmented -v and see if you can predict how the files that remain are allocated. Run with -c to confirm your answer. What is interesting about the data layout of file /i? Why is it problematic?  

> It increase the fragmentation of the group, both inode and data.  

`./ffs.py -f in.fragmented -v -c`  

```
group inodes     data
    0 /ib-d-f-h- /ibidifihi iii------- ---------- 
    1 ---------- ---------- ---------- ---------- 
    2 ---------- ---------- ---------- ---------- 
    3 ---------- ---------- ---------- ---------- 
    4 ---------- ---------- ---------- ---------- 
    5 ---------- ---------- ---------- ---------- 
    6 ---------- ---------- ---------- ---------- 
    7 ---------- ---------- ---------- ---------- 
    8 ---------- ---------- ---------- ---------- 
    9 ---------- ---------- ---------- ---------- 
```

### 9. A new policy, which we call contiguous allocation (-C), tries to ensure that each file is allocated contiguously. Specifically, with -C n, the file system tries to ensure that n contiguous blocks are free within a group before allocating a block. Run ./ffs.py -f in.fragmented -v -C 2 -c to see the difference. How does layout change as the parameter passed to -C increases? Finally, how does -C affect filespan and dirspan?  

`./ffs.py -f in.fragmented -v -c -C 2`  

```
group inodes     data
    0 /ib-d-f-h- /-b-d-f-hi iiiiiii--- ---------- 
    1 ---------- ---------- ---------- ---------- 
    2 ---------- ---------- ---------- ---------- 
    3 ---------- ---------- ---------- ---------- 
    4 ---------- ---------- ---------- ---------- 
    5 ---------- ---------- ---------- ---------- 
    6 ---------- ---------- ---------- ---------- 
    7 ---------- ---------- ---------- ---------- 
    8 ---------- ---------- ---------- ---------- 
    9 ---------- ---------- ---------- ---------- 
```