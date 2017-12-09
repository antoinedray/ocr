#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "neural.h"
#include "loaderNN.h"
#include "data_base.h"

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

void OCR_NN(struct NN *MyNet, size_t iter, double learning_rate, size_t nb_fonts){
	set_learning_rate(learning_rate);
	double **inputs = get_database_in(nb_fonts, 62);
	double **outputs = get_database_out(62);
	size_t size_DB = nb_fonts*62;
	for(size_t i = 0; i < iter; i++){
		for(size_t j = 0; j < size_DB; j++){
			backprop(MyNet,inputs[j], outputs[j]);
		}
	}
}

int main(int argc,char* argv){
	if (argv == "XOR"){
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
	}
	else if (argv == "OCR"){
		size_t layers[3] = {1024,512,62};
		struct NN *MyNet = init_NN(layers,3);
		OCR_NN(MyNet,10000,0.2,60); //get nb_fonts
		save_NN(MyNet,"OCR_NN");
	}
	else
		printf("Incorrect arguments");
	return 1;
}
