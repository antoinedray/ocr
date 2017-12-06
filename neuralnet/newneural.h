# include <math.h>
# include <stdio.h>
# include <stdlib.h>


// Structure of Neural Network
struct NN{
	size_t size;
	size_t *layersize;
	double **biases;
	double **weights;

};

struct NN *init_NN(size_t *layersize);

double* feedforward(struct NN *MyNet, double *inputs);
