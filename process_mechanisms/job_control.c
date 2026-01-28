#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

void handler_sigstp(int sig){
    printf("Stop not allowed\n");
}

int main(int argc, char* argv[]){


    struct sigaction sa;
    sa.sa_handler = &handler_sigstp;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa, NULL);


    //We can use this signal function
    //But read manual page of signal of why we don't
    //Issue : portability
    //So please read man page of signal
    // signal(SIGTSTP, &handler_sigstp);
    

    int x;
    printf("Enter number :");
    scanf("%d",&x);
    printf("Result %d*5 : %d\n",x,x*5);

    return 0;
}
