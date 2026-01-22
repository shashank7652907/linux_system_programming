#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    //File descriptors 
    int fd[2];
    //fd[0] : read
    //fd[1] : write

    if(pipe(fd) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }
    int id = fork();
    if(id == -1){
        printf("An error occured with fork\n");
        return 4;
    }
    if(id == 0){
        close(fd[0]);
        int x;
        printf("Input a number : 0x");
        scanf("%x",&x);
        if(write(fd[1],&x,sizeof(int)) == -1){
            printf("An error occured while writing to the pipe\n");
            return 2;
        }
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int y;
        if(read(fd[0],&y,sizeof(char)) == -1){
            printf("An error occured while reading from  the pipe\n");
            return 3;
        }
        close(fd[0]);
        printf("Last byte  from child process : 0x%x\n",y);
    }
}
