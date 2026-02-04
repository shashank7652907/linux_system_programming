#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

pthread_mutex_t mutex;


void* routine(){

    //Lock waits untill the mutex is unlocked
    //Try lock checks if or not there is a lock
    //if no lock it locks and executes the code locked (critical section)
    //returns 0 if lock is successfull
    //Else it returns !0 and executes error code we made
    if(pthread_mutex_trylock(&mutex) == 0){
        printf("Got lock \n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else{
        printf("Didnot get lock\n");
    }
    pthread_exit(0);
}


int main(int argc, char* argv[]){
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[4];
    for(int i = 0; i < 4; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) == -1){
            printf("Thread [%d] creation failed\n",i);
            return i + 1;
        }
    }

    for(int i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) == -1){
            printf("Thread [%d] join failed\n",i);
            return i + 6;
        }
    }
    return 0;
}
