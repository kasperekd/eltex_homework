#include <stdio.h>

#define N 5

int main(){

    int matrix[N][N] = {0};
    int value = 1;
    int row = 0, col = 0;
    int dx = 1, dy = 0;

    for (int i = 0; i < N * N; i++) {
        matrix[row][col] = value++;
        
        int nextRow = row + dy;
        int nextCol = col + dx;
        
        if (nextRow >= N || nextRow < 0 || nextCol >= N || 
            nextCol < 0 || matrix[nextRow][nextCol] != 0) {
            int temp = dx;
            dx = -dy;
            dy = temp;
        }
        
        col += dx;
        row += dy;
    }

    for (int i = 0; i < N * N; i++){
        printf("%2d ", matrix[0][i]);
        if ((i + 1) % N == 0){
            printf("\n");
        }
    }

    return 0;
}