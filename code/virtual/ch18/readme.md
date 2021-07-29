## 18. Paging: Introduction  

### 1. Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags:  

> Num of PTE = address space / page size

`./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0`  

```shell
...
  [    1017]   0x00000000
  [    1018]   0x00000000
  [    1019]   0x8002e9c9
  [    1020]   0x00000000
  [    1021]   0x00000000
  [    1022]   0x00000000
  [    1023]   0x00000000
```  
`./paging-linear-translate.py -P 1k -a 2m -p 512m -v -n 0`
```shell
  [    2040]   0x80038ed5
  [    2041]   0x00000000
  [    2042]   0x00000000
  [    2043]   0x00000000
  [    2044]   0x00000000
  [    2045]   0x00000000
  [    2046]   0x8000eedd
  [    2047]   0x00000000
```
`./paging-linear-translate.py -P 1k -a 4m -p 512m -v -n 0`  

```shell
  [    4088]   0x00000000
  [    4089]   0x80078d9a
  [    4090]   0x8006ca8e
  [    4091]   0x800160f8
  [    4092]   0x80015abc
  [    4093]   0x8001483a
  [    4094]   0x00000000
  [    4095]   0x8002e298
```

###  2. Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example:  

`./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 100 -c`  

```shell
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]   0x80000018
  [       1]   0x80000008
  [       2]   0x8000000c
  [       3]   0x80000009
  [       4]   0x80000012
  [       5]   0x80000010
  [       6]   0x8000001f
  [       7]   0x8000001c
  [       8]   0x80000017
  [       9]   0x80000015
  [      10]   0x80000003
  [      11]   0x80000013
  [      12]   0x8000001e
  [      13]   0x8000001b
  [      14]   0x80000019
  [      15]   0x80000000

Virtual Address Trace
  VA 0x00002e0f (decimal:    11791) --> 00004e0f (decimal    19983) [VPN 11]
  VA 0x00001986 (decimal:     6534) --> 00007d86 (decimal    32134) [VPN 6]
  VA 0x000034ca (decimal:    13514) --> 00006cca (decimal    27850) [VPN 13]
  VA 0x00002ac3 (decimal:    10947) --> 00000ec3 (decimal     3779) [VPN 10]
  VA 0x00000012 (decimal:       18) --> 00006012 (decimal    24594) [VPN 0]
```  

### 3. Now let’s try some different random seeds, and some different (and sometimes quite crazy) address-space parameters, for variety:  

`./paging-linear-translate.py -P 8 -a 32 -p 1024 -v -s 1`  
`./paging-linear-translate.py -P 8k -a 32k -p 1m -v -s 2`  
`./paging-linear-translate.py -P 1m -a 256m -p 512m -v -s 3`  

### 4. Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?  

`./paging-linear-translate.py -P 1m -a 256m -p 256m -v -s 3`  

```shell 
ARG seed 3
ARG address space size 256m
ARG phys mem size 256m
ARG page size 1m
ARG verbose True
ARG addresses -1

Error: physical memory size must be GREATER than address space size (for this simulation)
```