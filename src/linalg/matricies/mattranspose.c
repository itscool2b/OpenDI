#include "../../../include/arena.h"
#include "../../../include/linalg/matricies/mattranspose.h"

double *mattranspose(Arena *arena, double *a, int m, int n){

double *resultant = arena_push(arena, m*n*sizeof(double));

for(int i = 0; i < m; i++){
  for (int j = 0; j < n; j++){

    double og_pos = a[i*n+j];
    resultant[j*m+i] = og_pos;
  
  }
}

  return resultant;

}
