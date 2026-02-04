#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* rollDice(){
    int value = (rand() % 6) + 1;
    int* result = (int *)malloc(sizeof(int));
    *result = value;
    printf("Thread result :%d\n",*result);
    
    pthread_exit((void *)(result));
}



int main(int argc, char* argv[]){
    int* res;
    pthread_t th;
    if(pthread_create(&th, NULL, &rollDice, NULL) == -1){
        perror("thread create failed");
        return 1;
    }
    //This starts the main thread
    //But as we use pthread_exit() here the main program exits
    //But wait for all other threads to finish
    //But if we use return 0 , it ends main program and 
    //Kills all the threads
    pthread_exit(0);
    
    if(pthread_join(th, (void **)&res) == -1){
        perror("Join failed");
        return 2;
    }

    printf("Val %d\n",*res);
    free(res);
    return 0;
}


