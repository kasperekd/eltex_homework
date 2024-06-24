#include <stdio.h>

#define N 5

int main(){
    int array[N];
    for (int i = 0; i < N; i++){
        array[i] = i + 1;
    }
    
    printf("\nInput ->");
    for (int i = 0; i < N; i++){
        printf(" %d",array[i]);
    }
    
    for (int i = 0; i < N / 2; i++) {
        int temp = array[i];
        array[i] = array[N - i - 1];
        array[N - i - 1] = temp;
    }

    printf("\nOutput ->");
    for (int i = 0; i < N; i++){
        printf(" %d",array[i]);
    }

    printf("\n");
    return 0;
}