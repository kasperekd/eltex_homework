#include <stdio.h>

#define N 3
#define FLAT 0

int main(){
#if !FLAT
    int matrix[N][N];

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matrix[i][j] = i * N + j + 1;
        }
    }
    
    for (int i = 0; i < N * N; i++){
        printf("%d ", matrix[0][i]);
        if ((i + 1) % N == 0){
            printf("\n");
        }
    }
#endif
#if FLAT
    int flatMatrix[N * N];
    for (int i = 0; i < N * N; i++){
        flatMatrix[i] = i + 1;
    }
    
    for (int i = 0; i < N * N; i++){
        printf("%d ", flatMatrix[i]);
        if ((i + 1) % N == 0){
            printf("\n");
        }
    }
#endif
    return 0;
}