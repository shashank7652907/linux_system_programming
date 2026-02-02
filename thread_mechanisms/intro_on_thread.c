#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* routine(){
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
    pthread_exit(0);
}


int main(int argc, char* argv[]){

    //Declare a varible to store info of thread
    //Variable type is pthread

    pthread_t t1, t2;

    if(pthread_create(&t1, NULL, &routine, NULL) != 0){
        perror("thread 1 failed");
        return 1;
    }
    if(pthread_create(&t2, NULL, &routine, NULL) != 0){
        perror("thread 2 failed");
        return 2;
    }

    if(pthread_join(t1, NULL) != 0){
        perror("Join thread 1 failed");
        return 4;
    }
    if(pthread_join(t2, NULL) != 0){
        perror("Join thread 2 failed");
        return 5;
    }
    return 0;

    
}
