#include <stdarg.h>
#include <stdio.h>


double divide_numbers(int count, ...){

    va_list list;
    va_start(list,count);

    if (count == 0){

    return 0.0;
    }

    double total = va_arg(list, double);
    double value;

    for(int i = 1; i<count; i++){

    value = va_arg(list,double);

    if (value == 0.0){
    printf("you cant divide by 0");
    return 0.0;
    }
    
    total = total / value;

    }


    va_end(list);
    return total;


}
