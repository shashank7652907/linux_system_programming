#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//The sum computed by the background thread
struct sum_runner_struct{
    long long limit;
    long long answer;
};

//Thread fucntion to generate sum fro 0 to N
void* sum_runner(void* arg){
    struct sum_runner_struct* argc_struct =
        (struct sum_runner_struct*)arg;
    
    long long sum = 0;

    
    for(long long i = 0; i <= argc_struct->limit; i++){
        sum += i;
    }

    argc_struct->answer = sum;
    
    pthread_exit(0);
}


int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage %s <num0>  <num1> <num2> .... <num(n-1)> \n",argv[0]);
        exit(-1);
    }

    pthread_t tids[argc -1];

    struct sum_runner_struct args[argc - 1];

    //Launch threads
    for(int i = 0; i < argc -1; i++){
        
        args[i].limit = atoll(argv[i + 1]);

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, sum_runner, &args[i]);

    }



    //Wait untill thread is done its work
    for(int i = 0; i < argc - 1; i++ ){
        pthread_join(tids[i] , NULL);
        printf("Sum for thread %d  is %lld\n"
            ,i,args[i].answer);

    }
    

    

}

