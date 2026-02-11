#define _POSIX_C_SOURCE 200809L


#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


volatile int sigcount = 0;

void handler(int signum){
	sigcount++;
	printf("Signal is handled");
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
		if(sigcount >= 1){
			sa.sa_handler = SIG_IGN;
			sigaction(SIGINT, &sa, NULL);
		}
		printf("Hmmmmm\n");
		sleep(1);
	}
	return 0;
}

