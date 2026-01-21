#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// libraries for wait
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int p_id = fork();
    int n;
    // Different n for child and parent processes
    if(p_id == 0) n = 1;
    else n = 6;
    //Waits untill child is completd 
    //Wait should have some argument so NULL
    if(p_id != 0) wait(NULL); 
    for(int i = n;i < n + 5; i++) printf("%d ",i);
    // Prints new line only while in Parent process
    if(p_id != 0) printf("\n");
    return 0;



}
