#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 1

sem_t semaphore;

int* fuel;

void* routine(void* arg){
    *fuel += 50;
    printf("Fuel is at %d\n",*fuel);
    sem_post(&semaphore);
    return NULL;
}

int main(){
    pthread_t th[2];
    sem_init(&semaphore, 0, 0);
    fuel = malloc(sizeof(int));
    *fuel = 50;
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_create(&th[i], NULL, routine, NULL) != 0){
            perror("Thread creation failed");
        }
    }
    sem_wait(&semaphore);


    printf("Deallocating fuel\n");
    free(fuel);

    for(int i =0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed\n");
        }
    }

    return 0;
}
