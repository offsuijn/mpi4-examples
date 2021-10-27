// producer-consumer 예제 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QSIZE 5
#define LOOP 1

typedef struct {
	 int data[QSIZE];
	 int index;
	 int count;
	 pthread_mutex_t lock;
	 pthread_cond_t notfull;
	 pthread_cond_t notempty;
}
queue_t;

void* produce (void* args);
void* consume (void* args);
void put_data (queue_t* q, int d);
int get_data (queue_t* q);
queue_t* qinit();
void qdelete(queue_t* q);

int main() {
	 
	queue_t *q;
	pthread_t producer, consumer;
	pthread_t consumer2;
	   
	q = qinit();

	pthread_create(&producer, NULL, produce, (void *)q);
	pthread_create(&consumer, NULL, consume, (void *)q);
	pthread_create(&consumer2, NULL, consume, (void *)q);

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);
	pthread_join(consumer2, NULL);

	qdelete(q);

}

queue_t* qinit() {

	queue_t* q;
	  
  	q = (queue_t*)malloc(sizeof(queue_t));
	q->index = q->count = 0;
	pthread_mutex_init(&q->lock, NULL);
	pthread_cond_init(&q->notfull, NULL);
	pthread_cond_init(&q->notempty, NULL);

	return q;

}

void qdelete(queue_t* q) {
	 
	pthread_mutex_destroy(&q->lock);
	pthread_cond_destroy(&q->notfull);
	pthread_cond_destroy(&q->notempty);
	free(q);

}

void* produce(void* args) {

	int i, d;
	queue_t* q = (queue_t*)args;
	for (i = 0; i < LOOP*2; i++) {
//	for (i = 0; i < LOOP; i++) {
		d = random() % 10;
		put_data(q, d);
		printf("%d: %ld put data %d to queue\n", i, pthread_self(), d);
	} 
	pthread_exit(NULL);
}

void* consume(void* args) {

	int i, d;
	queue_t* q = (queue_t*)args;
	for (i = 0; i < LOOP; i++) {
		d = get_data(q);
		printf("%d: %ld got data %d from queue\n", i, pthread_self(), d);
	}
	pthread_exit(NULL);
}

void put_data(queue_t* q, int d) {

	for (int i = 0; i < 10; i++) {
		 printf("a");
		 fflush(stdout);
	}

	pthread_mutex_lock(&q->lock);
	while (q->count == QSIZE)
//	if (q->count == QSIZE)
		pthread_cond_wait(&q->notfull, &q->lock);
	q->data[(q->index + q->count) % QSIZE] = d;
	q->count++;
//	pthread_cond_signal(&q->notempty);
	pthread_cond_broadcast(&q->notempty);
	pthread_mutex_unlock(&q->lock);

}

int get_data(queue_t* q) {

	int d;
	pthread_mutex_lock(&q->lock);
//	while(q->count == 0) {
	if(q->count == 0) {
		for (int i = 0; i < 10; i++) {
		 printf("b");
		 fflush(stdout);
		}
		pthread_cond_wait(&q->notempty, &q->lock);
	}
	d = q->data[q->index];
	q->index = (q->index + 1) % QSIZE;
	q->count--;
	pthread_cond_signal(&q->notfull);
	pthread_mutex_unlock(&q->lock);
		 
	return d;
}


