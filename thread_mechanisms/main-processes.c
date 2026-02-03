#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char* argv[]){

    int x = 10;
    
    int pid = fork();
    if(pid == -1){
        perror("Fork failed");
        return 1;
    }

    if(pid == 0){
        //Child process only
        x++;
    }

    sleep(2);
    printf("X value is %d\n",x);



    printf("Process id : %d\n",getpid());

    if(pid != 0){
        //Parent process only
        wait(NULL);
    }

   

    return 0;
}
