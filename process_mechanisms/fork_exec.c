#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 8

int main(int argc, char *argv[]){
    for(int i = 0; i < NUM_CHILDREN; i++){
        pid_t pid = fork();
        if(pid < 0){
            perror("Fork failed .. \n");
            exit(1);
        }
        else if(pid == 0){
            //Child now exec's
            char* args[] = {"./bogosort" ,
                            "99","22","1","2","3","54","11",
                            "94","67","42","83",
                            NULL
            };
            execv(args[0], args);

            printf("Never going to see this .. \n");
        }
    }

    //Parent 
    // we can do clever processing here 
    printf("Parent is doing something interesting ..\n");


    //Parent waiting for child 
    printf("Parent is waiting for child  ..\n");
    for(int i = 0; i < NUM_CHILDREN; i++){
        wait(NULL);
    }



    return 0;
}
