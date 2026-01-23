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
        int err = execlp("ping", "ping", "-c", "1", "google.com",NULL);
        if(err == -1){
            printf("Could not find program to execute\n");
            return 2;
        }
        printf("This should not get print\n");
    }
    else{
        //Parent process
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            int statusCode  = WEXITSTATUS(wstatus);
            if(statusCode == 0){
                printf("Successful \n");
            }
            else{
                printf("Failed with status code %d\n",statusCode);
            }
        }
        
        
        //Some post processing goes here
    }

    return 0;
}

