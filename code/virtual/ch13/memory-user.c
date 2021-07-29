#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char** argv){
    if(argc!=3){
        printf("At least one extra parameter!\n");
        return 0;
    }

    printf("pid: %d\n", getpid());

    int memory = atoi(argv[1])*1024*1024;
    int length = (int)(memory/sizeof(int));

    int runTime = atoi(argv[2]);
    int *arr = (int*)malloc(memory);
    clock_t begin = clock();
    double time_spent;

    while(1)
    {
        time_spent = (double)(clock()-begin)/CLOCKS_PER_SEC;
        if(time_spent >= runTime)
            break;
        for(int i = 0; i<length; i++)
            arr[i] += 1;
    }
    free(arr);
    return 0;
}