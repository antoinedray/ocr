#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "neural.h"
#include "loaderNN.h"

int main(){
	size_t *size;
	size_t sizer[4] ={2,2,1};
	size =sizer;
	printf("Creating NN: \n");
	struct NN *MyNet = init_NN(size,3);
	if(!MyNet)
		printf("Failed! \n");
	else
		printf("Succes! \n");
	save_NN(MyNet);
	printf("NN saved \n");
	double inputs[2] ={1,1};
	double *output = feedforward(MyNet,inputs);
	int i = 0;
	while(output[i]){	
		printf("%lf|",output[i]);
		i++;
	}
	//printf("Loading NN \n");
	//struct NN *loaded = load_NN("NNsave.txt");
	//printf("%lu",loaded->size);
	return 1;
}
