#include "rounding.h"
#include <string.h>

double roundval(const char* decision, double x){


    if (strcmp(decision, "floor") == 0){

    long long n = (long long)x;

    if (x < 0 && x != n) {
        n = n - 1;
    }

    return (double)n;


    }
    if(strcmp(decision, "ceil") == 0){


    long long n = (long long)x;
    
    if (x > 0 && x != n) {
        n = n + 1;
    }
    
    return (double)n;
}

    else{

    return number;

    }

}
