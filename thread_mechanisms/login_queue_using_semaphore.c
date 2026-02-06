#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

sem_t loginSemaphore;

#define THREAD_NUM 16

void* routine(void* args){
    printf("[%d] thread wating for login..\n",*(int *)args);
    sem_wait(&loginSemaphore);
    printf("[%d] Logged in\n",*(int *)args);
    sleep(rand() % 5 + 1);
    printf("[%d] Logged out\n",*(int *)args);
    sem_post(&loginSemaphore);
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t th[THREAD_NUM];
    sem_init(&loginSemaphore, 0, 2);
    //So essentially semaphores are used to limiting access
    //To a resource for a limited no of threads or users

    int i;
    for(i = 0; i < THREAD_NUM; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], NULL, routine, a) != 0){
            perror("Thread creation failed");
        }
    }

    for(i = 0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Thread join failed");
        }
    }
    sem_destroy(&loginSemaphore);
    return 0;
}