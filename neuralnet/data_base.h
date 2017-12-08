#include <stdio.h>
#include <stdlib.h>
#include "../mysdl/mysdl.h"

struct BIN_Matrix{
	int lines;
	int cols;
	double *mat;
};

struct letter_bin{
	size_t len;
	int *inputs;
};

double* get_inputs_NN(struct letter_bin *l);
