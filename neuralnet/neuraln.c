#include<err.h>
#include"data_base.h"

struct N {
	double *mat;
	char type;
}

struct NN {
	size_t nb_char;
	struct N **neu;
}

static double size = 32;

struct N *init_N(char a){
	struct N MyNeu = malloc(sizeof(struct N));
	MyNeu->mat = calloc(sizeof(double)*size*size);
	MyNeu->type = a;
}

struct NN *init_NN(size_t nb_char,char *l_char){
	for(size_t i = 0; i < nb_char; i++){
		struct N *MyNeu = init_N (l_char[i]);
	}
}

void train_NN(struct NN *MyNet, double *mat, size_t char_i){
	struct N *Neu = MyNet->neu[char_i];
	for(size_t i = 0; i < size*size ; i++){
		if(mat[i] == 0)
			Neu->mat[i] -= 1;
		Neu->mat[i] += mat[i];
	}
}
 
double feed(struct N *Neu,struct letter_bin *letter){
	double ret = 0;
	double re = 0;
	for(size_t i = 0 ; i < letter->len ; i++){
		ret += letter->inputs[i] * Neu->mat[i];
		re += Neu->mat[i];  
	}
	return ret / re;
}

void full_train(struct NN *MyNet, double *mat){
	size_t i = 0; //idex of char
	while(fscanf(fp, "%s", line) != EOF){
		char filename[100] = "";
		char *location = "database/";
		strcat(filename, location);
		strcat(filename, line);
		double *train = get_database_in(filename);
		train_NN(MyNet, train, i);
		if (i == nb_Chars)
			i = 0;
		else
			i++;
	}
}

void set_size(size_t val){
	size = val;
}

size_t get_char_index(char a, struct NN *MyNet){
	for(size_t i = 0; i < MyNet->nb_char;i++){
		if(MyNet->neu[i]->type == a)
			return i;
	}
}
