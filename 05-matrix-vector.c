// matrix-vector multiplication을 한 뒤, max를 출력하는 예

//
// 2021 Fall - Cloud Computing (01)
// Homework #1: Parallelize matrix-vector multiplication, 
// 		and max operation using OpenMPI
//
// Copyright (c) Prof. Jaehyeong Sim
// Department of Computer Science and Engineering, Ewha Womans University
//

#include "mpi.h"
#include <stdio.h>

//#define N 16
#define N 1024

double mat[N][N];
double vec[N];
double out[N];

int main (int argc, char* argv[])
{
	int rank, size;
	double local_iter, start_iter, end_iter;
	double local_max, max;
	double rdata;
	MPI_Status status;
	double t1, t2;
	char filename[1024];

	// Read matrix and vector data from file
	sprintf(filename, "%d.txt", N);
	FILE *fp = fopen(filename, "r");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(fp, "%lf", &mat[i][j]);
		}
	}
	for (int i = 0; i < N; i++) {
		fscanf(fp, "%lf", &vec[i]);
	}
	fclose(fp);

	// MPI start
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	local_iter = N / size;
	start_iter = rank * local_iter;
	end_iter = local_iter + start_iter;

	for (int i = start_iter; i < end_iter; i++) {
		for (int j = 0; j < N; j++) {
			out[i] += mat[i][j] * vec[j];	
		}		
		
	}

	local_max = -1;
	for (int i = start_iter; i < end_iter; i++) {
		if (out[i] > local_max) {
			local_max = out[i];
		}
	}
	max = local_max;
	
	if (rank == 0) {
		for (int i = 1; size > 1 && i < size; i++) { 
			MPI_Recv(&rdata, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
			if (rdata > max) {
				max = rdata;
			}
		}
		printf("Max Value: %f\n", max);
	} else {
		MPI_Send(&local_max, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	
	t2 = MPI_Wtime();

	printf("Elapsed time for rank %d is %f\n", rank, t2 - t1);
	
	MPI_Finalize();
	
	return 0;
}

