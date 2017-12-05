#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<string.h>
#include"newneural.h"
#include"loaderNN.h"

void save_NN(struct NN *MyNet){
	FILE *f = fopen("NNsave.txt","w");
	if(!f){warn("Not able to create save file");return;}
	fprintf(f,"%lu \n",MyNet->size);
	size_t h = 0;
	while(MyNet->layersize[h]){
		fprintf(f,"%lu|",MyNet->layersize[h]);
		h++;
	}
	fprintf(f,"\n \n");
	for(size_t i =0;MyNet->biases[i];i++){
		for(size_t j=0;j<MyNet->layersize[i+1];j++){
			fprintf(f,"%lf|",MyNet->biases[i][j]);
		}
		fprintf(f,"\n");
	}
	fprintf(f,"\n");
	for(size_t i =0;MyNet->weights[i];i++){
		for(size_t j=0;j<MyNet->layersize[i];j++){
			fprintf(f,"%lf|",MyNet->weights[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
	return;
}

struct NN *load_NN(char *filename){
	FILE *f = fopen(filename,"r");
	char *line = NULL;
	size_t len =0;
	size_t index = 0;
	int loc = 0;
	struct NN *MyNet = malloc(sizeof(struct NN));
	while(!feof(f)){
		getline(&line,&len,f);
		if (loc == 0){
			MyNet->size = atoi(line);
			loc +=1;
		}
		if (loc == 1){
			index = 1;
			for(size_t i = 0 ; line[i]!='\n';i++){
				if(line[i] == '|'){
					index +=1;
				}
			}	
		}
	}	
	return MyNet;
}
