#include "data_base.h"

struct N{
	double *mat;
	char type;
};

struct NN {
	size_t nb_char;
	struct N **neu;
};

struct N *init_N(char a);

struct NN *init_NN(size_t nb_char, char *l_char);

double feed(struct N *Neu, struct letter_bin *letter);

void full_train(struct NN *MyNet);

char full_feed(struct NN *MyNet,struct letter_bin *letter);

void save(struct NN *MyNet,char *filename);

size_t get_char_index(char a, struct NN *MyNet); 
