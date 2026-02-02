#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_SIZE 200


int main(int argc, char* argv[]){
    

    int pfd[2];

    if(pipe(pfd) == -1){
        perror("Pipe failed");
        return 1;
    }
    int pid = fork();
    if(pid == -1){
        perror("Fork failed");
        return 2;
    }

    if(pid == 0){
        //Child process
        char str[MAX_SIZE];
        printf("Input string : ");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';

        close(pfd[0]);

        int n = strlen(str) + 1;
        if(write(pfd[1], &n, sizeof(int)) == -1){
            perror("Write of length failed");
            return 4;
        }

        if(write(pfd[1], str, n * sizeof(char)) == -1){
            perror("Write of string failed\n");
            return 3;
        }

        close(pfd[1]);

    }

    else{
        //Parent process
        close(pfd[1]);
        char str[MAX_SIZE];

        int n;

        if(read(pfd[0], &n, sizeof(int)) == -1){
            perror("Read of len failed");
            return 5;
        }
        if(read(pfd[0], str, n * sizeof(char)) == -1){
            perror("Read of str failed");
            return 6;

        }

        printf("String is %s\n",str);

        close(pfd[0]);
        wait(NULL);
    }

    return 0;

}
