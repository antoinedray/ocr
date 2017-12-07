#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "neural.h"
#include "loaderNN.h"

void XOR_NN(struct NN *MyNet,size_t iter, double learning_rate){
	set_learning_rate(learning_rate);
	double input1[2] = {1,1};
	double input2[2] = {1,0};
	double input3[2] = {0,1};
	double input4[2] = {0,0};
	double output1[1] = {0};
	double output2[1] = {1};
	double output3[1] = {1};
	double output4[1] = {0};
	for(size_t i = 0; i<iter;i++){
		backprop(MyNet,input1,output1);
		backprop(MyNet,input2,output2);
		backprop(MyNet,input3,output3);
		backprop(MyNet,input4,output4);
	}
}

int main(){
	size_t layers[3] = {2,2,1};
	struct NN *MyNet = init_NN(layers,3);
	XOR_NN(MyNet,10000000,0.01);
	save_NN(MyNet,"XOR_NN");	
	double input1[2] = {1,1};
	double input2[2] = {1,0};
	double input3[2] = {0,1};
	double input4[2] = {0,0};
	double *output = feedforward(MyNet,input1);
	printf("1 XOR 1 : %lf \n",output[0]);
	output = feedforward(MyNet,input2);
	printf("1 XOR 0 : %lf \n",output[0]);
	output = feedforward(MyNet,input3);
	printf("0 XOR 1 : %lf \n",output[0]);
	output = feedforward(MyNet,input4);
	printf("0 XOR 0 : %lf \n",output[0]);
	return 1;
}
