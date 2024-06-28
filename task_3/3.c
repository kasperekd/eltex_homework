#include <stdio.h>

int main(){
    int array[10] = {0};
    int *ptrA = array;

    for (int i = 0; i < 10; i++){
        *(ptrA + i) = i;
    }
    
    for (int i = 0; i < 10; i++){
        printf("%d", *(ptrA + i));
    }
    printf("\n");

    return 0;
}