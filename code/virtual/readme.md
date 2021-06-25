3. 

```shell
espeon@Espeon:~/work/OSTEP/code/virtual$ free -m
              total        used        free      shared  buff/cache   available
Mem:          12687         224       12295           0         167       12231
Swap:          4096           0        4096
espeon@Espeon:~/work/OSTEP/code/virtual$ fg
./a.out 10 100
^C
espeon@Espeon:~/work/OSTEP/code/virtual$ ./a.out 100 30
pid: 689
^Z
[1]+  Stopped                 ./a.out 100 30
espeon@Espeon:~/work/OSTEP/code/virtual$ free -m
              total        used        free      shared  buff/cache   available
Mem:          12687         316       12204           0         167       12140
Swap:          4096           0        4096
```

for 1G RAM：
```shell
espeon@Espeon:~/work/OSTEP/code/virtual$ free -m
              total        used        free      shared  buff/cache   available
Mem:          12687         236       12279           0         172       12217
Swap:          4096           0        4096
espeon@Espeon:~/work/OSTEP/code/virtual$ ./a.out 1000 30
pid: 713
^Z
[1]+  Stopped                 ./a.out 1000 30
espeon@Espeon:~/work/OSTEP/code/virtual$ free -m
              total        used        free      shared  buff/cache   available
Mem:          12687        1236       11278           0         172       11216
Swap:          4096           0        4096
```