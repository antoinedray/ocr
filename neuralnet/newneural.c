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

static inline double random(double min,double max){
	srand(time(NULL));
	double range = max - min;
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

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
			tmp1[i][j] = random(0.0,1.0); //random generator
		}
		for(size_t k = 0;k<MyNet->layersize[i];k++){
			tmp2[i][k] = random(0.0,1.0); //random generator
		}
	}
	MyNet->biases = tmp1;
	MyNet->weights = tmp2;
	return MyNet;
}

int feedforward(struct NN *MyNet, double *inputs){
	return 1;
}
