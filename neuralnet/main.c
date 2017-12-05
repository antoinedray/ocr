#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "newneural.h"
#include "loaderNN.h"

int main(){
	size_t *size;
	size_t sizer[4] ={2,2,1,0};
	size =sizer;
	printf("Creating NN: \n");
	struct NN *MyNet = init_NN(size);
	if(!MyNet)
		printf("Failed! \n");
	else
		printf("Succes! \n");
	save_NN(MyNet);
	printf("NN saved \n");
	printf("Loading NN \n");
	struct NN *loaded = load_NN("NNsave.txt");
	printf("%lu",loaded->size);
	return 1;
}
