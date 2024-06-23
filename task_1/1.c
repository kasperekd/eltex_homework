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
    
    char buf[int_size + 1];
    buf[int_size] = '\0';

    for (int i = 0; i < int_size; i++){
        buf[int_size - 1 - i] = ((in >> i) & 1) + '0';
    }
    
    printf("\nBinary representation of a positive integer: %s\n", buf);

    return 0;
}