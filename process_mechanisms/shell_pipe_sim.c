#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// $ ping -c 4 google.com | grep rtt
// rtt min/avg/max/mdev = 24.213/29.600/33.608/3.443 ms

int main(int argc, char* argv[]){
    int fd[2];
    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 1;
    }

    int pid1 = fork();
    if(pid1 == -1){
        perror("Fork - I failed");
        return 2;
    }
    if(pid1 == 0){
        //Child process 1 : ping
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        execlp("ping", "ping", "-c", "4", "google.com", NULL);
    }

    else{
        //Parent process
        int pid2 = fork();
        if(pid2 == -1){
            perror("Fork - II failed");
            return 3;
        }
        if(pid2 == 0){
            // Child process 2 : grep 
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);

            execlp("grep", "grep", "rtt", NULL);

        }

        //If we dont close both fds in parent
        //Grep executes infinitely beacause for pipe all should be closed
        close(fd[0]);
        close(fd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);

    }

    return 0;
}
