
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

// Wait() only cares about waiting for any child process to complete and returns their id
//Waitpid() cares about child process which we mention inside the function

int main(int argc, char* argv[]){
    int pid1 = fork();

    if(pid1 == -1){
        perror("Fork 1 failed");
        return 1;
    }

    if(pid1 == 0){
        //Child process 1
        sleep(4);
        printf("Finished execution : [%d]\n",getpid());

        return 0;

    }

    int pid2 = fork();
    if(pid2 == -1){
        perror("Fork 2 failed");
        return 2;
    }

    if(pid2 == 0){
        //Child process 2
        sleep(1);
        printf("Finished execution : [%d]\n",getpid());

        return 0;
    }

    //Parent process

    int pid1_result = waitpid(pid1, NULL, WNOHANG);
    printf("Waited for [%d]\n",pid1_result);

    int pid2_result = waitpid(pid2, NULL, WNOHANG);
    printf("Waited for [%d]\n",pid2_result);



    return 0;
}
