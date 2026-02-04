#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int stoveFuel[4] = {100, 100, 100, 100};
pthread_mutex_t mutexStove[4];

void* rouitne(void* arg){
    for(int i = 0; i < 4; i++){
        if(pthread_mutex_trylock(&mutexStove[i]) == 0){
            int fuelNeeded = rand() % 30;
            
            if(stoveFuel[i] - fuelNeeded < 0){
                printf("No more fuel .. going \n");
            }
            else{
                stoveFuel[i] -= fuelNeeded;
                sleep(1);
                printf("Fuel left %d\n",stoveFuel[i]);
            }
            pthread_mutex_unlock(&mutexStove[i]);
            break;
        }
        else {
            if (i == 3) {
                printf("No stove available yet, waiting...\n");
                sleep(1);
                i = 0;
            }
        }
     
    }
    pthread_exit(0);   
}


int main(int argc, char* argv[]){
    for(int i = 0; i < 4; i++){
        pthread_mutex_init(&mutexStove[i], NULL);
    }
    pthread_t th[10];
    for(int i = 0; i < 10; i++){
        if(pthread_create(&th[i], NULL, &rouitne, NULL) < 0){
            printf("Thread [%d] creation failed\n",i);
            return i + 1;
        }
    }

    for(int i = 0; i < 10; i++){
        if(pthread_join(th[i], NULL) < 0){
            printf("Thread [%d] join failed\n",i);
            return i + 11;
        }
    }
    for(int i = 0; i < 4; i++){
        pthread_mutex_destroy(&mutexStove[i]);
    }
    return 0;
}
