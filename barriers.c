#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


pthread_barrier_t barrier;

void * worker1(){
    usleep(600000);
    printf("Первый поток инициализировался!\n");
    pthread_barrier_wait(&barrier);
    printf("Первый поток работает!\n");
    usleep(300000);
    return NULL;
}

void * worker2(){
    usleep(4000000);
    printf("Второй поток инициализировался!\n");
    pthread_barrier_wait(&barrier);
    printf("Второй поток работает!\n");
    usleep(300000);
    return NULL;
}

void * worker3(){
    usleep(200000);
    printf("Третий поток инициализировался!\n"); 
    pthread_barrier_wait(&barrier);
    printf("Третий поток работает!\n");
    usleep(300000);
    return NULL;
}

int main(){
    pthread_barrier_init(&barrier, 0, 3);

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, worker1, NULL);
    pthread_create(&thread2, NULL, worker2, NULL);
    pthread_create(&thread3, NULL, worker3, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_barrier_destroy(&barrier);

    return 0;
}
