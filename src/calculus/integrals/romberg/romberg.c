#include <stdlib.h>
#include <math.h>

double romberg_integrate(double (*f)(double), double a, double b, double eps, int  k_max){

    double h = b - a;
    //not using VLA since im not a fucking chud...
    double *r_prev = calloc(k_max + 1, sizeof(double)); //+1 to avoid overflow
    double *r_curr = calloc(k_max + 1, sizeof(double));
    
r_prev[0] = (h/2) * (f(b) + f(a));

for (int i = 0; i < k_max; i++){
    double pow4 = 1.0;
    h = h/2;
    double c = 0;

    for (int j = 1; j <= (1<<i); j++){

    c += f(a+ (2*j-1) * h);

    }

    r_curr[0] = 0.5*r_prev[0]+h*c;

    for (int m = 1; m <= (i+1); m++){
   
    pow4 *= 4.0;
    r_curr[m] = ((pow4*r_curr[m-1]) - r_prev[m-1]) / (pow4-1);


    }
    if (fabs(r_curr[i+1] - r_prev[i]) < eps ){
    double result = r_curr[i+1];
    free(r_prev);
    free(r_curr);
    return result;

    }    

    double *temp = r_prev;
    r_prev = r_curr;
    r_curr = temp;

}

    double result = r_prev[k_max];  // Last diagonal value
    free(r_prev);
    free(r_curr);
    return result;

}
