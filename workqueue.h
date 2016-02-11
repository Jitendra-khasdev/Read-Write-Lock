#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>

#define NTHREADS 100


struct work_item {
	struct work_item *next;
	int operation;
};


struct work_queue_t {
	struct work_item *front;
	struct work_item *rear;
};



struct threadpool {
	pthread_t threads[NTHREADS];
	struct work_queue_t *wq;     
};


struct work_item *make_item()
{
	struct work_item *temp = (struct work_item *)malloc(sizeof(struct work_item));
	if (temp == NULL)
		return NULL;
	return temp;
}

int add_item(int op, struct work_queue_t *wq)
{

	struct work_item *add_temp = make_item();
	
	if (add_temp == NULL)
		return -1;

	add_temp->operation = op;
	add_temp->next = NULL;

	if (wq->rear == NULL) {
		wq->rear = add_temp;
		wq->front = wq->rear;	
	} else {
		wq->rear->next = add_temp;
		wq->rear = add_temp;
	}

	return 0;
}

int remove_item(struct work_queue_t *wq)
{
	if (wq->rear == NULL)
		return -1;

	

	struct work_item *temp = wq->front;
	int val = temp->operation;

	if (temp == wq->rear) {
		wq->front = NULL;
		wq->rear = NULL;
	} else {
		wq->front = wq->front->next;
		free(temp);
	}

	return val;
}

struct work_queue_t *work_queue()
{
	
	struct work_queue_t *wq = (struct work_queue_t *)malloc(sizeof(struct work_queue_t));

	wq->front = NULL;
	wq->rear = NULL;

	return wq;
}

int display(struct work_queue_t *wq)
{
	struct work_item *temp = wq->front;

	while (temp != NULL) {
		printf("%d ", temp->operation);
		temp = temp->next;
	}
	
	return 0;
}

