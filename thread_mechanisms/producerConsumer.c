#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define THREAD_NUM 8

sem_t semEmpty;
sem_t semFull;

int buffer[10];
int count = 0;

pthread_mutex_t mutexBuffer;

void* producer(void* args){
    while(1){
        //Produce 
        int x = rand() % 100;
        sleep(1);
        
        
        //Add to buffer
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
        
    }
    return NULL;
}

void* consumer(void* args){
    while(1){
        //Remove from buffer
        sem_wait(&semFull);
        int x;
        pthread_mutex_lock(&mutexBuffer);
        x = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        //Consume
        printf("Got number %d\n",x);
        // sleep(1);
        
    }
    return NULL;
}




int main(int argc, char* argv[]){
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    for(int i = 0; i < THREAD_NUM; i++){
        if(i > 0){
            if(pthread_create(&th[i], NULL, producer, NULL) != 0){
                perror("Thread creation failed");
            }
        }
        else{
            if(pthread_create(&th[i], NULL, consumer, NULL) != 0){
                perror("Thread creation failed");
            }
        }
    }

    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed");
        }
    }
    pthread_mutex_destroy(&mutexBuffer);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    return 0;
}


