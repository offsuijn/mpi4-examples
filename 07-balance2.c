// Synchronization using Mutex

#include <pthread.h>
#include <stdio.h>

long balance = 500;
pthread_mutex_t mutexbalance = PTHREAD_MUTEX_INITIALIZER;

void* deposit (void* sum) {
	long currbalance;
	pthread_mutex_lock(&mutexbalance);
	currbalance = balance;
	for (int i = 0; i < 100000; i++);
	currbalance += (long) sum;
	balance = currbalance;
	pthread_mutex_unlock(&mutexbalance);
	pthread_exit(NULL);
}

void* withdraw (void* sum) {
	long currbalance;
	pthread_mutex_lock(&mutexbalance);
	currbalance = balance;
	if (currbalance > 0)
		currbalance -= (long) sum;
	balance = currbalance;
	pthread_mutex_unlock(&mutexbalance);
	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	pthread_t thread1, thread2;
	int rc;
  		
	rc = pthread_create(&thread2, NULL, withdraw, (void *) 50);
 	if(rc) {
   		printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   		pthread_exit(NULL);
  	}
	rc = pthread_create(&thread1, NULL, deposit, (void *) 100);

 	if(rc) {
   		printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   		pthread_exit(NULL);
  	}
	
	//pthread_join(thread1, NULL);
	//pthread_join(thread2, NULL);

	//for (int i = 0; i < 1000000; i++);

	printf("balance = %ld", balance);

	return 0;
}

