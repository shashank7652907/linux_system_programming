#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* rollDice(){
    int value = (rand() % 6) + 1;
    int* result = (int *)malloc(sizeof(int));
    *result = value;
    printf("%p\n",result);
    
    return (void *)(result);
    pthread_exit(0);
}



int main(int argc, char* argv[]){
    int* res;
    pthread_t th;
    if(pthread_create(&th, NULL, &rollDice, NULL) == -1){
        perror("thread create failed");
        return 1;
    }

    if(pthread_join(th, (void **)&res) == -1){
        perror("Join failed");
        return 2;
    }
    printf("%p\n",res);

    printf("Val %d\n",*res);
    free(res);
    return 0;
}
