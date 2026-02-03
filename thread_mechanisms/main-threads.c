#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 10;

void* routine(){
    x++;
    sleep(2);
    printf("X value is %d\n",x);
    printf("Process id : %d\n",getpid());
    pthread_exit(0);
}

void* routine2(){
    //Even though we donot increment,
    //This prints x as 3 beacuse both threads share 
    //same address space unlike processes
    sleep(2);
    printf("X value is %d\n",x);
    printf("Process id : %d\n",getpid());
    pthread_exit(0);
}


int main(int argc, char* argv[]){
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL, &routine, NULL)){
        perror("Thread creation failed : 1");
        return 1;
    }
    if(pthread_create(&t2, NULL, &routine2, NULL)){
        perror("Thread creation failed : 2");
        return 1;
    }
    if(pthread_join(t1, NULL)){
        perror("Thread join failed : 1");
        return 2;
    }
    if(pthread_join(t2, NULL)){
        perror("Thread join failed : 2");
        return 2;
    }

    return 0;
}