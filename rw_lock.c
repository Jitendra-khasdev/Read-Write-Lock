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

void *master_thread(void *ptr)
{
	printf("Hello I am a thread\n");

}




/*Entry Point*/
int main()
{
	int num, val, i, n_thread;
	
	/*Create a work to store work item into memory*/
	struct work_queue_t *wq =  work_queue();

	/*Create a thread pool and assign a work_queue*/
	struct threadpool *tp = (struct threadpool *)malloc(sizeof(struct threadpool));
	tp->wq = wq;

	scanf("%d", &num);
	while (num--) {
		scanf("%d", &val);
		add_item(val, wq);
	}
	display(tp->wq);
	printf("\n");

	printf("Enter Number of Threads\n");
        scanf("%d", &n_thread);

        for (i = 0; i < n_thread; i++) {
                pthread_create(&(tp->threads[i]), NULL, master_thread, (void *)i);
        }

        for (i = 0; i < n_thread; i++) {
                pthread_join(tp->threads[i], NULL);
        }
	return 0;
}

