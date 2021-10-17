// 2개의 프로세스가 각각 local sum을 구하여 final sum을 구하는 예제

#include "mpi.h"
#include <stdio.h>

int main (int argc, char* argv[])
{ 
	int rank, size;
	int local_iter, start_iter, end_iter;
	int local_sum, sum;
	int rdata;
	MPI_Status status;
   
	int a[8];
	int b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int c[8] = {-1, -2, -3, -4, -4, -5, -6, -7};
    
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	local_iter = 4;
	start_iter = rank * local_iter;
	end_iter = local_iter + start_iter;

	for (int i = start_iter; i < end_iter; i++) {
		a[i] = b[i] + c[i];
	}

	local_sum = 0;
	for (int i = start_iter; i < end_iter; i++) {
		if (a[i] > 0) {
			local_sum += a[i];
		}
	}

	if (rank == 0) {
		MPI_Recv(&rdata, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		sum = local_sum + rdata;
		printf("%d\n", sum);
	} else {
		MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
