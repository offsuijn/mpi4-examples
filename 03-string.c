// 문자열을 주고받는 예제
// process 1 -> 0 : Some String

#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
    int rank, size;
    MPI_Status status;
    
    char sdata[255];
    char rdata[255];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 1) {
	strcpy(sdata, "String이 간다 길을 비켜라");
	MPI_Send(sdata, 255, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	printf("SENDING: %s\n", sdata); 
    } else {
	MPI_Recv(rdata, 255, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
	printf("RECEIVED: %s\n", rdata);
    }

    MPI_Finalize();
    return 0;
}
