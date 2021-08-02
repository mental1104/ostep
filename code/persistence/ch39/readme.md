# Chapter 39 Interlude: Files and Directories

## Homework (Code)  

In this homework, we’ll just familiarize ourselves with how the APIs described in the chapter work. To do so, you’ll just write a few different programs, mostly based on various UNIX utilities.  

---

### 1. Stat: Write your own version of the command line program stat, which simply calls the stat() system call on a given file or directory. Print out file size, number of blocks allocated, reference (link) count, and so forth. What is the link count of a directory, as the number of entries in the directory changes? Useful interfaces: stat() 

[stat.c](./stat.c)

`gcc stat.c`  
`./a.out readme.md`  

```shell
File type:              regular file
I-node number               85243
Mode                        100644 (octal)
Link count                  1
Ownership:                  UID=1000     GID=1000
Preferred I/O block size:   4096 bytes
File size:                  624 bytes
Blocks allocated:           8
Last status change:         Mon Aug  2 20:56:28 2021
Last file access:           Mon Aug  2 20:50:26 2021
Last file modification:     Mon Aug  2 20:56:28 2021
espeon@Espeon:~/work/OSTEP/code/persistence/ch39$ ./a.out readme.md
File type:              regular file
I-node number               85243
Mode                        100644 (octal)
Link count                  1
Ownership:                  UID=1000     GID=1000
Preferred I/O block size:   4096 bytes
File size:                  624 bytes
Blocks allocated:           8
Last status change:         Mon Aug  2 20:56:28 2021
Last file access:           Mon Aug  2 20:56:43 2021
Last file modification:     Mon Aug  2 20:56:28 2021
```

### 2. ListFiles: Write a program that lists files in the given directory. When called without any arguments, the program should just print the file names. When invoked with the -l flag, the program should print out information about each file, such as the owner, group, permissions, and other information obtained from the stat() system call. The program should take one additional argument, which is the directory to read, e.g., myls -l directory. If no directory is given, the program should just use the current working directory. Useful interfaces: stat(), opendir(), readdir(), getcwd().

[myls.c](./myls.c)  
`gcc myls.c`  
`./a.out -l`  
```shell
85297     100644      1    1000    1000    1839   Aug 02 20:56  stat.c
85243     100644      1    1000    1000    2275   Aug 02 20:59  readme.md
85298     100644      1    1000    1000    2079   Aug 02 21:34  myls.c
85306     100755      1    1000    1000    17552   Aug 02 21:35  a.out
83437     40755      5    1000    1000    4096   Aug 02 20:19  ..
85183     40755      2    1000    1000    4096   Aug 02 21:35  .
```
### 3. Tail: Write a program that prints out the last few lines of a file. The program should be efficient, in that it seeks to near the end of the file, reads in a block of data, and then goes backwards until it finds the requested number of lines; at this point, it should print out those lines from beginning to the end of the file. To invoke the program, one should type: mytail -n file, where n is the number of lines at the end of the file to print. Useful interfaces: stat(), lseek(), open(), read(), close().

```shell
espeon@Espeon:~/work/OSTEP/code/persistence/ch39$ ./a.out -10 readme.md 
`gcc myls.c`  
`./a.out -l`  
```shell
85297     100644      1    1000    1000    1839   Aug 02 20:56  stat.c
85243     100644      1    1000    1000    2275   Aug 02 20:59  readme.md
85298     100644      1    1000    1000    2079   Aug 02 21:34  myls.c
85306     100755      1    1000    1000    17552   Aug 02 21:35  a.out
83437     40755      5    1000    1000    4096   Aug 02 20:19  ..
85183     40755      2    1000    1000    4096   Aug 02 21:35  .

### 3. Tail: Write a program that prints out the last few lines of a file. The program should be efficient, in that it seeks to near the end of the file, reads in a block of data, and then goes backwards until it finds the requested number of lines; at this point, it should print out those lines from beginning to the end of the file. To invoke the program, one should type: mytail -n file, where n is the number of lines at the end of the file to print. Useful interfaces: stat(), lseek(), open(), read(), close().
```

### 4. Recursive Search: Write a program that prints out the names of each file and directory in the file system tree, starting at a given point in the tree. For example, when run without arguments, the program should start with the current working directory and print its contents, as well as the contents of any sub-directories, etc., until the entire tree, root at the CWD, is printed. If given a single argument (of a directory name), use that as the root of the tree instead. Refine your recursive search with more fun options, similar to the powerful find command line tool. Useful interfaces: you figure it out.

[myfind.c](./myfind.c)  

