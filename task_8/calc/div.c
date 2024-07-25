#include "calc.h"

int div(int a, int b){
    if (b == 0){
        errno = EDOM;
        return 0;
    }
    return a / b;
}