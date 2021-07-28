#include<stdio.h>
#include<semaphore.h>

typedef struct __rwlock_t {
    sem_t mutex;
    sem_t roomEmpty;
    int readers;
    char pad[sizeof(sem_t) - sizeof(int)];
} rwlock_t;

int main(){
    sem_t s;
    rwlock_t lock;
    printf("sizeof semaphore: %lu\n", sizeof(s));
    printf("sizeof semaphore: %lu\n", sizeof(lock));
    return 0;
}