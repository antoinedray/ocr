#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "neural.h"

double sigmoid (double z){
	return(1.0/ (1.0 + exp(-z)));
}

double sigmoid_deriv (double z){
	return sigmoid(z) * (1 - sigmoid(z));
}

double avg (double* inp, double len){
	double ret = 0.0;
	for (int i = 0; i < len; i++)
		ret += *(inp + i);
	return (ret / len);
}

double sum_pter (double* pointer, int len){
	double res = 0.0;
	for (int i = 0; i < len; i++)
		res += *(pointer + i);
	return res;
}

double sum_arr (double* arr, int len){
	double res = 0.0;
	for (int i = 0; i < len; i++)
		res += *(arr + len);
	return res;
}

/*struct NeuralNet{
  int* sizes;
  size_t layers;
  double** biases_beg;
  double** weights_beg;
  };
*/
struct NeuralNet create_neural_net(int* Mysize, int size){
  struct NeuralNet MyNet = malloc(sizeof(NeuralNet));	
  double** MyBiases = malloc(sizeof (double));
	double** MyWeights = NULL;
	srand (time(NULL));

	//maybe change this to double pointer

	for(int i = 0; i < size; i++){
		if (i != 0){
			//*(MyBiases + i - 1)[Mysize[i]];
			for (int j = 0; j < *(Mysize+i);j++){
				*(*(MyBiases + i - 1) + j) = (double)rand()
					/ (double) RAND_MAX;
			}
		}
		if (i != sizeof(Mysize) - 1){
			//*(MyWeights + i)[Mysize[i]];
			for (int j = 0; j < Mysize[i];j++){
				*(*(MyWeights + i)+j) = (double)rand()
					/ (double) RAND_MAX;
			}
		}
	}
	struct NeuralNet MyNet;
	MyNet.weights_beg = MyWeights;
	MyNet.biases_beg =MyBiases;
	MyNet.sizes = Mysize;
	MyNet.layers = size;
	return MyNet;
}

double dot_product(double *v, double *u, int n)
{
	double result = 0.0;
	for (int i = 0; i < n; i++)
		result += *(u + i) * (*(v + i));
	return result;
}

int check (int* Myinp, int pos){
	if(*(Myinp + pos) == *(Myinp+pos +1))
		return 0;
	return 1;
}


double** feedforward(struct NeuralNet MyNet, double* a){
	double** res = NULL;
	for (int i = 0; i < MyNet.layers; i++){
		double* tmp = NULL;
		*tmp = 0.0;
		for (int j = 0; j < *(MyNet.sizes + i); j++){
			*(tmp + j) = sigmoid(dot_product(*(MyNet.weights_beg + i), a, 
						*(MyNet.sizes + i)) 
					+ *(*(MyNet.biases_beg + i) + j));
		}
		a = tmp;
		*res = tmp;
		res--;
	}
	return res;
}

void backprop_xor(struct NeuralNet MyNet, double* training_inp, 
		double* training_otp, double eta){
	double** nabla_w = NULL;
	double** nabla_b = NULL;

	//take code from create neuralnet to init nablas
	for(int i = 0; i < MyNet.layers; i++){
		if (i != 0){
			for (int j = 0; j < *(MyNet.sizes + i);j++){
				*(*(nabla_b + i - 1) + j) = 0;
			}
		}
		if (i != MyNet.layers - 1){
			for (int j = 0; j < *(MyNet.sizes + i);j++){
				*(*(nabla_w + i)+j) = 0;
			}
		}
	}

	double** a = feedforward(MyNet, training_inp);
	double** err_degree = NULL;
	**err_degree = 0.0;

	for (int i = 0; i < MyNet.layers;i++){
		for (int j = 0; j < MyNet.sizes[MyNet.layers - i - 1]; j++){
			if (i == 0)
				*(*(err_degree) + i) = (*(training_otp + i) - *((*a) + i)) 
					* (*(*a) + i)* (1 - (*(*a) + i));
			else{
				*(*(nabla_w + MyNet.layers - j - 1)+j) = eta * 
					*(*(err_degree) + j) * *(*(a + i) + j);
				*(*(nabla_b + MyNet.layers - j - 1)+j) = eta 
					* *(*(err_degree) + j) * *(*(a + i) + j);
				*(*(err_degree + i) + j) = (*((*a + i)+ j))* (1 - 
						(*(*(a+i)) + j)) * (**err_degree) * (sum_arr 
							(*(MyNet.weights_beg + MyNet.layers - i - 1), 
							 *(MyNet.sizes + MyNet.layers - i - 1)));
			}
		}
	}

	MyNet.weights_beg = nabla_w;
	MyNet.biases_beg = nabla_b;














	/*for (int i = 0; i < MyNet.sizes[MyNet.layers - 1]; i++){
	 *(*(err_degree) + i) = (*(training_otp + i) - *((*a) + i)) * (*(*a) + i)* (1 - (*(*a) + i));
	 }

	 for (int i = 0; i < MyNet.sizes[MyNet.layers - 2]; i++){
	 *(nabla_w + MyNet.layers - 1)[i] = eta * *(*(err_degree) + i) * (*(a) + i);
	 }

	 for (int i = 0; i < MyNet.sizes[MyNet.layers - 2]; i++){
	 *(*(err_degree + 1) + i) = (*((*a + 1)+ i))* (1 - (*(*(a+1)) + i)) * (**err_degree) * (sum_arr (*(MyNet.weights_beg + MyNet.layers - 2)));
	 }

	 *(nabla_w) = eta * avg(*(err_degree+1), MyNet.size[1]) *  
	 return nabla_w;*/
}

/*void backprop(struct NeuralNet MyNet, int* training_inp[], int* training_otp[], int epochs, double eta){
  if (sizeof(training_inp) / MyNet.sizes[0] == sizeof(training_otp) / MyNet.sizes[sizeof(sizes) - 1]){
  for (int i = 0; i < epochs; i++){
  for (int j = 0; j < sizeof(training_inp);j++){
  double* a = feedforward(MyNet, *(training_inp + j));
  double var = 0.0;
  if (j == 0){
  var = eta * ((*(training_otp + j) - (*a)) * (*a) * (1 - *a)) * ;
  }			
  }
  }
  }
  }
 */


/*void sgd(struct NeuralNet MyNet, int training_inp[], int training_otp[]){
  if (sizeof(test_data) != 0){
  }
  size_t n = sizeof(training_inp);
  for (size_t i = 0; i < sizeof(epochs); i++){
//shuffle your training data
mini_batches = 
}
}
void update_mini_batch (struct NeuralNet MyNet, double *mini_batches[], double eta){
}*/
