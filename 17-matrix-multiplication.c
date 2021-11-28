#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100

int main(int argc, char **argv) {
    omp_set_num_threads(1); //set number of threads here
    int i, j, k;
    double sum;
    double start, end; // used for timing
    double A[N][N], B[N][N], C[N][N];

    #pragma omp parallel shared(A,B,C)
    {
    #pragma omp for
    for (i = 0; i < N; i++) {
	for (j = 0; j < N; j++) {
	    A[i][j] = j*1;
	    B[i][j] = i*j+2;
	    C[i][j] = j-i*2;
	}
    }
    
    #pragma omp single nowait
    start = omp_get_wtime(); //start time measurement

    for (i = 0; i < N; i++) {
	#pragma omp for
	for (j = 0; j < N; j++) {
	    sum = 0;
	    for (k=0; k < N; k++) {
		sum += A[i][k] * B[k][j];
	    }
	    C[i][j] = sum;
	}
    }
    #pragma omp single
    end = omp_get_wtime(); //end time measurement
    
    #pragma omp single
    printf("Time of computation: %f seconds\n", end-start);
    }

    return(0);
}

/*
Time of computation by # of thread

1 thread => 0.003482
2 thread => 0.005624
4 thread => 0.004796
8 thread => 0.003875
*/
