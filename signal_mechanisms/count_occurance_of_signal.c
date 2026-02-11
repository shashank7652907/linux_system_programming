#define _POSIX_C_SOURCE 200809L


#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


//Using volatile so that compiler does not optimize
volatile int sigcount = 0;

void handler(int signum){
	sigcount++;
	
}


int main()
{
	int i;
	

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	
	sa.sa_handler   = handler;
	sigaction(SIGINT, &sa, NULL);

	
	for(i = 0; i < 10; i++)
	{
		printf("Hmmmmm\n");
		sleep(1);
	}
	printf("The signal has occured %d times\n ",sigcount);
	return 0;
}

