#include "../../../include/backward/linalg/matmul_backward_a.h"
#include "../../../include/linalg/matricies/mattranspose.h"
#include "../../../include/linalg/matricies/matmul.h"

double *matmul_backward_a(Arena *arena, double *dout, double *b, int m, int n, int p){

	double *bt = mattranspose(arena, b, n, p);
	double *grad = matmul(arena, dout, bt, m, p, n);

	return grad;

}
