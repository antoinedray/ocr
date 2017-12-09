#include <stdio.h>
#include "data_base.h"
#include "neural.h"

static struct letter_bin *IMGtoBIN(SDL_Surface* img)
{
  Uint8 r, g, b;
  int height = img->h;
    int width = img->w;
    double *mat = calloc(width * height, sizeof(double));
    for(int h = 0; height > h; h++)
    {
        for (int w = 0; width > w; w++)
        {
            SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);
            if (r == 255)
                mat[w + h * width] = 0.0;
            else
                mat[w + h * width] = 1.0;
        }
    }
    struct letter_bin *bin = malloc(sizeof(struct letter_bin));
    bin->inputs = mat;
    bin->len = height*width;
    return bin;
}

/*
        *FOR STAN*

    What is the use of the structure Bin matrix in your header ?

     *FOR ANTOINE*

size_letter = height*width
before hand, DB must be 32*32.
the mat will have the following struct: nb_fonts*nb_characters(62 by default) = lines,
order : same font -> maj / min / num
*/

static double *get_database_in(char *file) {
    SDL_Surface* letter_sdl = load_image(file);
    struct letter_bin *letter = IMGtoBIN(letter_sdl);
    return letter->inputs;
}

static double **get_database_out(size_t nb_characters){
    double **outputs = malloc(sizeof(double*)*nb_characters);
    for(size_t i = 0; i < nb_characters;i++){
        outputs[i] = calloc(nb_characters, sizeof(double)); // Why ??????
        outputs[i][i] = 1.0; // Why ????
    }
    return outputs;
}

void train(struct NN *MyNet) {
    FILE *fp = fopen("database/data.txt", "r");
    if (fp == NULL) {
        printf("Data file does not exists");
        return;
    }
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
	size_t i = 0;
	double **output_train = get_database_out(62);
    while((linelen = getline(&line, &linecap, fp)) > 0) {
        train = get_database_in(line);
		backprop(MyNet,train,output_train[i]);
        if (i == 61)
			i = 0;
		else
			i += 1 ;
    }
	return;
}
