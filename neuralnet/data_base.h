#include <stdio.h>
#include <stdlib.h>
#include "../mysdl/mysdl.h"

struct letter_bin{
	size_t len; //height*width
	double *inputs; //Black == 1 , White == 0
};

double **get_database_in(size_t nb_fonts, size_t nb_characters);

double **get_database_out(size_t nb_characters);
