#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg)
{
	int i, res = 0; 

	/* Comment the line below to see the cancellation happening */
	//TODO 2: Disable the cancellation
	res = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	if (res != 0)
	{
		printf("Thread pthread_setcancelstate failed");
		pthread_exit(NULL);
	}
	printf("Thread_fuction is running\n");
	for(i = 0; i < 10; i++)
	{
		//Enable cancellation at i = 7
		if(i == 7){
			res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
			if (res != 0)
			{
				printf("Thread pthread_setcancelstate failed");
				pthread_exit(NULL);
			}
		}
		printf("Thread function is still running (%d) ...\n", i);
		sleep(1);
	}
	pthread_exit(NULL); // Never returns
}

int main()
{
	int res;
	pthread_t a_thread;
    
	res = pthread_create(&a_thread, NULL, &thread_function, NULL);
	if (res != 0)
	{
		printf("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	sleep(3);
	printf("Cancelling thread ...\n");
	//TODO 1: Cancel the thread
	res = pthread_cancel(a_thread);

	if (res != 0)
	{
		printf("Thread Cancellation failed");
		exit(EXIT_FAILURE);
	}
	pthread_join(a_thread, NULL);
	exit(EXIT_SUCCESS);
}

//Output :

/*Thread_fuction is running
Thread function is still running (0) ...
Thread function is still running (1) ...
Thread function is still running (2) ...
Cancelling thread ...
Thread function is still running (3) ...
Thread function is still running (4) ...
Thread function is still running (5) ...
Thread function is still running (6) ...
Thread function is still running (7) ...*/
