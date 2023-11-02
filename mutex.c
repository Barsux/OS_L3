#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


/*
Представим что у нас есть банк, с возможностью пополнения счёта. Для этого есть две функции чтения и записи баланса.
*/
int balance = 0;


void writeBalance(int amount){
    usleep(250000);
    balance = amount;
}

int getBalance(){
    usleep(250000);
    return balance;
}
/* -----------------------------------------------------------------------------------------------------------------*/

pthread_mutex_t mutex;
int use_mutex = 0;


void * makeDeposit(int * amount){
    if(use_mutex)pthread_mutex_lock(&mutex);
    int balance = getBalance();
    balance += *amount;
    writeBalance(balance);
    if(use_mutex)pthread_mutex_unlock(&mutex);
    return NULL;
}


int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread1, thread2;

    printf("Использовать mutex? Y\\N\n");
    while(1){
        char c;
        scanf("%c", &c);
        if (c == 'Y'){
            use_mutex = 1;
            break;
        }
        else if(c == 'N') break;
        printf("Неправильный ввод, повторите попытку:");
    }
    

    printf("Наш баланс до пополнения: %d\n", getBalance());

    int d1 = 2000;
    int d2 = 1000;

    pthread_create(&thread1, NULL, makeDeposit, (void *)&d1);
    pthread_create(&thread2, NULL, makeDeposit, (void *)&d2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Наш баланс после пополнения: %d\n", getBalance());
    return 0;

}





