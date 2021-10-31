//
// 2021 Fall - Cloud Computing (01)
// Homework #2: Pthread Programming
//
// Copyright (c) Prof. Jaehyeong Sim
// Department of Computer Science and Engineering, Ewha Womans University
//

#include <stdio.h>
#include <pthread.h>

#define STR_SIZE 128

pthread_mutex_t mutex;
char original_string[STR_SIZE] = "Computer, Ewha";
int cnt = 0;
int idx1 = 0;
int idx2 = 0;

void* get_str(void *data)
{
	
	pthread_mutex_lock(&mutex);

	long tid = pthread_self();
	char* target_string = (char*)data;
	int* idx;

	if (target_string.length == 4)
		idx = &idx1;
	if (target_string.length == 8)
		idx = &idx2;

	if (target_string.length == 4 && target_string.length == idx1) {
		printf("*** Thread %d made a string: %s", tid, target_string);
	
	char target = target_string[idx];
	if (strchr(original_string, target != NULL) {
		original_string.Replace(target, '_');
		*idx++;
	} else {
		printf("ERROR; No target in original string\n");
   		pthread_exit(NULL);
	}
	
	
	printf ("Iteration %d:	thread %ld get %s from %s\n", cnt, tid, target, original_string);
	cnt++;
	pthread_mutex_unlock(&mutex);	

}


int main() {

	char target_string1[STR_SIZE] = "Ewha";
	char target_string2[STR_SIZE] = "Computer";

	printf("*** The initial original string:\t\t%s\n", original_string);

	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread1, NULL, get_str, (void *) target_string2);
  	pthread_create(&thread2, NULL, get_str, (void*) target_string1);
  		
	pthread_mutex_destroy(&mutex);

	printf("*** Final original string:\t\t\t%s\n", original_string);
	return 0;

}
