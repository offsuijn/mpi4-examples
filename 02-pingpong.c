// 2개의 프로세스가 char를 주고받는 예제
// process 1 -> 0 : 'a'
// process 0 -> 1 : 'b'

#include "mpi.h"
#include <stdio.h>

int main (int argc, char* argv[])
{
    int rank, size;
    char sdata, rdata;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int i = 0;

    while(i < 10) {
	if (rank == (i%2)) {
		sdata = 'a' + (i%2);
		MPI_Send(&sdata, 1, MPI_CHAR, (rank+1)%2, 0, MPI_COMM_WORLD);
		printf("Rank %d Iter: %d Sending: %c\n", rank, i, sdata);
		i++;
		MPI_Send(&i, 1, MPI_INT, (rank+1)%2, 0, MPI_COMM_WORLD);
	} else {
		MPI_Recv(&rdata, 1, MPI_CHAR, (rank+1)%2, 0, MPI_COMM_WORLD, &status);
    		printf("Rank %d Iter: %d Receiving: %c\n", rank, i, rdata);
		MPI_Recv(&i, 1, MPI_INT, (rank+1)%2, 0, MPI_COMM_WORLD, &status);
	}
    }

    MPI_Finalize();
    return 0;
}
