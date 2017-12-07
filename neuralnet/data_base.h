#include <stdio.h>
#include <stdlib.h>
#include "../mysdl/mysdl.h"

struct BIN_Matrix{
	int lines;
	int cols;
	int *mat;
};

struct letter_bin{
	size_t len;
	int *inputs;
};

struct letter_bin get_letter(SDL_image *img);
