#include <stdarg.h>
#include "primitive/multiply.h"

double multiply_numbers(int count, ...){

    va_list list;
    va_start(list,count);
    double value;
    double total = va_arg(list, double);

    for (int i = 1; i<count; i++){

    value = va_arg(list,double);
    total = total * value;

    }

    va_end(list);
    return total;

}
