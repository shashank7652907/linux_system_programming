#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        perror("Fork failed\n");
        return 1;
    }
    if(pid == 0){
        printf("Child process\n");
        sleep(10);
        //This will not get print right away as parent process
        //Has completed exectuion before child and has not wait for child
        //So parent terminates before child
        //Child becomes orphan process
        //Gets taken by systemd init
        //Now this below print statement will get executed
        printf("Child process is doing some work\n");
    }
    else{
        printf("Parent process\n");
        return 0;
    }
    return 0;
}