#ifndef PIPELINE_TYPES_H
#define PIPELINE_TYPES_H

typedef enum { ACTIVATION_NONE, ACTIVATION_RELU, ACTIVATION_SIGMOID, ACTIVATION_SOFTMAX } ActivationType;

typedef struct {
	double *d_weights;
	double *d_input;
} LayerGrad;

#endif
