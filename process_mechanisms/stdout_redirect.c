#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1) {
        printf("Fork failed\n");
        return 1;
    }
    if(pid == 0){
        //Child process
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
        if(file == -1) return 3;
        printf("The fd to ping result is %d\n",file);

        //Standard file descriptors
        //ID        fd
        //0         STDIN
        //1         STDOUT
        //2         STDERR
        //3         new fd created by us
        //3 will be pingResults.txt here


        //0,1,2 fds will be open even before the program

        dup2(file, STDOUT_FILENO);
        //dup2() will close STDOUT completely and replace
        //it with pingResults.txt
        //ID        fd
        //0         STDIN
        //1         pingResults.txt
        //2         STDERR

        //So output from ping to stdout will be 

        close(file);

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


