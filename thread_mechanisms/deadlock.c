#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define THREAD_NUM 8


pthread_mutex_t mutexFuel;
int fuel = 0;

pthread_mutex_t mutexWater;
int water = 10;


void* routine(void* arg){

    //One thread has locked water  waiting to lock fuel
    //One thread has locked fuel waituing to lock water
    //Deadlock has occured
    if(rand() % 2 == 0){
        pthread_mutex_lock(&mutexFuel);
        sleep(1);
        pthread_mutex_lock(&mutexWater);
    }
    else{
        pthread_mutex_lock(&mutexWater);
        sleep(1);
        pthread_mutex_lock(&mutexFuel);
    }
    // pthread_mutex_lock(&mutexFuel);
    //Using mutex lock twice will create a deadlock
    //As the thread doesnot know it only locked the mutex
    //So it will wait untill the lock is unlocked 
    //Which it only locked previously
    //Deadlock has occured
    fuel += 50;
    water = fuel;
    printf("Fuel is now %d and set water to %d\n",fuel,water);
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexWater);
    
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_mutex_init(&mutexWater, NULL);
    pthread_t th[THREAD_NUM];
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
    printf("Water %d\n",water);
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&mutexWater);
    return 0;
}
