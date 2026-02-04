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
        fuel += 15;
        printf("Filling fuel ... %d\n",fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        //Doesnot senf that signal in while might be true
        //Sends signal telling that the value migh've changed
        //So that cond_wait checks again
        sleep(1);
    }

    pthread_exit(0);

}

void* car(void* arg){
   
    pthread_mutex_lock(&mutexFuel);

    while(fuel < 40){
        printf("No fuel../.. Waiting \n");
        pthread_cond_wait(&condFuel , &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    //Whenever signal comes from another thread
    //It checks the while condition again
    
    fuel -= 40;
    printf("Got fuel. Now left  %d\n",fuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_exit(0);

}

int main(int argc, char* argv[]){
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    pthread_t th[2];
    for(int i = 0; i < 2; i++){
        if(i == 1){
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

    for(int i = 0; i < 2; i++){
        if(pthread_join(th[i], NULL) == -1){
            printf("Thead [%d] join failed\n",i);
            return i + 3;
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}
