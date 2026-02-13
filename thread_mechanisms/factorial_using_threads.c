#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct fact_params
{
	int count;
};

void *fact(void *parameters)
{
	int i;
	int* factorial = malloc(sizeof(int));
	*factorial = 1;
	struct fact_params* pp = (struct fact_params*)parameters;

	if (pp->count != 0)
	{
		for (i = 1; i <= pp->count; i++)
			(*factorial) = (*factorial) * i;
	}
	return (void *)factorial;
}

int main()
{
	int n;
	int* p;
	pthread_t thread_id;
	struct fact_params thread_args;
	
	printf("Enter a number: ");
	scanf("%d", &n);
	thread_args.count = n;

	if(pthread_create(&thread_id, NULL, fact, &thread_args) != 0){
		perror("Thread creation failed");
		return 1;
	}
	

	if(pthread_join(thread_id, (void **)&p) != 0){
		perror("Thread join failed");
		return 2;
	}
	printf("Factorial = %d\n", *p);
	free(p);

	return 0;
}

