/* 
 * Author: Hugo
 */

#include <iostream>
#include <stdio.h>
#include <time.h>

#define BILLION 1000000000L

using namespace std;

bool comparer(int SomaA, int SomaB) {

    if (SomaA < SomaB) {
        return true;
    }
    return false;
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

    N--;
    i=0;
    /*
     * n=3
     * i=0
     * 0 1 2 3
     * 5 3 7 10
     */

    /* measure monotonic time */
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (i < N) {
        
        if (array[N] > array[i]) {
            somaA = somaA + array[N];
            N--;
            if (array[N] > array[i]) {
                N--;
            } else {
                i++;
            }
        } else {
            somaA = somaA + array[i];
            i++;
            if (array[N] > array[i]) {
                N--;
            } else {
                i++;
            }
        }
    }


    clock_gettime(CLOCK_MONOTONIC, &end);
    /* mark the end time */
     diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
    
    cout << somaA << endl;    

    return 0;
}
