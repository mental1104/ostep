# Chapter 27: Interlude: Thread API
## Homework  

### 1. First build main-race.c. Examine the code so you can see the (hopefully obvious) data race in the code. Now run helgrind (by typing valgrind --tool=helgrind main-race) to see how it reports the race. Does it point to the right lines of code? What other information does it give to you?  

```shell
espeon@Espeon:~/work/OSTEP/code/concurrency/ch27$ valgrind --tool=helgrind ./main-race
==350== Helgrind, a thread error detector
==350== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==350== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==350== Command: ./main-race
==350== 
==350== ---Thread-Announcement------------------------------------------
==350== 
==350== Thread #1 is the program's root thread
==350== 
==350== ---Thread-Announcement------------------------------------------
==350== 
==350== Thread #2 was created
==350==    at 0x49A0282: clone (clone.S:71)
==350==    by 0x48632EB: create_thread (createthread.c:101)
==350==    by 0x4864E0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==350==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==350==    by 0x109513: Pthread_create (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-race)
==350==    by 0x1095F1: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-race)
==350== 
==350== ----------------------------------------------------------------
==350== 
==350== Possible data race during read of size 4 at 0x10C014 by thread #1
==350== Locks held: none
==350==    at 0x1095F2: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-race)
==350== 
==350== This conflicts with a previous write of size 4 by thread #2
==350== Locks held: none
==350==    at 0x1095A6: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-race)
==350==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==350==    by 0x4864608: start_thread (pthread_create.c:477)
==350==    by 0x49A0292: clone (clone.S:95)
==350==  Address 0x10c014 is 0 bytes inside data symbol "balance"
==350== 
==350== ----------------------------------------------------------------
==350== 
==350== Possible data race during write of size 4 at 0x10C014 by thread #1
==350== Locks held: none
==350==    at 0x1095FB: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-race)
==350== 
==350== This conflicts with a previous write of size 4 by thread #2
==350== Locks held: none
==350==    at 0x1095A6: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-race)
==350==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==350==    by 0x4864608: start_thread (pthread_create.c:477)
==350==    by 0x49A0292: clone (clone.S:95)
==350==  Address 0x10c014 is 0 bytes inside data symbol "balance"
==350== 
==350== 
==350== Use --history-level=approx or =none to gain increased speed, at
==350== the cost of reduced accuracy of conflicting-access information
==350== For lists of detected and suppressed errors, rerun with: -s
```

### 2. What happens when you remove one of the offending lines of code? Now add a lock around one of the updates to the shared variable, and then around both. What does helgrind report in each of these cases?  

> Like this:  

```c
int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    //balance++; // unprotected access
    Pthread_join(p, NULL);
    return 0;
}
```
> All clear  

```shell
espeon@Espeon:~/work/OSTEP/code/concurrency/ch27$ valgrind --tool=helgrind ./main-race
==779== Helgrind, a thread error detector
==779== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==779== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==779== Command: ./main-race
==779== 
==779== 
==779== Use --history-level=approx or =none to gain increased speed, at
==779== the cost of reduced accuracy of conflicting-access information
==779== For lists of detected and suppressed errors, rerun with: -s
==779== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```  

### 3. Now let’s look at main-deadlock.c. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). Can you see what problem it might have?  

### 4. Now run helgrind on this code. What does helgrind report?


```shell
espeon@Espeon:~/work/OSTEP/code/concurrency/ch27$ valgrind --tool=helgrind ./main-deadlock
==876== Helgrind, a thread error detector
==876== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==876== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==876== Command: ./main-deadlock
==876== 
==876== ---Thread-Announcement------------------------------------------
==876== 
==876== Thread #3 was created
==876==    at 0x49A0282: clone (clone.S:71)
==876==    by 0x48632EB: create_thread (createthread.c:101)
==876==    by 0x4864E0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==876==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109513: Pthread_create (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x109654: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876== 
==876== ----------------------------------------------------------------
==876== 
==876== Thread #3: lock order "0x10C040 before 0x10C080" violated
==876== 
==876== Observed (incorrect) order is: acquisition of lock at 0x10C080
==876==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109382: Pthread_mutex_lock (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x1095CD: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x4864608: start_thread (pthread_create.c:477)
==876==    by 0x49A0292: clone (clone.S:95)
==876== 
==876==  followed by a later acquisition of lock at 0x10C040
==876==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109382: Pthread_mutex_lock (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x1095D9: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x4864608: start_thread (pthread_create.c:477)
==876==    by 0x49A0292: clone (clone.S:95)
==876== 
==876== Required order was established by acquisition of lock at 0x10C040
==876==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109382: Pthread_mutex_lock (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x1095B3: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x4864608: start_thread (pthread_create.c:477)
==876==    by 0x49A0292: clone (clone.S:95)
==876== 
==876==  followed by a later acquisition of lock at 0x10C080
==876==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109382: Pthread_mutex_lock (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x1095BF: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x4864608: start_thread (pthread_create.c:477)
==876==    by 0x49A0292: clone (clone.S:95)
==876== 
==876==  Lock at 0x10C040 was first observed
==876==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109382: Pthread_mutex_lock (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x1095B3: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x4864608: start_thread (pthread_create.c:477)
==876==    by 0x49A0292: clone (clone.S:95)
==876==  Address 0x10c040 is 0 bytes inside data symbol "m1"
==876== 
==876==  Lock at 0x10C080 was first observed
==876==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x109382: Pthread_mutex_lock (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x1095BF: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-deadlock)
==876==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==876==    by 0x4864608: start_thread (pthread_create.c:477)
==876==    by 0x49A0292: clone (clone.S:95)
==876==  Address 0x10c080 is 0 bytes inside data symbol "m2"
==876== 
==876== 
==876== 
==876== Use --history-level=approx or =none to gain increased speed, at
==876== the cost of reduced accuracy of conflicting-access information
==876== For lists of detected and suppressed errors, rerun with: -s
==876== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
```

