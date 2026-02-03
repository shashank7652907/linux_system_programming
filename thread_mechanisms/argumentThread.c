#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg){
    sleep(1);
    int index = *((int *)arg);
    printf("[%d]",index);
    free(arg);
    pthread_exit(0);
}

int main(int argc, char* argv[]){
    pthread_t th[10];
    for(int i = 0; i < 10; i++){
        int* a = (int *)malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, &routine, a) == -1){
            printf("Thread create failed [%d]",i);
            return i + 1;
        }
        printf("Thread [%d] created\n",i);
    }

    for(int i = 0; i < 10;i++){
        if(pthread_join(th[i], NULL) == -1){
            printf("Thread [%d] join failed\n",i);
            return i + 7;
        }
    }
    printf("\n");

    return 0;
}