#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>

struct NN {
	size_t size;
	size_t *layersize;
	struct N ***mat;
};

void set_learning_rate(double x);

struct NN *init_NN(size_t *layersize, size_t size);

double* feedforward(struct NN *MyNet, double *inputs);

void backprop(struct NN *MyNet, double *input_t, double *output_t);

int *get_outputs(struct NN *MyNet, double *out);
