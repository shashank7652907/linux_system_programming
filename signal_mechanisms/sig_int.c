#define _POSIX_C_SOURCE 200809L


#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signum){
	printf("Signal is handled\n");
}


int main()
{
	int i;

	struct sigaction sa;
	//We are populaitng the whole sa struct with 0
	//So that no value is set or reset
	memset(&sa, 0, sizeof(sa));
	
    //We are using handler function to replace sigint
    sa.sa_handler   = handler;
	sigaction(SIGINT, &sa, NULL);
	
	for(i = 0; i < 20; i++)
	{
		printf("Hmmmmm\n");
		sleep(1);
	}
	return 1;
}

