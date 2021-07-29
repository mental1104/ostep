#include<stdio.h>
#include<stdlib.h>

int main(){
    int *data = (int *)malloc(10*sizeof(int));
    free(data);
    printf("%d\n", data[5]);
    return 0;
}