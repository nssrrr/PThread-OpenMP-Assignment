#include <stdio.h>
#include </opt/homebrew/opt/libomp/include/omp.h>
#include <time.h>

#define M 1000
#define N 1000
#define P 1000

int A[M][N];
int B[N][P];
int C[M][P];

int main() {

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = i - j;
        }
    }

    clock_t start_time = clock();

    #pragma omp parallel for
    printf("hi\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time)/CLOCKS_PER_SEC;

    printf("Elapsed time: %f seconds\n", elapsed_time/4);

    return 0;
}
