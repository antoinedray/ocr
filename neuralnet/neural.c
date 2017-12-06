#include <math.h>
#include <stdio.h>
#include <stlib.h>
#include <time.h>

#include "neural.h"

static struct N { //Neurones
	double *weights;
	size_t nb_inputs;
	struct N *inputs;
	//struct N *outputs;
	double bias;
	double value; //sum(w[i]inputs[i]) + bias
}

struct NN { //Neural Network
	size_t size; //nb of layers
	size_t *layersize;
	struct N **mat; //representation of NN threw a matrix
}

static double random(void){
	double random_value;
    srand (time( NULL));
    random_value = (double)rand()/RAND_MAX*2.0-1.0;
    return random_value;
}

static double sigmoid(double x){return 1.0/(1.0+exp(-x));}
static double sigmoid_d(double x){return sigmoid(x)*(1.0-sigmoid(x));}

static struct N *init_N(struct N *inputs,size_t nb_inputs){
	struct N *Neu = malloc(sizeof(struct N));
	Neu->nb_inputs = nb_inputs;
	Neu->inputs = inputs;
	Neu->weights = malloc(sizeof(double)*nb_inputs);
	for(size_t i = 0; i<nb_inputs;i++){
		Neu->weights[i] = random();
	}
	Neu->value = 0;
	Neu->bias = random();
	return Neu;
}

struct NN *init_NN(size_t *layersize,size_t size){
	struct NN *MyNet = malloc(sizeof(struct NN));
	MyNet->size = size;
	MyNet->layersize = layersize;
	MyNet->mat = malloc(sizeof(struct *N)*size);
	for(size_t i = 0; i < size;i++){
		size_t = sizelayer = layersize[i];
		MyNet->mat[i] = malloc(sizeof(struct N)*sizelayer);
		if(i==0){
			for(size_t j = 0; j < sizelayer; j++){ //layer inputs 
				struct N *Neu = init_N(NULL,0);
				MyNet->mat[i][j]=Neu;
			}
		}
		else{
			for(size_t j = 0; j <sizelayer; j++){
			struct N *Neu = init_N(mat[i-1],layersize[i-1]);
			}
		}
	}
	return MyNet;
}

double* feedforward(struct NN *MyNet, double *inputs){
	//setting the inputs
	struct N **mat = MyNet->mat;
	for(size_t i = 0; i < layersize[0]; i++){
		mat[0][i]->value = input[i];
	}
	//starting feedforward
	for(size_t i = 1; i < size; i++){
		struct N *layer = mat[i];
		for(size_t j = 0; j < layersize[i]; j++){
			struct N *node = layer[j];
			node[j]->value = 0;
			for(size_t k = 0; k <node->nb_inputs; k++){
				node[j]->value += (node->weights[k])*(node->inputs[k]->value);
			}
			node[j]->value = sigmoid(value+bias); 
		}
	}
	//getting outputs
	double *outputs = malloc(sizeof(double)*layersize[size-1]);
	for(size_t i = 0; i < layersize[size-1];i++){
		outputs[i] = mat[size-1][i]->value;
	}
	return outputs;
}

void _backprop(struct NN *MyNet, double *input_t, double *output_t){
	//feedforward with training inputs
	feedforward(MyNet,input_t);
	//calculating the error at the outputs and changing following weights/biases 
	// deltak = (tk - ok)ok(1-ok)
	// Dwjk = v*deltak*oj
	// Dbk = v*deltak*1
	double v = 0.1
	// v = learning rate
	// wjk = wjk + Dwjk
	// bjk = bk + Dbk
	//back proping errors
	double *deltas = malloc(sizeof(double)*layersize[size-1]); //MyNet size >=2; 
	for(size_t i = 0; i < MyNet->layersize[size-1];i++){
		struct N *node = mat[size-1][i];
		double delta = (output_t[i] - node->value)*(node->value)*(1 - node->value);
		for(size_t j = 0; j < node->nb_inputs; j++){
			node->weights[j] += v * delta * node->inputs[j]->value;
		}
		deltas[i] = delta;
		node->bias += v * delta * 1;
	}
	//backprop hidden layers
	//deltaj = oj(1-oj)sum(deltak*wjk)
	//here the algo is going backwards, e.g layerprev = output
	double *delta_prev = deltas;
	double *delta_cur = malloc(sizeof(double)*MyNet->layersize[size - 2]);
	for(size_t i = size - 2; i>=0 ; i-=1){
		double *layer_cur = MyNet->mat[i];
		double *layer_prev = MyNet->mat[i+1];
		for(size_t j = 0; j<MyNet->layersize[i]; j++){
			double delta = 0;
			double act_v = 0;
			struct N *node_cur = layer_prev[j]
			for(size_t k = 0; k<MyNet->layersize[i+1]; k++){
				struct N *node_prev = layer_prev[k];
				act_v += delta_prev[k] * node_prev->weights[j]; 
			}
			delta = node_cur->value * (1 - node->value) * (act_v);
			delta_cur[j] = delta;
			for(size_t k = 0; k<
		}
	}	
}
