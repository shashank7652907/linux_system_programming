#define _XOPEN_SOURCE 600

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_barrier_t barrier;

void* routine(void* arg){
    while(1){
        printf("Waiting at the barrier \n");
        sleep(1);
        pthread_barrier_wait(&barrier);
        printf("We passed the barrier\n");
        sleep(1);
    }

    pthread_exit(0);

}

int main(int argc, char* argv[]){
    
    pthread_t th[10];
    pthread_barrier_init(&barrier, NULL,7);

    for(int i = 0; i < 9; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) < 0){
            printf("Thread [%d] creation failed\n",i);
            return i + 1;
        }
    }

    for(int i = 0; i < 9; i++){
        if(pthread_join(th[i], NULL) == -1){
            printf("Thread [%d] join failed\n",i);
            return i + 9;
        }
    }
    pthread_barrier_destroy(&barrier);


    return 0;


}
