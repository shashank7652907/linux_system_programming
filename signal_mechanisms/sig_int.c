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
	
	//We are ignorig the signal using SIG_IGN
	sa.sa_handler   = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	
	for(i = 0; i < 20; i++)
	{
		printf("Hmmmmm\n");
		if(i == 5){
			//We are restoring it again to default 
			//Using SIG_DFL
			sa.sa_handler = SIG_DFL;
			sigaction(SIGINT, &sa, NULL);
		}
		sleep(1);
	}
	return 1;
}

