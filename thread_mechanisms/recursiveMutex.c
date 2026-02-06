#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define THREAD_NUM 8
#define _GNU_SOURCE  // For PTHREAD_MUTEX_RECURSIVE_NP

pthread_mutex_t mutexFuel;

int fuel = 0;


void* routine(void* arg){
    pthread_mutex_lock(&mutexFuel); 
    pthread_mutex_lock(&mutexFuel);
    pthread_mutex_lock(&mutexFuel);
    fuel += 50;
    printf("Incremented fuel to %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexFuel);
    //We have to unlock the mutex same no. of times
    //The same no. of times we locked it 
    //The same thread will lock the critical code twice
    //Using mutex beacuse of recursive mutex attribute

    //This recursive mutex attribute can be used 
    //In recursive funciton 
    
    return NULL;
}

int main(int argc, char* argv[]){
    
    pthread_t th[THREAD_NUM];
    pthread_mutexattr_t mutexRecursiveAttributes;
    pthread_mutexattr_init(&mutexRecursiveAttributes);
    pthread_mutexattr_settype(&mutexRecursiveAttributes, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&mutexFuel, &mutexRecursiveAttributes);
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_create(&th[i], NULL, routine, NULL) != 0){
            perror("Thread creation failed");
        }
    }
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed");
        }
    }
    printf("Fuel %d\n",fuel);
    pthread_mutexattr_destroy(&mutexRecursiveAttributes);
    pthread_mutex_destroy(&mutexFuel);
    return 0;
}

