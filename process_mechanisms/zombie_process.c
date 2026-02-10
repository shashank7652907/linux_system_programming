#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == 0){
        printf("Child process\n");
    }

    else{
        sleep(5);
        //For those 5 seconds of sleep the child has become a zombie process
        //i.e its completed but parent has not collected its return value 
        //Not cleaned up by parent
        printf("Parent process\n");
        wait(NULL);
    }
    return 0;
}
