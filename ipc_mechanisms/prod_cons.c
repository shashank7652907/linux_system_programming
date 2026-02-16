#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

sem_t semJob;

struct job
{
    int data;
    struct job* next;
};

static struct job* job_queue;
static pthread_mutex_t mutex;

void random_sleep(int factor)
{
    int s;

    s = 1 + (int)((1.0 * rand() / RAND_MAX) * factor);
    sleep(s);
}

void process_job(struct job* next_job, long no)
{
    int id;

    id = (int)pthread_self();
    printf("\nConsumer %ld (%u) finished job %d\n", no, id, next_job->data);
    random_sleep(1);
}

void *consumer(void *arg)
{
    struct job *next_job;

    while (1)
    {
        //Waiting before locking
        //Because if we lock and then wait then we run into
        //Dead lock situation where we already locked it at 0 
        //Then waiting for it to become 1
        sem_wait(&semJob);
		pthread_mutex_lock(&mutex);
        if (job_queue == NULL)
            next_job = NULL;
        else
        {
            next_job = job_queue;
            job_queue = job_queue->next;
        }
		pthread_mutex_unlock(&mutex);

        if (next_job == NULL)
            break;
        process_job(next_job, (long)(arg));
        free(next_job);
    }
    printf("\nThread %ld Done.\n", (long)(arg));
    return NULL;
}

void enqueue_job(void)
{
    static int i = 0;
    struct job *new_job;

    new_job = (struct job *)malloc(sizeof(struct job));
    new_job->data = i++;

	pthread_mutex_lock(&mutex);
    new_job->next = job_queue;
    job_queue = new_job;
	pthread_mutex_unlock(&mutex);

    printf("\nJob no %d is added.\n", i - 1);
}
void *producer(void *arg)
{
    while (1)
    {
        enqueue_job();
        sem_post(&semJob);
        random_sleep(4);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t th_id1, th_id2, th_prod;
	pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < 6; i++) // Put some jobs to start with
    {
        enqueue_job();
    }
    //Keeping initial value as 6 becuase we already enquued 6 jobs
    //If we didnot then we should keep this as 0
    sem_init(&semJob, 0, 6);
    pthread_create(&th_id1, NULL, &consumer, (void *)(1L));
    pthread_create(&th_id2, NULL, &consumer, (void *)(2L));
    pthread_create(&th_prod, NULL, &producer, NULL);

    pthread_join(th_prod, NULL);

    return 0;
}

