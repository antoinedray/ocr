#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<string.h>
#include"neural.h"
#include"loaderNN.h"

void save_NN(struct NN *mynet, char * name)
{
	FILE * myfile;
	myfile = fopen(name,"w");
	fprintf(myfile, "%lu\n[",mynet->size);
	for(size_t i = 0; i < mynet->size;i++)
	{
		fprintf(myfile,"%lu");
		if (i < mynet->size-1)
			frprintf(myfile,",");
	}
	fprintf(myfile,"]\n");
	for(size_t i = 0; i < mynet->size; i++)
	{
		for (size_t j = 0; j < mynet->layersize[i]; j++)
		{
			for(size_t k = 0; k < mynet->mat[i][j]->nb_inputs;k++)
			{
				fprintf(myfile,"[%lu][%lu]#%lf\n",i-1,k,mynet->mat[i][j]->weights[k]);
			}
			fprintf(myfile,"b %lf\n",mynet->mat[i][j]->bias);
		}
		fprintf(myfile,"$\n");
	}

	fprintf(myfile,"E");
	fclose(myfile);
}

struct NN * load_NN(char *name)
{
	FILE *file = fopen(fileName,r)
	char prev = "";
	char c = ""
	size_t s = 0;
	struct NN *mynet = malloc(sizeof(struct NN));
	double = 
	while ((c = fgetc(file)) != EOF)





	FILE * myfile;
	myfile = fopen(name,"r");
	char* line = NULL
	struct NN *mynet = malloc(sizeof(struct NN));
	size_t mynet_size = 0;
	mynet_size = (size_t)fgetc(file);
	size_t s = 0;
	char c = "";
	
	for (int i = 0; i < 2; i++)
		fgetc(file);
	
	size_t * mynet_layers = malloc(mynet_size);
	
	for (size_t i =0; i < mynet_size; i++)
	{
		s = 0;
		c = "";
		while((c = fgetc(myfile) != "," && c != "]")
			s = 10 * s + (size_t)c;
		mynet_layers[i] = s;
	}
	fgetc(myfile);
	fgetc(myfile);

	size
	for (size_t i = 0; i < mynet_size; i++)
	{
		for (size_t j = 0; j < mynet_layers[i]; j++)
		{
			struct mynn = 
			s = 0;
			s = "";
			while((c = fgetc(myfile) != "#" && c != "\n" && c != "]")
				s = 10 * s + (size_t)s;
			if
		}
	}

}

/*
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
*/
