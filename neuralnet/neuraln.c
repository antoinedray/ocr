#include<err.h>
#include<stdlib.h>
#include"neuraln.h"
/*
struct N {
	double *mat;
	char type;
}

struct NN {
	size_t nb_char;
	struct N **neu;
}*/

//static double size = 32;

struct N *init_N(char a){
	struct N *MyNeu = malloc(sizeof(struct N));
	MyNeu->mat = calloc(sizeof(double),1024);
	MyNeu->type = a;
	return MyNeu;
}

struct NN *init_NN(size_t nb_char,char *l_char){
	struct NN *MyNet = malloc(sizeof(struct NN));
	MyNet->neu = malloc(sizeof(struct N*)*nb_char); 
	for(size_t i = 0; i < nb_char; i++){
		struct N *MyNeu = init_N(l_char[i]);
		MyNet->neu[i] = MyNeu; 
	}
	MyNet->nb_char = nb_char;
	return MyNet;
}

void train_NN(struct NN *MyNet, double *mat, size_t char_i){
	struct N *Neu = MyNet->neu[char_i];
	for(size_t i = 0; i < 1024 ; i++){
		if(mat[i] == 0)
			Neu->mat[i] -= 1;
		else
			Neu->mat[i] += 1;
	}
}
 
double feed(struct N *Neu,struct letter_bin *letter){
	double ret = 0;
	double re = 0;
	for(size_t i = 0 ; i < letter->len ; i++){
		if(Neu->mat[i]>0){	
			ret += letter->inputs[i] * Neu->mat[i];
			re += Neu->mat[i];
		}
	}
	//warn("%lf",ret/re);
	return ret/re;
}

void full_train(struct NN *MyNet){
	size_t i = 0; //idex of char
	FILE *fp = fopen("database/data.txt","r");
	if (fp == NULL){
		printf("Data file does not exists");
		return;
	}
	char line[100]; 
	while(fscanf(fp, "%s", line) != EOF){
		char filename[100] = "";
		char *location = "database/";
		strcat(filename, location);
		strcat(filename, line);
		double *train = get_database_in(filename);
		train_NN(MyNet, train, i);
		free(train);
		if (i >= MyNet->nb_char-1)
			i = 0;
		else
			i++;
	}
}

char full_feed(struct NN *MyNet,struct letter_bin *letter){
	double cur;
	double max = -1000000;
	char ret = '0';
	for(size_t i = 0 ; i < MyNet->nb_char; i++){
		cur = feed(MyNet->neu[i],letter);
		if(cur > max){
			max = cur;
			warn("Char nb: %lu",i);
			ret = MyNet->neu[i]->type;
		}
	}
	return ret;	
}

void save(struct NN *MyNet,char *filename){
	FILE *myfile = fopen(filename,"w");
	fprintf(myfile,"%lu \n",MyNet->nb_char);
	for(size_t i = 0; i < MyNet->nb_char; i++){
		struct N *neu = MyNet->neu[i];
		for(size_t j = 0; j < 1024; j++){
			fprintf(myfile,"%lf ", neu->mat[j]);
			if(j%32 == 0)
				fprintf(myfile,"\n");
		}
		fprintf(myfile,"\n\n");
	}
}
size_t get_char_index(char a, struct NN *MyNet){
	for(size_t i = 0; i < MyNet->nb_char;i++){
		if(MyNet->neu[i]->type == a)
			return i;
	}
	return 0;
}
