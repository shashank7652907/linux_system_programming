#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define NUM_OF_THREADS 4

sem_t semaphore;

void* routine(void* arg){
    int index = *(int *)arg;
    int semVal;
    sem_wait(&semaphore);
    sleep(index + 1);
    sem_getvalue(&semaphore, &semVal);
    printf(" In [%d] semaphore value after wait is %d\n",index,semVal);
    sem_post(&semaphore);
    sem_getvalue(&semaphore, &semVal);
    printf(" In [%d] semaphore value after post is %d\n",index,semVal);
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t th[NUM_OF_THREADS];
    sem_init(&semaphore, 0, 4);
    for(int i = 0; i < NUM_OF_THREADS; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, &routine, a) != 0){
            perror("Thread creation failed");
        }
    }

    for(int i = 0; i < NUM_OF_THREADS; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed");
        }
    }
    return 0;
}
