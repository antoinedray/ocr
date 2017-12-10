#include "data_base.h"

struct N{
	double *mat;
	char type;
}

struct NN {
	size_t nb_char;
	struct N **neu;
}

struct N *init(char a){

}

struct

double feed(struct N *Neu, struct letter_bin *letter);

void full_train(struct NN *MyNet, double *mat);

size_t get_char_index(char a, struct NN *MyNet); 
