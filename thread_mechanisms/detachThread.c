#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define THREAD_NUM 2

void* routine(void* arg){
    sleep(1);
    printf("Finished execution\n");
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t th[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_create(&th[i], NULL, routine, NULL) != 0){
            perror("Creation thread failed");
        }
        pthread_detach(th[i]);
    }

    // for(int i = 0; i < THREAD_NUM; i++){
    //     if(pthread_join(th[i], NULL) != 0){
    //         printf("Thread [%d] join failed\n",i);
    //     }
    // }
    pthread_exit(0);
    //As we used pthread exit here 
    //The main thread will be finished 
    //But threads will run
    //So first we will get thread join failed twice
    //Then after sleep of 1 sec
    //We get Finished executin twice
    //Even tho we detached the threads from main process
    //Even for normal joinable threads, execution starts immediately after pthread_create().
    //pthread_join() only blocks the main thread until the worker thread finishes; 
    //it does not cause the thread to execute.
}