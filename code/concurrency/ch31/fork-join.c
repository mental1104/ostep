#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

sem_t s; 

void *child(void *arg) {
    printf("child\n");
    sem_post(&s);// use semaphore here
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    
    printf("parent: begin\n");
    sem_init(&s, 0, 1);// init semaphore here
    Pthread_create(&p, NULL, child, NULL);
    sem_wait(&s);// use semaphore here
    sleep(1);
    printf("parent: end\n");
    return 0;
}

