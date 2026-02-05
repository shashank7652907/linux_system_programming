#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

void* routine(void* arg){
    printf("%lu\n",pthread_self());
    // pthread_t is managed by the pthreads API, 
    //while gettid() returns an ID managed by the operating system
    printf("%d\n",(pid_t)(syscall(SYS_gettid)));
    pthread_exit(0);
}

int main(int argc, char* argv[]){
    //The pthread_t is actually an opaque data type as per pthrea api
    //So we can never say what data type it will be like char, long, int or a struct 

    pthread_t th[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) < 0){
            printf("Thread [%d] creation failed\n",i);
            return i + 1;
        }
        // printf("%lu : PTHREAD ID\n",th[i]);
    }
    for(int i = 0; i < THREAD_NUM; i++){
        if(pthread_join(th[i], NULL) < 0){
            perror("Thread join failed");
            return i + 3;
        }
    }
    
    return 0;
}