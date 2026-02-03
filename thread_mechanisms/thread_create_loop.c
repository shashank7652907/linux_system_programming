#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 8

int mails = 0;
pthread_mutex_t mutex;


void* routine(){
    for(int i = 0; i < 10000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

int main(int argc, char* argv[]){

    pthread_t t[MAX_THREADS];

    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < MAX_THREADS; i++){
        if(pthread_create(t + i, NULL, &routine, NULL)){
            printf("Creation of thread [%d] failed\n",i);
            return i+1;
        }
        printf("Thread [%d] started\n",i);
    }

    for(int i = 0; i < MAX_THREADS; i++){
        if(pthread_join(t[i], NULL)){
            printf("Join thread [%d] failed\n",i);
            return i+7;
        }
        printf("Thread [%d] ended\n",i);
    }

    pthread_mutex_destroy(&mutex);

    printf("Number of mails : %d\n",mails);
    
    return 0;
}

