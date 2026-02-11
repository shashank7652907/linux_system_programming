#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int agrc, char* argv[]){
    int pid = vfork();
    if(pid == 0){
        printf("Child process\n");
        _exit(0);

        //If we use return 0 we get 
        // Child process
        // Parent process
        // *** stack smashing detected ***: terminated
    }

    else{
        printf("Parent process\n");
        waitpid(&pid, NULL, WNOHANG);
    }
    return 0;
}
