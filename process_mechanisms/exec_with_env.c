#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main(int argc,char* argv[]){
    
    //exec*p : P defines fined path of file given

    // execv : V denotes put arguments in a vector / array

    char* arr[] = {
        "ping",
        "google.com",
        NULL
    };

    execvp("ping",arr);

    //execl : L denotes list arguments

    execl("/usr/bin/ping",
        "ping",
        "-c",
        "4",
        "google.com",
        NULL
    );

    //exec*e : E denotes environment,
    //variables used for error checking

    char* env[] = {
        "TEST=environment variables",
        NULL
    };


    execve("/usr/bin/pings",arr,env);

    // If we reach here, exec failed
    perror("execve");
    printf("errno = %d\n", errno);

    //mess up path in exec to print below message
    printf("This will not get printed\n"); 
    printf("Unless we messup exec function\n");
    return 0;
}
