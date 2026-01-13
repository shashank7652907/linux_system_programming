#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>




void doSomeWork(char* name){
    const int NUM_TIMES = 5;
    for(int i = 0; i < NUM_TIMES; i++){
        sleep(rand() % 4);
        printf("Done pass %d for %s \n",i,name);
    }

}

int main(){

    printf("Now I am with process ID : %d\n",(int)getpid());
    
    
    pid_t pid = fork();
    srand((int)pid);

    printf("Fork Returned  : %d\n",(int)pid);

    if(pid < 0) perror("Fork Failed\n");
    else if(pid == 0) {
        printf("I am the child with pid %d\n",(int)getpid());
        doSomeWork("Child");
        exit(42);
    }

    //We must be the parent 
    printf("I am the parent waiting for child to end\n");
    doSomeWork("Parent");
    int status = 0;
    pid_t childPid = wait(&status);
    printf("Parent knows child %d ending with status %d\n",(int)childPid,status);
    int  childExitStatus = WEXITSTATUS(status);
    printf("The Return value is %d\n",childExitStatus);


    return 0;
}
