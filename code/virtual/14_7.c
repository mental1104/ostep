#include<stdio.h>
#include<stdlib.h>

int main(){
    int* data = (int *)malloc(10*sizeof(int));
    int* ptr = data+5;
    free(ptr);
    return 0;
}