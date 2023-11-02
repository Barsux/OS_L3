#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

void * worker1(){
    printf("Работает первый поток!\n");
    usleep(300000);
    sem_post(&sem2);
    return NULL;
}

void * worker2(){
    sem_wait(&sem2);
    printf("Работает второй поток!\n");
    usleep(200000);
    sem_post(&sem1);
    return NULL;
}

void * worker3(){
    sem_wait(&sem1);
    printf("Работает третий поток!\n");
    usleep(245000);
    return NULL;
}

int main(){
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, worker1, NULL);
    pthread_create(&thread2, NULL, worker2, NULL);
    pthread_create(&thread3, NULL, worker3, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}


