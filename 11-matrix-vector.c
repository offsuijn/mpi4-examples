// matrix-vector multiplication

#include <stdio.h>
#include <omp.h>

#define N 16

int main(int argc, char *argv[]) {
	
	double mat[N][N];
	double vec[N];
	
	double result[N];
	double localmax;
	
	double max = -10000000;
	
	char filename[16];

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
	
    omp_set_num_threads(4);
	#pragma omp parallel shared(mat,vec,result)
	{
		#pragma omp for
		for (int i = 0; i < N; i++) {
			result[i] = 0;
			for (int j = 0; j < N; j++)
				result[i] += mat[i][j] * vec[j];
		}
		
		#pragma omp for reduction(max:localmax)
		for (int i = 0; i < N; i++)
			if (result[i] > localmax)
				localmax = result[i];
			
		#pragma omp single
		printf("%f\n", localmax);
	}

	return 0;
}
