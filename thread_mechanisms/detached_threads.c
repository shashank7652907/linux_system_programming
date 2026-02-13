#include <stdio.h>
#include <pthread.h>

void* thread_function(void* thread_arg)
{
	int i = 10;

	/* Do work here... */
	while (i--)
	{
		printf("Thread Working\n");
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_attr_t attr;
	pthread_t thread;

	// 1: Initialize the attribute object
	pthread_attr_init(&attr);

	// 2: Modify attribute to set the state to PTHREAD_CREATE_DETACHED
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	// 3: Create the thread with above attribute
	if(pthread_create(&thread, &attr, thread_function, NULL) != 0){
		perror("Thread creation failed");
		return 1;
	}
	
	/* Do work here... */

	//Tried joining threads but we they cant be joined as they are detached threads
	if(pthread_join(thread, NULL) != 0){
		perror("Thread join failed");
		return 2;
	}
	// 4: De-Initialize the attribute object
	pthread_attr_destroy(&attr);
	while (1)
	{
		printf("Process Working\n");
		sleep(2);
	}
	return 0;
}
