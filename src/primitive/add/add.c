#include <stdarg.h>
#include "primitive/add.h"


double add_numbers(int count, ...){

    va_list list;
    va_start(list,count);
    double total = 0;
    double value;

    for (int i = 0; i<count; i++){

    value = va_arg(list, double);
    total += value;

    }

    va_end(list);

    return total;
}



