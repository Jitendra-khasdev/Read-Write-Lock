/*
 * Assigment 1: Creation of threads using pthread library.
 * Date : 10-Feb-2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "workqueue.h"


void *print_message_function(void *ptr);
int counter = 0;

sem_t mutex, wrt;
int read_count = 0;


/*
 * Assume data variable is shared resource
 */
int data = 5;

/*
 * Reader function for reader thread
 *
 */

int reader(void *ptr)
{
	sem_wait(&mutex);
	read_count++;
	if (read_count == 1)
		sem_wait(&wrt);
	sem_post(&mutex);

	sleep(3);
	printf("Reader Thread : %d data == %d\n", (int)ptr, data);

	sem_wait(&mutex);
	read_count--;
	if (read_count == 0)
		sem_post(&wrt);
	sem_post(&mutex);
	return 0;
}

/*
 * Writer function for writer thread
 *
 */


int writer(void *ptr)
{
	sem_wait(&wrt);
	data++;
	printf("Writer Thread : %d data == %d\n", (int)ptr, data);
	sleep(2);
	sem_post(&wrt);
	return 0;
}

/*
 * Process thread
 *
 */

void *master_thread()
{





}




/*Entry Point*/
int main()
{
	int num, val;
	/*pthread_t thread[NTHREADS];
	int i, j, n_thread;

	sem_init(&mutex, 0, 1);
	sem_init(&wrt, 0, 1);

	printf("Enter Number of Threads\n");
	scanf("%d", &n_thread);

	for (i = 0; i < n_thread; i++) {
		pthread_create(&thread[i], NULL, master_thread, (void *)i);
	}

	for (i = 0; i < n_thread; i++) {
		pthread_join(thread[i], NULL);
	}
	
	printf("Modified data == %d\n", data);*/
	struct work_queue_t *wq =  work_queue();

	scanf("%d", &num);
	while (num--) {
		scanf("%d", &val);
		add_item(val, wq);
	}

	display(wq);

	printf("\n");
	return 0;
}

