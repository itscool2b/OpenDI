#include "../../../include/arena.h"
#include "../../../include/linalg/matricies/matadd.h"

double *matadd(Arena *arena, double *a, double *b, int m, int n){

double *resultant = arena_push(arena, sizeof(double)*m*n);
for (int i = 0; i < m; i++){
  for (int j = 0; j < n; j++){
      resultant[i*n+j] = a[i*n+j] + b[i*n+j];
  }
}

  return resultant;
}
