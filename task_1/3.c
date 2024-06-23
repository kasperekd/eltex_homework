#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("\nEnter a positive integer\n> ");

    int in = 0;
    int try_count = 0;
    int c = 0;

    while (1){
        if ((scanf("%d", &in) == 1) && (in > 0)){
            break;
        }
        
        try_count++;

        if (try_count < 3){
            printf("\nInvalid number entered, try again\n> ");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }else{
            printf("\nToo many failed input attempts\n");
            exit(1);
        }
    }
    
    int int_size = sizeof(in) * 8;
    int units_count = 0;

    for (int i = 0; i < int_size; i++){
        (in >> i) & 1 ? units_count++ : 0;
    }
    
    printf("\nUnits in binary representation of a positive integer: %d\n", units_count);

    return 0;
}