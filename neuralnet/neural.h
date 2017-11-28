#ifndef _NEURAL_H_
#define _NEURAL_H_

double sigmoid (double z);
double sigmoid_deriv (double z);
double avg (double* inp, double len);
double sum_pter (double* pointer, int len);
double sum_arr (double* array, int len);
struct NeuralNet{
	int* sizes;
	int layers;
	double** biases_beg;
	double** weights_beg;
};
struct NeuralNet create_neural_net(int *Mysize, int size);
double dot_product(double *v, double *u, int n);
int check (int* Myinp, int pos);
double** feedforward(struct NeuralNet MyNet, double* a);
void backprop_xor(struct NeuralNet MyNet, double* training_inp, 
	double* training_otp, double eta);
#endif