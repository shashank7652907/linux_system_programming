#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

//2 processes
//Child process should generate random numbers and send to parent
//Parent is going to sum all the results and print the result


int main(int argc, char* argv[]){
    int fd[2];

    if(pipe(fd) == -1){
        perror("Pipe failed");
        return 2;
    }

    int pid = fork();
    
    if(pid == -1){
        perror("Fork failed");
        return 1;
    }

    if(pid == 0){
        close(fd[0]);
        // Child process
        int arr[10];
        int n , i;
        srand(time(NULL));
        n = rand() % 10  + 1;
        printf("Generated :");
        for(i = 0; i < n; i++){
            arr[i] = rand() % 11;
            printf("%d ",arr[i]);
        }

        if(write(fd[1], &n, sizeof(int)) == -1){
            perror("Write of n failed");
            return 4;
        }

        printf("\nSent n is %d\n",n);

        if(write(fd[1], arr, n * sizeof(int)) == -1){
            perror("Writing array failed");
            return 3;
        }

        close(fd[1]);

        printf("Array is sent\n");
        
    }

    else{
        //Parent process
        close(fd[1]);
        int arr[10];
        int n, i , sum = 0;

        if(read(fd[0], &n, sizeof(int)) == -1){
            perror("Reading of n failed");
            return 5;
        }

        printf("Recieved n is %d\n",n);

        if(read(fd[0], arr, n * sizeof(int)) == -1){
            perror("Reading arr failed");
            return 6;
        }
        printf("Array is recieved\n");
        close(fd[0]);

        for(i = 0; i < n; i++){
            sum += arr[i];
        }

        printf("Sum of arr is %d\n",sum);

        


        wait(NULL);
    }

    return 0;

}
