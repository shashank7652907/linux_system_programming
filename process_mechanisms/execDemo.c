#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    printf("My PID is : %d\n",getpid());

    /*With L : Comma seperated arguments
      With V : Vector (i.e an array of strings)
      With P : Include normal search for executable */

    char* args[] = {"./helloExec", "Hello", "World", NULL};
    
    execvp(args[0], args);

    printf("Goodbye World\n");
    

    return 0;
}