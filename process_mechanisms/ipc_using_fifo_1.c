#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {

    //Do "mkfifo sum" before in terminal
    int arr[5];
    srand(time(NULL));
    int i;
    for (i = 0; i < 5; i++) {
        arr[i] = rand() % 100;
        printf("Generated %d\n", arr[i]);
    }
    
    int fd = open("sum",O_WRONLY);
    if (fd == -1) {
        return 1;
    }
    
    if (write(fd, arr,  5 * sizeof(int)) == -1) {
        return 2;
    }
    
    close(fd);
    int sum;

    //Homework given by CodeVault
    //To read back sum from IPC_2

    int fd_1 = open("sum", O_RDONLY);

    if (read(fd_1, &sum, sizeof(sum)) == -1) {
            return 3;
    }

    close(fd_1);
    printf("Sum is %d\n",sum);
    
    return 0;
}