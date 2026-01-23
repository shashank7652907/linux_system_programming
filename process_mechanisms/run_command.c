#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1) {
        printf("Fork failed\n");
        return 1;
    }
    if(pid == 0){
        //Child process
        execlp("ping", "ping", "-c", "4", "google.com",NULL);
        printf("This should not get print\n");
    }
    else{
        wait(NULL);
        printf("Successful in running command\n");
        //Some post processing goes here
    }

    return 0;
}
