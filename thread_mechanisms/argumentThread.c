#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg){
    int sum = 0;
    int a = *(int *)arg;
    for(int i = a; i < a + 5; i ++){
        sum += primes[i];
    }
    *(int *)arg = sum;
    printf("Local sum : %d\n",sum);
    return arg;
}

int main(int argc, char* argv[]){
    pthread_t th[10];
    for(int i = 0; i < 2; i++){
        int* a = (int *)malloc(sizeof(int));
        *a = i * 5;
        if(pthread_create(&th[i], NULL, &routine, a) == -1){
            printf("Thread create failed [%d]",i);
            return i + 1;
        }
        printf("Thread [%d] created\n",i);
    }
    int globalSum = 0;
    for(int i = 0; i < 2;i++){
        int* r;
        if(pthread_join(th[i], (void **)&r) == -1){
            printf("Thread [%d] join failed\n",i);
            return i + 7;
        }
        globalSum +=  *r;
        free(r);
    }
    printf("Sum is %d ",globalSum);
    
    printf("\n");

    return 0;
}