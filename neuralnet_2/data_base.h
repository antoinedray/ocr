//#include <stdio.h>
//#include <stdlib.h>
#include "../mysdl/mysdl.h"

struct letter_bin
{
    size_t len; //height*width
    double *inputs; //Black == 1 , White == 0
};

double *get_database_in(char *file);

struct letter_bin *get_in(char *file);
//void train(struct NN *MyNet);