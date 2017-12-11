//#include <stdlib.h>
//#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>

//#include "neural.h"
//#include "loaderNN.h"
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

void OCR_NN(struct NN *MyNet, size_t iter, double learning_rate){
  set_learning_rate(learning_rate);
  for(size_t i = 0; i<iter; i++){
    printf("%zu / %zu\n", i, iter);
    train(MyNet);
  }
}

void try_OCR_img(struct NN *MyNet, char* character,size_t char_index){
    //struct NN *MyNet = load_NN(filename);
    double *inputs = get_database_in(character);
    double *outputs = feedforward(MyNet,inputs);
    double coef = 0;
    size_t ret = 0;
    for(size_t i = 0; outputs[i];i++){
        if(coef < outputs[i]){
            coef = outputs[i];
            ret = i;
        }
    }
    printf("%lu %lu \n",char_index,ret);
}

int main(){
/*
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
*/
    size_t layers[3] = {1024,512,66};
    struct NN *MyNet = init_NN(layers,3);
    OCR_NN(MyNet,10000,0.2); //get nb_fonts
    save_NN(MyNet,"OCR_NN_1");
	char line[50];
	MyNet = load_NN("OCR_NN_1");
    FILE *f = fopen("database/data.txt","r");
	size_t i = 0;
	while(fscanf(f,"%s", line) != EOF){
		char loc[100] = "database/";
		strcat(loc,line);
		try_OCR_img(MyNet, loc, i);
		i++;
	} 
   	return 1;
}
