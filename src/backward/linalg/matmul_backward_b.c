#include "../../../include/backward/linalg/matmul_backward_b.h"
#include "../../../include/linalg/matricies/mattranspose.h"
#include "../../../include/linalg/matricies/matmul.h"

double *matmul_backward_b(Arena *arena, double *a, double *dout, int m, int n, int p){

	double *at = mattranspose(arena, a, m, n);
	double *grad = matmul(arena, at, dout, n, m, p);

	return grad;

}
