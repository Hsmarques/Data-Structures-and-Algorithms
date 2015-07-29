/* 
 * Author: Hugo
 */

#include <iostream>
#include <stdio.h>
#include <time.h>

#define BILLION 1000000000L

using namespace std;

int maxvalue(int a, int b) {
    if (a > b)return a;
    return b;
}

int minvalue(int a, int b) {
    if (a < b)return a;
    return b;
}

int sumMax(int array[], int i, int j) {

    if (i == j - 1) {
        return maxvalue(array[i], array[j]);
    } else {
        return maxvalue(array[i] + minvalue(sumMax(array, i + 2, j	  ), sumMax(array, i + 1, j - 1)),
                		array[j] + minvalue(sumMax(array, i + 1, j - 1), sumMax(array, i 	, j - 2)));
    }
}

int main() {

    int N, i;
    int somaA = 0;

    uint64_t diff;
    struct timespec start, end;

    cin >> N;
    int array[N];

    for (i = 0; i < N; i++) {
        cin >> array[i];
    }


    /* measure monotonic time */
    clock_gettime(CLOCK_MONOTONIC, &start);

    somaA = sumMax(array, 0, N - 1);


    clock_gettime(CLOCK_MONOTONIC, &end);
    /* mark the end time */
     diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
    
    cout << somaA << endl;
    return 0;
}

