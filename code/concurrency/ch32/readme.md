# Chapter 32 Common Concurrency Problems 

## Homework (Code)

This homework lets you explore some real code that deadlocks (or avoids deadlock). The different versions of code correspond to different approaches to avoiding deadlock in a simplified vector_add() routine. See the README for details on these programs and their common substrate.  

### 1. First let’s make sure you understand how the programs generally work, and some of the key options. Study the code in vector-deadlock.c, as well as in main-common.c and related files.  

### Now, run ./vector-deadlock -n 2 -l 1 -v, which instantiates two threads (-n 2), each of which does one vector add (-l 1), and does so in verbose mode (-v). Make sure you understand the output. How does the output change from run to run?

```shell
➜  ch32 git:(main) ✗ ./vector-deadlock -n 2 -l 1 -v
->add(0, 1)
<-add(0, 1)
              ->add(0, 1)
              <-add(0, 1)
```

### 2. Now add the -d flag, and change the number of loops(-l) from 1 to higher numbers. What happens? Does the code (always) deadlock?

```shell
➜  ch32 git:(main) ✗ ./vector-deadlock -n 2 -l 10 -v -d
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
              <-add(1, 0)
              ->add(1, 0)
<-add(0, 1)
->add(0, 1)
(pause)
```
> Not always, but sometimes.  

### 3. How does changing the number of threads (-n) change the outcome of the program? Are there any values of -n that ensure no deadlock occurs?  

> 0,1.

### 4. Now examine the code in vector-global-order.c. First, make sure you understand what the code is trying to do; do you understand why the code avoids deadlock? Also, why is there a special case in this vector_add() routine when the source and destination vectors are the same?

> They're the same. No deadlock, since they're compared by the addresses.  

### 5. Now run the code with the following flags: -t -n 2 -l 100000 -d. How long does the code take to complete? How does the total time change when you increase the number of loops, or the number of threads?

```shell
➜  ch32 git:(main) ✗ ./vector-global-order -t -n 2 -l 100000 -d        
Time: 0.04 seconds
➜  ch32 git:(main) ✗ ./vector-global-order -t -n 2 -l 200000 -d
Time: 0.08 seconds
➜  ch32 git:(main) ✗ ./vector-global-order -t -n 4 -l 50000 -d
Time: 0.11 seconds
```

### 6. What happens if you turn on the parallelism flag (-p)? How much would you expect performance to change when each thread is working on adding different vectors (which is what -p enables) versus working on the same ones?

```shell
➜  ch32 git:(main) ✗ ./vector-global-order -t -n 2 -l 100000 -d -p        
Time: 0.02 seconds
➜  ch32 git:(main) ✗ ./vector-global-order -t -n 2 -l 200000 -d -p
Time: 0.02 seconds
➜  ch32 git:(main) ✗ ./vector-global-order -t -n 4 -l 50000 -d -p
Time: 0.02 seconds
```

### 7. Now let’s study vector-try-wait.c. First make sure you understand the code. Is the first call to pthread_mutex_trylock() really needed? Now run the code. How fast does it run compared to the global order approach? How does the number of retries, as counted by the code, change as the number of threads increases?



