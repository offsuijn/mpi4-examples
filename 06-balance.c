// Synchronization using Joining

#include <pthread.h>
#include <stdio.h>

int balance = 500;

void* deposit (void* sum) {
	int currbalance = balance;
	//for (int i = 0; i < 100000; i++);
	currbalance += (long) sum;
	//for (int i = 0; i < 100000; i++);
	balance = currbalance;
	pthread_exit(NULL);
}

void* withdraw (void* sum) {
	int currbalance = balance;
	//for (int i = 0; i < 100000; i++);
	if (currbalance > 0)
		currbalance -= (long) sum;
	//for (int i = 0; i < 100000; i++);
	balance = currbalance;
	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	pthread_t thread1, thread2;
	int rc;
  	
	rc = pthread_create(&thread1, NULL, deposit, (void *) 100);
	if(rc) {
   		printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   		pthread_exit(NULL);
  	}
	rc = pthread_create(&thread2, NULL, withdraw, (void *) 50);

 	if(rc) {
   		printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   		pthread_exit(NULL);
  	}

	//pthread_join(thread1, NULL);
	//pthread_join(thread2, NULL);

	printf("balance = %d", balance);

	return 0;
}

