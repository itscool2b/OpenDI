#include "../../../include/arena.h"
#include "../../../include/linalg/matricies/matscale.h"

double *matscale(Arena *arena, double *a, double s, int m, int n){


double *resultant = arena_push(arena, sizeof(double)*n*m);

for (int i = 0; i < m; i++){
  for(int j = 0; j <n; j++){
  
  resultant[i*n+j] = a[i*n+j] * s;
  }

}

  return resultant;

}
