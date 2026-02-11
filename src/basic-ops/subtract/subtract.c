#include <stdarg.h>
#include "subtract.h"

double subtract_numbers(int count, ...){

    double value;

    va_list list;
    va_start(list,count);

    double total = va_arg(list,double);
    
    for (int i=1; i<count; i++){

    value = va_arg(list,double);
    total -= value;

    }

    va_end(list);
    return total;

}
