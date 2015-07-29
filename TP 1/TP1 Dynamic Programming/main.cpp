/* 
 * Author: Hugo
 */

#include <iostream>
#include <stdio.h>
#include <time.h>

#define BILLION 1000000000L

using namespace std;

bool leftOOB = false;
bool downOOB = false;

int maxvalue(int a, int b) {
    if (a > b)return a;
    return b;
}

int minvalue(int a, int b) {
    if (a < b)return a;
    return b;
}

int main() {

    int N, i,j, diagonal;

    uint64_t diff;
	struct timespec start, end;
	
    cin >> N;
    int array[N];
    int array2d [N][N];

    if (N == 0) {
        cout << 0 << endl;
    }
    //preenche array com valores
    for (i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
    
    for (i = 0; i < N; i++)
    {
    	for (j = 0; j < N; j++)
    	{
    		array2d[i][j]=0;
    	}
    }

    N=N-1;

	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);

    //chama a função para preencher para as N diagonais
    for (diagonal = 0; diagonal <= N; diagonal++) {
        
        j=diagonal;

        for (i = 0; j <= N; i++) {
            leftOOB = false;
            downOOB = false;


            if ((j - 2) < 0) {
                //esquerda 2
                leftOOB = true;
            } else if ((i + 2) > N) {
                //baixo 2
                downOOB = true;
            }

            if ((j - 1) < 0 || (i + 1) > N) {
                array2d[i][j] = maxvalue(array[i], array[j]);
            } else if (leftOOB == true && downOOB == true) {
                array2d[i][j] = maxvalue(array[i], array[j]);
            } else if (leftOOB == true && downOOB == false) {
                array2d[i][j] = maxvalue(array[i] + minvalue(array2d[i + 2][j], array2d[i + 1][j - 1]),
                        array[j]);
            }else if (leftOOB == false && downOOB == true) {
                array2d[i][j] = maxvalue(array[i],
                        array[j] + minvalue(array2d[i + 1][j - 1], array2d[i][j - 2]));
            } else {
                array2d[i][j] = maxvalue(array[i] + minvalue(array2d[i + 2][j], array2d[i + 1][j - 1]),
                        array[j] + minvalue(array2d[i + 1][j - 1], array2d[i][j - 2]));
            }
            j++;
        }

    }

    clock_gettime(CLOCK_MONOTONIC, &end);
	/* mark the end time */
	 diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

    cout << array2d[0][N] << endl;
    return 0;
}

