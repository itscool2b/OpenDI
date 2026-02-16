#include <plplot.h>
#include "visuals/graph.h"
#include <stdlib.h>

void graph(double (*f)(double), double x_min, double x_max, int num_points, const char *title)
{


    double *x = malloc(num_points*sizeof(double));
    double *y = malloc(num_points*sizeof(double));

    double y_min = f(x_min);
    double y_max = y_min;
    double step = (x_max - x_min) / (num_points - 1);

    for (int i = 0; i<num_points; i++){

    x[i] = x_min + i * step;
    y[i] = f(x[i]);

    if (y[i] < y_min){ 


    y_min = y[i];

    }
    if (y[i] > y_max){ 


    y_max = y[i];

    }

    }

    plsdev("xwin");
    plinit();
    plenv(x_min, x_max, y_min, y_max, 0, 0);
    pllab("x","y", title);
    plline(num_points,x,y);
    plend();

    free(x);
    free(y);


}

