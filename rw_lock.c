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

sem_t			mutex;
pthread_rwlock_t	rwlock;

struct threadpool *tp = NULL;

/*
 * Assume data variable is shared resource
 */
int data = 5;

/*
 * Reader function for reader thread
 */
int reader()
{
	pthread_rwlock_rdlock(&rwlock);
	printf("Reader Thread : Data == %d\n", data);
	sleep(2);	
	pthread_rwlock_unlock(&rwlock);
	return 0;
}

/*
 * Writer function for writer thread
 */
int writer()
{
	pthread_rwlock_wrlock(&rwlock);
	data++;
	printf("Writer Thread : Data == %d\n", data);
	sleep(2);
	pthread_rwlock_unlock(&rwlock);
	return 0;
}

/*
 * Process thread
 */
void *master_thread(void *ptr)
{
	int op;
	printf("This is thread no : %d\n", (int)ptr);
	sem_wait(&mutex);
	op = remove_item(tp->wq);
	if (op != -1) {
		/*Call Read operation*/
		if (op == 1) {
			reader();
		}
		/*Call Write operation*/
		if (op == 0) {
			writer();
		}
	}
	sem_post(&mutex);
}

/*Entry Point*/
int main()
{
	int num, val, i, n_thread;
	
	/*Initialization of mutex*/
	sem_init(&mutex, 0, 1);
	
	/*Intialization of read-write lock*/
	pthread_rwlock_init(&rwlock, NULL);
	
	/*Create a work to store work item into memory*/
	struct work_queue_t *wq =  work_queue();

	/*Create a thread pool and assign a work_queue*/
	tp = (struct threadpool *)malloc(sizeof(struct threadpool));
	tp->wq = wq;

	/*Get the total number of reader writer*/
	scanf("%d", &num);
	while (num--) {
		scanf("%d", &val);
		add_item(val, wq);
	}

	/*Display the work items*/
	display(tp->wq);
	printf("\n");

	/*Get the number of threads*/
	printf("Enter Number of Threads\n");
        scanf("%d", &n_thread);

	/*Create threads*/
        for (i = 0; i < n_thread; i++) {
                pthread_create(&(tp->threads[i]), NULL, master_thread, (void *)i);
        }

	/*Hold till the threads terminate*/
        for (i = 0; i < n_thread; i++) {
                pthread_join(tp->threads[i], NULL);
        }
	/*Display the work items*/
	display(tp->wq);
	printf("\n");
	return 0;
}

