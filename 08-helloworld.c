#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void* PrintHello (void* threadid) {
	long tid;
	tid = (long) threadid;
	//if (tid == 1)
	//	for (int i = 0; i < 1000000; i++);
	printf ("Hello World! It’s me, thread #%ld!\n", tid);
	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	pthread_t threads [NUM_THREADS];
	int rc;
	long t;
	for (t = 0; t < NUM_THREADS; t++) {
  		rc = pthread_create(&threads[t], NULL, PrintHello, (void*) t);
  		if(rc) {
   			printf("ERROR; return code from pthread_create( ) is %d\n", rc);
   			pthread_exit(NULL);
  		}
 	}

//	for (t = 0; t < NUM_THREADS; t++) {
//		pthread_join(threads[t], NULL);
//	}

	printf("main finish\n");

 	pthread_exit(NULL);
}
