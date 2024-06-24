#include <stdio.h>

#define N 3

int main(){
    int matrix[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (j < N - i) ? 1 : 0;
        }
    }

    for (int i = 0; i < N * N; i++){
        printf("%d ", matrix[0][i]);
        if ((i + 1) % N == 0){
            printf("\n");
        }
    }
    
    return 0;
}