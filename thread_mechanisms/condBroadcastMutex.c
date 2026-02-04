#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int fuel = 0;
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

void* fuel_filling(void* arg){
    
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&mutexFuel);
        fuel += 60;
        printf("Filling fuel ... %d\n",fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel);
        //Instead of signal if we use broadcast 
        //This signals all the threads 
        //Instead of only one thread
        sleep(1);
    }

    pthread_exit(0);

}

void* car(void* arg){
   
    pthread_mutex_lock(&mutexFuel);

    while(fuel < 40){
        printf("No fuel../.. Waiting \n");
        pthread_cond_wait(&condFuel , &mutexFuel);
    }
    
    fuel -= 40;
    printf("Got fuel. Now left  %d\n",fuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_exit(0);

}

int main(int argc, char* argv[]){
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    pthread_t th[5];
    for(int i = 0; i < 5; i++){
        if(i == 4){
            if(pthread_create(&th[i], NULL, &fuel_filling, NULL) == -1){
                printf("Thread [%d] creation failed\n",i);
                return i + 1;
            }
        }
        else{
            if(pthread_create(&th[i], NULL, &car, NULL) == -1){
                printf("Thread [%d] creation failed\n",i);
                return i + 1;
            }

        }
    }

    for(int i = 0; i < 5; i++){
        if(pthread_join(th[i], NULL) == -1){
            printf("Thead [%d] join failed\n",i);
            return i + 3;
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}