### 5. Now run helgrind on main-deadlock-global.c. Examine the code; does it have the same problem that main-deadlock.c has? Should helgrind be reporting the same error? What does this tell you about tools like helgrind?  

> Reporting the same problem.  

### 6. Let’s next look at main-signal.c. This code uses a variable (done) to signal that the child is done and that the parent can now continue. Why is this code inefficient? (what does the parent end up spending its time doing, particularly if the child thread takes a long time to complete?) 

> Inefficient. Since the cpu spins in the loop wasting power.  

### 7. Now run helgrind on this program. What does it report? Is the code correct?
Possible data race with `read()/write()`
```shell
espeon@Espeon:~/work/OSTEP/code/concurrency/ch27$ valgrind --tool=helgrind ./main-signal
==1022== Helgrind, a thread error detector
==1022== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==1022== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1022== Command: ./main-signal
==1022== 
this should print first
==1022== ---Thread-Announcement------------------------------------------
==1022== 
==1022== Thread #1 is the program's root thread
==1022== 
==1022== ---Thread-Announcement------------------------------------------
==1022== 
==1022== Thread #2 was created
==1022==    at 0x49A0282: clone (clone.S:71)
==1022==    by 0x48632EB: create_thread (createthread.c:101)
==1022==    by 0x4864E0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
==1022==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1022==    by 0x109533: Pthread_create (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-signal)
==1022==    by 0x10961C: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-signal)
==1022== 
==1022== ----------------------------------------------------------------
==1022== 
==1022== Possible data race during read of size 4 at 0x10C014 by thread #1
==1022== Locks held: none
==1022==    at 0x10961E: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-signal)
==1022== 
==1022== This conflicts with a previous write of size 4 by thread #2
==1022== Locks held: none
==1022==    at 0x1095CD: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-signal)
==1022==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1022==    by 0x4864608: start_thread (pthread_create.c:477)
==1022==    by 0x49A0292: clone (clone.S:95)
==1022==  Address 0x10c014 is 0 bytes inside data symbol "done"
==1022== 
==1022== ----------------------------------------------------------------
==1022== 
==1022== Possible data race during write of size 1 at 0x52741A5 by thread #1
==1022== Locks held: none
==1022==    at 0x48488A6: mempcpy (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1022==    by 0x49107B1: _IO_new_file_xsputn (fileops.c:1236)
==1022==    by 0x49107B1: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
==1022==    by 0x4905677: puts (ioputs.c:40)
==1022==    by 0x109633: main (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-signal)
==1022==  Address 0x52741a5 is 21 bytes inside a block of size 1,024 alloc'd
==1022==    at 0x483C893: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1022==    by 0x4902E83: _IO_file_doallocate (filedoalloc.c:101)
==1022==    by 0x491304F: _IO_doallocbuf (genops.c:347)
==1022==    by 0x49120AF: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:745)
==1022==    by 0x4910834: _IO_new_file_xsputn (fileops.c:1244)
==1022==    by 0x4910834: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
==1022==    by 0x4905677: puts (ioputs.c:40)
==1022==    by 0x1095CC: worker (in /home/espeon/work/OSTEP/code/concurrency/ch27/main-signal)
==1022==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1022==    by 0x4864608: start_thread (pthread_create.c:477)
==1022==    by 0x49A0292: clone (clone.S:95)
==1022==  Block was alloc'd by thread #2
==1022== 
this should print last
==1022== 
==1022== Use --history-level=approx or =none to gain increased speed, at
==1022== the cost of reduced accuracy of conflicting-access information
==1022== For lists of detected and suppressed errors, rerun with: -s
==1022== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 36)
```

### 8. Now look at a slightly modified version of the code, which is found in main-signal-cv.c. This version uses a condition variable to do the signaling (and associated lock). Why is this code preferred to the previous version? Is it correctness, or performance, or both?  

> Both.  

### 9. Once again run helgrind on main-signal-cv. Does it report any errors?
```shell 
espeon@Espeon:~/work/OSTEP/code/concurrency/ch27$ valgrind --tool=helgrind ./main-signal-cv
==1190== Helgrind, a thread error detector
==1190== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==1190== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1190== Command: ./main-signal-cv
==1190== 
this should print first
this should print last
==1190== 
==1190== Use --history-level=approx or =none to gain increased speed, at
==1190== the cost of reduced accuracy of conflicting-access information
==1190== For lists of detected and suppressed errors, rerun with: -s
==1190== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)
```


