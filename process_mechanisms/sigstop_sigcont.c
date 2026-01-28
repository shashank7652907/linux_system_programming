#define _POSIX_C_SOURCE 200809L

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
        while(1){
            printf("Something\n");

            nanosleep(&ts, NULL);
        }
    }
    else{
        //Parent process
        kill(pid, SIGSTOP);
        int t;
        
        do{
            printf("Time in seconds for exection\n");
            scanf("%d",&t);

            if(t > 0){
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }


        }while(t > 0);

        kill(pid, SIGKILL);
        

        
        wait(NULL);
    }
 
    return 0;
}
