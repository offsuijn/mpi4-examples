#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, f;
    char *array;
    const int n = 27;

    array = malloc(n * sizeof(char));
    for (i=0; i<n-1; i++)
        array[i] = i + 'a';

    f = array[0];

    printf("Before  = <%s>\n",array);

    #pragma omp parallel default(none) shared(array,n,f) private(i)
    {
        int nthreads = omp_get_num_threads();
        int tid = omp_get_thread_num();
        
        int blocksize = (n-2) / nthreads;
        int start = tid * blocksize;
        int end = start + blocksize - 1;
        if (tid == nthreads-1) end = n-2;

        char val = array[end+1];
        #pragma omp barrier 

        for (i = start; i < end; i++)
            array[i] = array[i+1];

        array[end] = val;
	
	#pragma omp barrier
	#pragma omp single
	array[n-2] = f;
    }

    printf("After = <%s>\n",array);

    return 0;
}
