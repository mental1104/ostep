#include<stdio.h>

int main(){
    unsigned int temp = 0x80000000;
    int v1 = *(int *)&temp;
    int v2 = *(int *)&temp;
    
    printf("%d\n", v1 + v2);//They overflow to 0
    return 0;
}