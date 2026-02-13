#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int main(){
    pthread_attr_t thread_attr;
    struct sched_param sp;
    int  i;
    if(pthread_attr_init(&thread_attr) != 0){
        perror("Thread attr init failed");
        return 6;
    }

    if(pthread_attr_getschedpolicy(&thread_attr, &i) != 0){
        perror("Thread policy get  failed");
        return 1;
    }
    printf("Scheduling policy   = %s\n",
                   (i == SCHED_OTHER) ? "SCHED_OTHER" :
                   (i == SCHED_FIFO)  ? "SCHED_FIFO" :
                   (i == SCHED_RR)    ? "SCHED_RR" :
                   "???");  
    
    if(pthread_attr_getschedparam(&thread_attr, &sp) != 0){
        perror("Thread param get failed");
        return 2;
    }
    printf("Scheduling priority = %d\n",sp.sched_priority);

    if(pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO) != 0){
        perror("Thread policy set failed");
        return 3;
    }
    pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);
    
    if(pthread_attr_getschedpolicy(&thread_attr, &i) != 0){
        perror("Thread policy get  failed");
        return 1;
    }
    printf("Scheduling policy   = %s\n",
                   (i == SCHED_OTHER) ? "SCHED_OTHER" :
                   (i == SCHED_FIFO)  ? "SCHED_FIFO" :
                   (i == SCHED_RR)    ? "SCHED_RR" :
                   "???");  

    // IMPORTANT: Explicit scheduling
    //If we dont use below line the scheduler will not inherit policy set by us
    pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);


    sp.sched_priority = 10;
    if(pthread_attr_setschedparam(&thread_attr, &sp) != 0){
        perror("Thread param set failed");
        return 4;
    }

    printf("Scheduling priority = %d\n",sp.sched_priority);


    if(pthread_attr_destroy(&thread_attr)!= 0 ){
        perror("Thread attr destroy failed");
        return 9;

    }
    return 0;
}
