#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 1000
#define N 1000
#define P 1000
#define NUM_THREADS 4

int A[M][N];
int B[N][P];
int C[M][P];

void *multiply(void *thread_id) {
    int tid = *((int *)thread_id);
    int start_row = tid * M / NUM_THREADS;
    int end_row = (tid + 1) * M / NUM_THREADS;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

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

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time)/CLOCKS_PER_SEC;

    printf("Elapsed time: %f seconds\n", elapsed_time/NUM_THREADS);
    // Print the result matrix C
    

    return 0;
}
