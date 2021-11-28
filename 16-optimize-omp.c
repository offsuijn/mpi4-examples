int foo(int N, int *a, int *b, int *c, int *d) {
    double tmp, total = 0;
    
    // share, private 변수를 설정해준다.
    #pragma omp parallel default(none) \
	shared(N,a,b,c,d,total) private(tmp)
    {
	// for문을 parallel로 돌리기 위해서 sections를 없애고 성능을 높이기 위해 nowait을 추가하였다.
        #pragma omp for nowait
	for (int i = 0; i < N; i++) {
 		a[b[i]] += b[i];
		total += b[i];
 	}
	#pragma omp for nowait
	for (int i = 0; i < N; i++) {
		tmp = c[i];
		c[i] = d[i];
		d[i] = tmp;
		total += c[i];
 	}
	
	// 다음에 올 for문은 위의 d 배열 값을 모두 변경한 뒤에 실행되어야 하므로 배리어를 걸어 모든 연산이 끝날 때까지 기다린다.
	#pragma omp barrier

	#pragma omp for
	for (int i = 0; i < N; i++) {
		total += d[i];
	}
    }
    return total;
}
