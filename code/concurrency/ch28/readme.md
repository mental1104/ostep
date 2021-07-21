# Chapter 28: Locks  

## Homework  

### 1. Examine flag.s. This code “implements” locking with a single memory flag. Can you understand the assembly?  
> It simply sets the mutex from 0 to 1 and then enter the critical section.  

### 2.  When you run with the defaults, does flag.s work? Use the -M and -R flags to trace variables and registers (and turn on -c to see their values). Can you predict what value will end up in flag?  

```shell
espeon@Espeon:~/work/OSTEP/code/concurrency/ch28$ ./x86.py -p flag.s -t 1 -i 100 -R ax -M flag -c
ARG seed 0
ARG numthreads 1
ARG program flag.s
ARG interrupt frequency 100
ARG interrupt randomness False
ARG procsched 
ARG argv 
ARG load address 1000
ARG memsize 128
ARG memtrace flag
ARG regtrace ax
ARG cctrace False
ARG printstats False
ARG verbose False


 flag      ax          Thread 0         

    0       0   
    0       0   1000 mov  flag, %ax
    0       0   1001 test $0, %ax
    0       0   1002 jne  .acquire
    1       0   1003 mov  $1, flag
    1       0   1004 mov  count, %ax
    1       1   1005 add  $1, %ax
    1       1   1006 mov  %ax, count
    0       1   1007 mov  $0, flag
    0       1   1008 sub  $1, %bx
    0       1   1009 test $0, %bx
    0       1   1010 jgt .top
    0       1   1011 halt
```

### 3. Change the value of the register %bx with the -a flag (e.g., -a bx=2,bx=2 if you are running just two threads). What does the code do? How does it change your answer for the question above?  

```shell
espeon@Espeon:~/work/OSTEP/code/concurrency/ch28$ ./x86.py -p flag.s -t 1 -i 100 -R ax -M flag -a bx=2 -c
ARG seed 0
ARG numthreads 1
ARG program flag.s
ARG interrupt frequency 100
ARG interrupt randomness False
ARG procsched 
ARG argv bx=2
ARG load address 1000
ARG memsize 128
ARG memtrace flag
ARG regtrace ax
ARG cctrace False
ARG printstats False
ARG verbose False


 flag      ax          Thread 0         

    0       0   
    0       0   1000 mov  flag, %ax
    0       0   1001 test $0, %ax
    0       0   1002 jne  .acquire
    1       0   1003 mov  $1, flag
    1       0   1004 mov  count, %ax
    1       1   1005 add  $1, %ax
    1       1   1006 mov  %ax, count
    0       1   1007 mov  $0, flag
    0       1   1008 sub  $1, %bx
    0       1   1009 test $0, %bx
    0       1   1010 jgt .top
    0       0   1000 mov  flag, %ax
    0       0   1001 test $0, %ax
    0       0   1002 jne  .acquire
    1       0   1003 mov  $1, flag
    1       1   1004 mov  count, %ax
    1       2   1005 add  $1, %ax
    1       2   1006 mov  %ax, count
    0       2   1007 mov  $0, flag
    0       2   1008 sub  $1, %bx
    0       2   1009 test $0, %bx
    0       2   1010 jgt .top
    0       2   1011 halt
```

### 4. Set bx to a high value for each thread, and then use the -i flag to generate different interrupt frequencies; what values lead to a bad outcomes? Which lead to good outcomes? 
`./x86.py -p flag.s -t 2 -i 100 -R ax -M flag -a bx=100 -c`    
```shell
    1     180                            1004 mov  count, %ax
    1     181                            1005 add  $1, %ax
    1     181                            1006 mov  %ax, count
    0     181                            1007 mov  $0, flag
    0     181                            1008 sub  $1, %bx
    0     181                            1009 test $0, %bx
    0     181                            1010 jgt .top
    0     172   ------ Interrupt ------  ------ Interrupt ------  
    0     172   1011 halt
    0     181   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     181                            1011 halt
```
`./x86.py -p flag.s -t 3 -i 22 -R ax -M flag -a bx=100,bx=100,bx=100 -c`  
Since `flag.s` has 11 instructions, when `-i` is set to multiple of 11, it works correctly.  

### 5. Now let’s look at the program test-and-set.s. First, try to understand the code, which uses the xchg instruction to build a simple locking primitive. How is the lock acquire written? How about lock release? 

acquire:  
```s
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again
```  

release:  
```s
mov  $0, mutex
```

### 6. Now run the code, changing the value of the interrupt interval (-i) again, and making sure to loop for a number of times. Does the code always work as expected? Does it sometimes lead to an inefficient use of the CPU? How could you quantify that?

> The interval was set to a number from 1 to 100 and it always worked as expected.  

### 7. Use the -P flag to generate specific tests of the locking code. For example, run a schedule that grabs the lock in the first thread, but then tries to acquire it in the second. Does the right thing happen? What else should you test?  

> Yes. Performance and fairness.  

### 8. Now let’s look at the code in peterson.s, which implements Peterson’s algorithm (mentioned in a sidebar in the text). Study the code and see if you can make sense of it.

> Omission  

### 9. Now run the code with different values of -i. What kinds of different behavior do you see? Make sure to set the thread IDs appropriately (using -a bx=0,bx=1 for example) as the code assumes it.

> Omission(Temporarily)  

### 10. Can you control the scheduling (with the -P flag) to “prove” that the code works? What are the different cases you should show hold? Think about mutual exclusion and deadlock avoidance.  

> Omission(Temporarily)  

### 11. Now study the code for the ticket lock in ticket.s. Does it match the code in the chapter? Then run with the following flags: -a bx=1000,bx=1000 (causing each thread to loop through the critical section 1000 times). Watch what happens; do the threads spend much time spin-waiting for the lock?

`./x86.py -p ticket.s -M count,ticket,turn -R ax,bx,cx -a bx=1000,bx=1000 -c`  

> Count is correct.  

> Threads indeed spend much time spin-waiting:

```shell
1008 mov $1, %ax
 1995  1996  1995    1994     5  1994                            1009 fetchadd %ax, turn
 1995  1996  1995    1994     4  1994                            1010 sub  $1, %bx
 1995  1996  1995    1994     4  1994                            1011 test $0, %bx
 1995  1996  1995    1994     4  1994                            1012 jgt .top
 1995  1996  1995       1     4  1994                            1000 mov $1, %ax
 1995  1997  1995    1996     4  1994                            1001 fetchadd %ax, ticket
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 1995  1997  1995    1996     4  1995                            1002 mov turn, %cx
 1995  1997  1995    1996     4  1995                            1003 test %cx, %ax
 1995  1997  1995    1996     4  1995                            1004 jne .tryagain
 ```

> See the non-stop 1002-1004 instruction, which might be enlightening.  

### 12. How does the code behave as you add more threads?  

`./x86.py -p ticket.s -M count -t 10 -c -i 5`  

### 13. Now examine yield.s, in which a yield instruction enables one thread to yield control of the CPU (realistically, this would be an OS primitive, but for the simplicity, we assume an instruction does the task). Find a scenario where test-and-set.s wastes cycles spinning, but yield.s does not. How many instructions are saved? In what scenarios do these savings arise?  

`./x86.py -p test-and-set.s -M count,mutex -R ax,bx -a bx=5,bx=5 -c -i 7`  
`./x86.py -p yield.s -M count,mutex -R ax,bx -a bx=5,bx=5 -c -i 7`  

### 14. Finally, examine test-and-test-and-set.s. What does this lock do? What kind of savings does it introduce as compared to test-and-set.s?

> Change mutex to 1 only if lock is free. That will avoid unnecessary writing.
