# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include <math.h>
# include <time.h>

# include "newneural.h"

/*struct NN {
	size_t size;
	size_t *layersize; // nb of neurones per layer
	double **biases; //first layer no biases
	double **weights; //last layer no weights
};*/

// layersize = { X , X , X} X a size_t value.

static double sigmoid(double x){return 1.0/(1.0+exp(-x));}

static double sigmoid_d(double x){return sigmoid(x)*(1.0-sigmoid(x));}

static size_t len_array(size_t *arr){
	size_t i = 0;
	while(arr[i])
		i+=1;
	return i;
}

struct NN *init_NN(size_t *layersize){
	struct NN *MyNet = malloc(sizeof(struct NN));
	if(!MyNet){warn("Not able to allocate memory for Neural Network");return NULL;}
	MyNet->size = len_array(layersize);
	MyNet->layersize = layersize;
	double **tmp1 = malloc(sizeof(double *)*(MyNet->size-1));
	if (!tmp1){warn("Not able to allocate memory for Pointer Array Biases");return
NULL;}
	double **tmp2 = malloc(sizeof(double *)*(MyNet->size-1));
	if (!tmp2){warn("Not able to allocate memory for Pointer Array Weigths");return
NULL;}
	srand(time(NULL));
	for(size_t i = 0;i<MyNet->size-1;i++){
		tmp1[i] = malloc(sizeof(double)*(MyNet->layersize[i+1]));
		if (!tmp1[i]){
			warn("Not able to allocate memory for Array Biases");
			return NULL;
		}
		tmp2[i] = malloc(sizeof(double)*(MyNet->layersize[i]));
		if (!tmp2[i]){
			warn("Not able to allocate memory for Array Weigths");
			return NULL;
		}
		for(size_t j = 0;j<MyNet->layersize[i+1];j++){
			tmp1[i][j] = (double)rand()/(double)RAND_MAX;
		}
		for(size_t k = 0;k<MyNet->layersize[i];k++){
			tmp2[i][k] = (double)rand()/(double)RAND_MAX;
		}
	}
	MyNet->biases = tmp1;
	MyNet->weights = tmp2;
	return MyNet;
}

static size_t nb_neurones(struct NN *MyNet){
	size_t ret = 0;
	for(size_t i = 0; i<MyNet->size;i++)
		ret += MyNet->layersize[i];
	return ret;
}

double* feedforward(struct NN *MyNet, double *inputs){
	size_t *layersize = MyNet->layersize;
	double** weights = MyNet-> weights;
	double** biases = MyNet-> biases;
	size_t size = MyNet->size;
	double* output = NULL;
	for(size_t l = 1; l<size;l++){ 
		double *next_layer = malloc(layersize[l]*sizeof(double));
		for(size_t i = 0; i<layersize[l];i++){
			double valn = 0;
			for(size_t j = 0; j<layersize[l-1];j++){
				valn += weights[l-1][j] * inputs[j]; 
			}
			valn = sigmoid(valn + biases[l-1][i]);
			next_layer[i]=valn;
			output = next_layer;
		}
	}
		return output;
}

void _backprop(struct NN *MyNet, double *input_t, double *output_t){
	//feedforward trainning	
	size_t *layersize = MyNet->layersize;
	double** weights = MyNet-> weights;
	double** biases = MyNet-> biases;
	size_t size = MyNet->size;
	double* output = NULL;
	double** activation_v = malloc((size)*sizeof(double*));
	activation_v[0] = input_t;
	for(size_t i = 1; i<size;i++){
		activation_v[i] = malloc(layersize[i]*sizeof(double));
	}
	for(size_t l = 1; l<size;l++){ 
		double *next_layer = malloc(layersize[l]*sizeof(double));
		for(size_t i = 0; i<layersize[l];i++){
			double valn = 0;
			for(size_t j = 0; j<layersize[l-1];j++){
				valn += weights[l-1][j] * inputs[j]; 
			}
			valn = sigmoid(valn + biases[l-1][i]);
			next_layer[i]=valn;
			activation_v[l][i] = valn;
			output = next_layer;
		}
	}
	//Error calculation
	double *errors = malloc((layersize[size-1]*sizeof(double))
	for(size_t i = 0; i<layersize[size-1]; i++){
		double delta = (output_t[i] -
activation[size-1][i])activation[size-1][i](1-activation[size-1][i]);
	//RESTARTING FROM SCRATCH DON"T USE THIS FILE
		


