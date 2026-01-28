#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int x;

void handle_sigusr1(int sig){
    if(x == 0){
        printf("\nHint : MUltiplication is repititive additon\n");
    }
}

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1) return 1;
    if(pid == 0){
        //Child process
        sleep(5);
        kill(getppid(),SIGUSR1);
    }
    else{
        //Parent Process

        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);


        
        printf("What is 5 * 3 : ");
        scanf("%d",&x);
        if(x == 15) printf("Right !\n");
        else printf("Wrong !\n");
    }
    wait(NULL);

    return 0;
}
