#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char* argv[]){
    int fd[3][2];
    for(int i = 1; i <= 3; i++){
        if(pipe(fd[i-1]) == -1){
            perror("Pipe   failed\n");
            return i;
        }
    }

    int pid1 = fork();
    if(pid1 == -1){
        perror("Fork 1 failed");
        return 4;
    }

    if(pid1 == 0){
        // Child process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);

        int x;

        if(read(fd[0][0], &x, sizeof(int)) == -1){
            perror("Read in child 1 failed");
            return 5;
        }

        x += 5;

        if(write(fd[1][1], &x, sizeof(int)) == -1){
            perror("Write in child 1 failed");
            return 6;
        }

        close(fd[0][0]);
        close(fd[1][1]);
        
        return 0;
    }


    
    int pid2 = fork();

    if(pid2 == -1){
        perror("Fork 2 failed");
        return 7;
    }

    if(pid2 == 0){
        //Child 2 process

        int x;

        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        if(read(fd[1][0], &x, sizeof(int)) == -1){
            perror("Read in child 2 failed");
            return 8;
        }
        x += 5;

        if(write(fd[2][1], &x, sizeof(int)) == -1){
            perror("Write in child 2 failed");
            return 9;
        }

        close(fd[1][0]);
        close(fd[2][1]);


        return 0;

    }
    //Parent process

    int x = 0;

    
    
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);

    if(write(fd[0][1], &x, sizeof(int)) == -1){
        perror("Write in parent failed");
        return 10;
    }

    if(read(fd[2][0], &x, sizeof(int)) == -1){
        perror("Read in parent failed");
        return 11;
    }

    

    printf("Result is %d\n", x);

    close(fd[0][1]);
    close(fd[2][0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    


    return 0;
}
