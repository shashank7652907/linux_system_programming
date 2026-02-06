#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h> //For semaphore

#define THREAD_NUM 4

sem_t semaphore;

void* routine(void* arg){
    sem_wait(&semaphore);
    sleep(1);
    printf("Thread id is %d\n",*(int *)arg);
    sem_post(&semaphore);
    free(arg);
    return NULL;

    //Internally
    // V(S)
    // sem_wait(sem_t s){
    //     if(s == 0){
    //         while(1);
    //     }
    //     s--;
    // }

    // P(S)
    // sem_post(sem_t s){
    //     s++;
    // }
}

int main(int argc, char* argv[]){
    sem_init(&semaphore, 0, 5);
    //The inital value of S here denotes how many threads can execute the critical section
    //Unlike mutex where only one thread can execute critical section at a time
    //Seamphiore intial value determines how many threads can start execution of critical section at once
    //Here 2 is given so 2 threads at a time
    //Even if S > THREAD_NUM it executes 4 threads and then joins to main
    //Unlike mutexes, semaphores can allow multiple threads to access a critical section concurrently,
    // depending on the initial value of the semaphore
    //With mutex we can only lock one thread at a time 
    //Or with recursive mutex we can lock same 1 thread twice
    //But we cannot lock multiple threads at a time using same lock
    pthread_t th[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        int* a = (int *)malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, routine, a) != 0){
            perror("Thread creation failed");
        }
    }
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed");
        }
    }
    sem_destroy(&semaphore);
    return 0;
}
