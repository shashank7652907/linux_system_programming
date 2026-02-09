#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define NUM_OF_THREADS 2

pthread_mutex_t fuelMutex;
sem_t fuelSemaphore;

int fuel = 50;

void* routine1(void* args){
    while(1){
        sem_wait(&fuelSemaphore);
        //Instead if we use mutex lock here 
        //The program will crash after few entries
        //Becuase unlike semaphore mutex has ownership
        //Whenever a mutex is locking a section
        //The mutex expects the section to be unlocked by same thread
        // pthread_mutex_lock(&fuelMutex);
        fuel += 50;
        printf("Fuel is at %d\n",fuel);  
    }
    return NULL;
}
void* routine2(void* args){
    while(1){
        sem_post(&fuelSemaphore);
        // pthread_mutex_unlock(&fuelMutex);
        usleep(50000);

    }
    return NULL;

}

int main(int argc, char* argv[]){
    pthread_t th[NUM_OF_THREADS];
    pthread_mutex_init(&fuelMutex, NULL);
    sem_init(&fuelSemaphore, 0, 1);
    for(int i = 0; i < NUM_OF_THREADS; i++){
        if(i % 2 == 0){
            if(pthread_create(&th[i], NULL, &routine1, NULL) != 0){
                perror("Thread creation failed");
            }
        }
        else{
            if(pthread_create(&th[i], NULL, &routine2, NULL) != 0){
                perror("Thread creation failed");
            }
        }
    }

    for(int i = 0; i < NUM_OF_THREADS; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed");
        }
    }
    return 0;
}
