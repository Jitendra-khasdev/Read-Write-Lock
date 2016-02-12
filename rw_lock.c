/*
 * Assigment 1: Creation of threads using pthread library.
 * Date : 10-Feb-2016
 *
 */
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "workqueue.h"

sem_t			mutex;
pthread_rwlock_t	rwlock;
int fd;
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
	char temp[7];
	pthread_rwlock_rdlock(&rwlock);
	lseek(fd, 0, SEEK_SET);
	if (read(fd, temp, sizeof(temp)) > 0)
		printf("Reader Thread : Data == %s\n", temp);
	else
		printf("Error while reading\n");
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
	lseek(fd, 0, SEEK_END);
	write(fd, "Writer", sizeof("Writer"));
	printf("Writer Thread : Data == %s\n", "Writer ");
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

	x:
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

	sleep(3);
	
	sem_wait(&mutex);
		if (count != 0) {
			sem_post(&mutex);
			goto x;
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


	/*Open a file*/
	fd = open("shared_resource.txt", O_CREAT | O_RDWR,  0644);

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

	/*Close Opened resource*/
	close(fd);
	return 0;
}

