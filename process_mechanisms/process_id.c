#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int p_id = fork();
    if(p_id == 0) sleep(1);
    
    printf("ID of Current process is %d and Parent process is %d\n",
        getpid(),getppid());

    // Not required to check like if(p_id != 0) wait(NULL);
    // Because wait automatically checks for any child processes
    if(wait(NULL) == -1) printf("No children to wait for\n");
    else printf("%d finished execution\n",getpid());
    return 0;

}