#include "../../../include/arena.h"
#include "../../../include/linalg/matricies/matmul.h"

double *matmul(Arena *arena, double *a, double *b, int m, int n, int p){

double *resultant = arena_push(arena, sizeof(double)*m*p);

for (int i = 0; i < m; i++){
  for (int j = 0; j < p; j++){
    resultant[i*p+j] = 0;
    for (int k = 0; k < n; k++){
    
    resultant[i*p+j] += a[i*n+k] * b[k*p+j];
    
    }
  
  }
}

  return resultant;

}
