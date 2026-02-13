#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/* The key used to associate a log file pointer with each thread.  */
static pthread_key_t thread_log_key;

/* Write message to the log file for the current thread.  */
void read_from_thread(int thread_num)
{
	//TODO 4: Get the pointer to the allocated
	char* data;
	data = pthread_getspecific(thread_log_key);
    if(!data){
        perror("Get specific data failed");
        pthread_exit(0);
    }
	
	printf("The data from thread %d is %s\n", thread_num, data);
}
/* Close the log file pointer THREAD_LOG.  */
void free_data(void *arg)
{
	//TODO 5: Free up the allocated space
	char* data = (char *)arg;
	printf("%s freeing\n", data);
	free(data);
}
void *thread_function(void *arg)
{
	int thread_num = (int)(long)(arg);
	char *data;
	int i,res;

	// TODO 2: Allocate the memory for 20 bytes and assign it to data
	data = malloc(20 * sizeof(char));
	if(!data){
		perror("Malloc failed");
		pthread_exit(0);
	}

	// TODO 3: Store pointer to the allocated space in thread specific data area
	res = pthread_setspecific(thread_log_key, data);
	if(res != 0){
		perror("Thread set specific key failed");
		pthread_exit(0);
	}

	/* Do work here ... */
	for (i = 0; i < 2 * thread_num; i++)
	{
		read_from_thread(thread_num);
		sleep(5 / thread_num);
	}
	printf("%d: done\n", thread_num);
	return NULL;
}

int main()
{
	int i, res;
	pthread_t threads[5];

	//1: Create a key for thread specific data
	// Use free_data as cleanup handler
	res = pthread_key_create(&thread_log_key, free_data);
	if(res != 0){
		perror("Key creation failed");
		return 2;
	}
	

	/* Create threads to do the work */
	for (i = 0; i < 5; ++i)
		pthread_create(&(threads[i]), NULL, &thread_function, (void *)(long)(i + 1));
	/* Wait for all threads to finish. */
	for (i = 0; i < 5; ++i)
		pthread_join(threads[i], NULL);

	/* Delete the key */
	// TODO 6: Free up the thread specific key with pthread_key_delete
    res = pthread_key_delete(thread_log_key);
    if(res != 0){
        perror("Thread key destroy failed");
        return 3;
    }

	return 0;
}

