#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "neural.h"

int main(){
	srand(time(NULL));
	int* MyInputs = NULL;
	int* MyOutputs = NULL;
	int len = 1100;
	for (int i = 0; i < len; i++){
		for (int j = 0; j < 2; j++)
			*(MyInputs + (i * 2) + j) = (int)rand() % 2;
		*(MyOutputs + i) = check(MyInputs + i, len);
	}
	int* mat = NULL;
	*mat = 2;
	*(mat + 1) = 2;
	*(mat + 2) = 1;
	int lay = 3;
	struct NeuralNet MyNet = create_neural_net(mat, lay);
	/*double** w = MyNet.weights_beg;
	  double** b = MyNet.biases_beg;*/
	for(int i = 0; i < len; i++){
		double* inp = NULL;
		*inp = *(MyInputs + i * 2);
		*inp = *(MyInputs + i * 2 + 1);
		double* out= NULL;
		*out = *(MyOutputs + i);
		backprop_xor(MyNet, inp, out, 1.0);
		if (i%100 == 0){
			double** a = (feedforward(MyNet,inp));
			printf("iteration number %u:inp:(%f,%f);out:%f;expected:%f\n",
					(char) i, *inp, *(inp + 1), **a, *(out + i));
		}
	}
	printf("\nDONE\n");
	return 0;

}
