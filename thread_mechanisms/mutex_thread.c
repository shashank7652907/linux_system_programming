#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t mutex;
// int lock = 0;

void* routine(){
    //read mail from mem (ld)
    //increment (add)
    //write mail to mem (st)

    for(int i = 0; i < 10000000; i++){
        // if(lock == 1){
        //     sleep(1);
        //     //Wait until lock is 0
        // }
        // lock = 1;
        // mails++;
        // lock = 0;

        //the below functions does all above
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

int main(int argc, char* argv[]){

    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);

    if(pthread_create(&t1, NULL, &routine, NULL)){
        perror("Create thread 1 : failed");
        return 1;
    }
    if(pthread_create(&t2, NULL, &routine, NULL)){
        perror("Create thread 2 : failed");
        return 2;
    }
    if(pthread_join(t1, NULL)){
        perror("Join thread 1 : failed");
        return 3;
    }
    if(pthread_join(t2, NULL)){
        perror("Join thread 2 : failed");
        return 4;
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails : %d\n",mails);
    
    return 0;
}
