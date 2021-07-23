# Chapter 30 Condition Variable
 
## Homework  

### 1. Our first question focuses on main-two-cvs-while.c (the working solution). First, study the code. Do you think you have an understanding of what should happen when you run the program?

### 2. Run with one producer and one consumer, and have the producer produce a few values. Start with a buffer (size 1), and then increase it. How does the behavior of the code change with larger buffers? (or does it?) What would you predict num_full to be with different buffer sizes (e.g., -m 10) and different numbers of produced items (e.g., -l 100), when you change the consumer sleep string from default(nosleep)to -C 0,0,0,0,0,0,1?  

`./main-two-cvs-while -p 1 -c 1 -m 1 -v`
`./main-two-cvs-while -p 1 -c 1 -m 10 -l 10 -C 0,0,0,0,0,0,1 -v`  

### 3. If possible, run the code on different systems (e.g., a Mac and Linux). Do you see different behavior across these systems?

> Not possible.  

### 4. Let’s look at some timings. How long do you think the following execution, with one producer, three consumers, a single-entry shared buffer, and each consumer pausing at point c3 for a second, will take? ./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t  

> Total time: 12.02 seconds.  

### 5. Now change the size of the shared buffer to 3 (-m 3). Will this make any difference in the total time?

`./main-two-cvs-while -p 1 -c 3 -m 3 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t`  

> Total time: 11.02 seconds.  

### 6. Now change the location of the sleep to c6 (this models a consumer taking something off the queue and then doing something with it), again using a single-entry buffer. What time do you predict in this case? ./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t

```shell
Consumer consumption:
  C0 -> 4
  C1 -> 3
  C2 -> 3

Total time: 5.00 seconds
```

### 7. Finally, change the buffer size to 3 again (-m 3). What time do you predict now?

```shell
Consumer consumption:
  C0 -> 3
  C1 -> 4
  C2 -> 3

Total time: 5.01 seconds
```
### 8. Now let’s look at main-one-cv-while.c. Can you configure a sleep string, assuming a single producer, one consumer, and a buffer of size 1, to cause a problem with this code?

> No  

### 9. Now change the number of consumers to two. Can you construct sleep strings for the producer and the consumers so as to cause a problem in the code?  

```shell
 NF        P0 C0 C1
  0 [*--- ] p0
  0 [*--- ]    c0
  0 [*--- ]       c0
  0 [*--- ] p1
  1 [*  0 ] p4
  1 [*  0 ] p5
  1 [*  0 ] p6
  1 [*  0 ]    c1
  0 [*--- ]    c4
  0 [*--- ]    c5
  0 [*--- ]    c6
  0 [*--- ]       c1
  0 [*--- ]    c0
  0 [*--- ]       c2
  1 [*EOS ] [main: added end-of-stream marker]
  1 [*EOS ]       c3
  0 [*--- ]       c4
  0 [*--- ]       c5
  0 [*--- ]       c6
  0 [*--- ]    c1
  0 [*--- ]    c2
  1 [*EOS ] [main: added end-of-stream marker]
  1 [*EOS ]    c3
  0 [*--- ]    c4
  0 [*--- ]    c5
  0 [*--- ]    c6

Consumer consumption:
  C0 -> 1
  C1 -> 0
```

### 10. Now examine main-two-cvs-if.c. Can you cause a problem to happen in this code? Again consider the case where there is only one consumer, and then the case where there is more than one.  

> always use while.  

### 11. Finally, examine main-two-cvs-while-extra-unlock.c. What problem arises when you release the lock before doing a put or a get? Can you reliably cause such a problem to happen, given the sleep strings? What bad thing can happen?  

`./main-two-cvs-while-extra-unlock -p 1 -c 2 -m 10 -l 10 -v -C 0,0,0,0,1,0,0:0,0,0,0,0,0,0`  

> First consumer only consumes one value.