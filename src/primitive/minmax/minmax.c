#include "primitive/minmax.h"
#include <stdarg.h>
#include <math.h>

float minmax(int decision, int count, ...){

	if (count == 0){
		return NAN;
	}

	va_list list;
	va_start(list, count);

	float result = va_arg(list, double);

	if (decision == 0) {  // MIN
		for (int i = 1; i < count; i++){
			float val = va_arg(list, double);
			if (val < result){
				result = val;
			}
		}
	}
	else {  // MAX
		for (int i = 1; i < count; i++){
			float val = va_arg(list, double);
			if (val > result){
				result = val;
			}
		}
	}

	va_end(list);
	return result;
}
