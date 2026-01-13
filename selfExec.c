
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    printf("Self Exec : My PID is : %d\n",getpid());

    if(argc != 2){
        printf("Pass atleast one argument as an integer\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    printf("n is %d..\n",n);

    if(n != 0){
        char nMinus1[10];
        sprintf(nMinus1, "%d", n-1);
        execl(argv[0],argv[0],nMinus1,NULL);
    }
    
    

    printf("Goodbye World\n");
    

    return 0;
}