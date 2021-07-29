## Chapter 14

### 1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program? 

[null.c](./null.c)  
> Segmentation fault  

### 2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?

`gcc -g null.c`  
`gdb`  
`run`  

```shell
Reading symbols from ./a.out...
(gdb) run
Starting program: /home/espeon/work/OSTEP/code/virtual/a.out 

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at null.c:6
6           printf("%d\n", *ptr);
```

### 3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?

```shell
espeon@Espeon:~/work/OSTEP/code/virtual$ valgrind --leak-check=yes ./null
==799== Memcheck, a memory error detector
==799== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==799== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==799== Command: ./null
==799== 
==799== Invalid read of size 4
==799==    at 0x109161: main (null.c:6)
==799==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==799== 
==799== 
==799== Process terminating with default action of signal 11 (SIGSEGV)
==799==  Access not within mapped region at address 0x0
==799==    at 0x109161: main (null.c:6)
==799==  If you believe this happened as a result of a stack
==799==  overflow in your program's main thread (unlikely but
==799==  possible), you can try to increase the size of the
==799==  main thread stack using the --main-stacksize= flag.
==799==  The main thread stack size used in this run was 8388608.
==799== 
==799== HEAP SUMMARY:
==799==     in use at exit: 0 bytes in 0 blocks
==799==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==799== 
==799== All heap blocks were freed -- no leaks are possible
==799== 
==799== For lists of detected and suppressed errors, rerun with: -s
==799== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault
```

### 4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?  

[forget.c](./forget.c)  

`gdb forget`  
```shell
Reading symbols from forget...
(gdb) run
Starting program: /home/espeon/work/OSTEP/code/virtual/forget 
[Inferior 1 (process 995) exited normally]
```

`valgrind --leak-check=yes ./forget`  
```shell
==1006== Memcheck, a memory error detector
==1006== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1006== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1006== Command: ./forget
==1006== 
==1006== 
==1006== HEAP SUMMARY:
==1006==     in use at exit: 400 bytes in 1 blocks
==1006==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
==1006== 
==1006== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==1006==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1006==    by 0x10915E: main (forget.c:5)
==1006== 
==1006== LEAK SUMMARY:
==1006==    definitely lost: 400 bytes in 1 blocks
==1006==    indirectly lost: 0 bytes in 0 blocks
==1006==      possibly lost: 0 bytes in 0 blocks
==1006==    still reachable: 0 bytes in 0 blocks
==1006==         suppressed: 0 bytes in 0 blocks
==1006== 
==1006== For lists of detected and suppressed errors, rerun with: -s
==1006== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```  

### 5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
[data.c](./data.c)
> Nothing happened 
`valgrind --leak-check=yes ./data`  
```shell
==1224== Memcheck, a memory error detector
==1224== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1224== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1224== Command: ./a.out
==1224== 
==1224== Invalid write of size 4
==1224==    at 0x10918D: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1224==  Address 0x4a4a1d0 is 0 bytes after a block of size 400 alloc'd
==1224==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1224==    by 0x10917E: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1224== 
==1224== 
==1224== HEAP SUMMARY:
==1224==     in use at exit: 0 bytes in 0 blocks
==1224==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==1224== 
==1224== All heap blocks were freed -- no leaks are possible
==1224== 
==1224== For lists of detected and suppressed errors, rerun with: -s
==1224== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### 6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?  
[](./14_6.c)  

```
espeon@Espeon:~/work/OSTEP/code/virtual$ ./a.out
0
```

```shell
==1381== Memcheck, a memory error detector
==1381== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1381== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1381== Command: ./a.out
==1381== 
==1381== Invalid read of size 4
==1381==    at 0x1091B7: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1381==  Address 0x4a4a054 is 20 bytes inside a block of size 40 free'd
==1381==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1381==    by 0x1091AE: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1381==  Block was alloc'd at
==1381==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1381==    by 0x10919E: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1381== 
0
==1381== 
==1381== HEAP SUMMARY:
==1381==     in use at exit: 0 bytes in 0 blocks
==1381==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
==1381== 
==1381== All heap blocks were freed -- no leaks are possible
==1381== 
==1381== For lists of detected and suppressed errors, rerun with: -s
==1381== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### 7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?  
[7.c](./14_7.c)  
```shell
espeon@Espeon:~/work/OSTEP/code/virtual$ ./a.out
free(): invalid pointer
Aborted
```

`valgrind --leak-check=yes ./a.out`  

```shell
==1540== Memcheck, a memory error detector
==1540== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1540== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1540== Command: ./a.out
==1540== 
==1540== Invalid free() / delete / delete[] / realloc()
==1540==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1540==    by 0x10919A: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1540==  Address 0x4a4a054 is 20 bytes inside a block of size 40 alloc'd
==1540==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1540==    by 0x10917E: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1540== 
==1540== 
==1540== HEAP SUMMARY:
==1540==     in use at exit: 40 bytes in 1 blocks
==1540==   total heap usage: 1 allocs, 1 frees, 40 bytes allocated
==1540== 
==1540== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==1540==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1540==    by 0x10917E: main (in /home/espeon/work/OSTEP/code/virtual/a.out)
==1540== 
==1540== LEAK SUMMARY:
==1540==    definitely lost: 40 bytes in 1 blocks
==1540==    indirectly lost: 0 bytes in 0 blocks
==1540==      possibly lost: 0 bytes in 0 blocks
==1540==    still reachable: 0 bytes in 0 blocks
==1540==         suppressed: 0 bytes in 0 blocks
==1540== 
==1540== For lists of detected and suppressed errors, rerun with: -s
==1540== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

### 8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.  

[vector.h](./vector.h)  
[vector.c](./vector.c)  
`valgrind --leak-check=yes ./a.out`  
```shell
==2020== Memcheck, a memory error detector
==2020== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2020== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==2020== Command: ./a.out
==2020== 
first value: 4
second value: 5
third value: 6
size: 3
capacity: 4
==2020== 
==2020== HEAP SUMMARY:
==2020==     in use at exit: 0 bytes in 0 blocks
==2020==   total heap usage: 4 allocs, 4 frees, 1,052 bytes allocated
==2020== 
==2020== All heap blocks were freed -- no leaks are possible
==2020== 
==2020== For lists of detected and suppressed errors, rerun with: -s
==2020== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```  
[Dynamic array - Wikipedia](https://en.wikipedia.org/wiki/Dynamic_array#Performance)
### 9. Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.
