#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    //fifo pipe also known as named pipe
    if(mkfifo("myfifo1",0777) == -1){
        if(errno != EEXIST){
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    printf("Opening..\n");
    //O_WRONLY : open only for write only
    //here as we are opening only for write only
    //the open halts the writing process
    //Untill we open the file for read only 
    //So use cat myfifo1 to read from another terminal
    //Or use O_RDWR for both opening read & write
    int fd = open("myfifo1",O_WRONLY);
    if(fd == -1) return 3;
    printf("Opened\n");

    int x = 65;

    if(write(fd, &x, sizeof(x)) == -1) return 2;
    printf("Written\n");

    close(fd);
    printf("Closed\n");
    //Read open manual for clear info

    return 0;
}
