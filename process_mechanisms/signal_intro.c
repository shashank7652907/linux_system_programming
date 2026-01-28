#define _POSIX_C_SOURCE 200809L
//For errors in compiling 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

//For signals
#include <signal.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1) return 1;

    if(pid == 0){
        //Child process
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 50 * 1000 * 1000; // 50 ms
        int i = 1;
        while(1){
            
            printf("Something : %d \n",i);
            i++;
            nanosleep(&ts, NULL);
        }
    }
    else{
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}
