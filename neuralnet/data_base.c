#include <stdio.h>
#include <stdlib.h>
#include "../mysdl/mysdl.h"
#include "data_base.h"

static struct letter_bin *IMGtoBIN(SDL_Surface* img)
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int height = img->h;
    int width = img->w;
    double *mat = calloc(width*height, sizeof(double));
    for(int h = 0; height > h; h++)
    {
        for (int w = 0; width > w; w++)
        {
            SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);
            if (r ==255)
                mat[w + h * width] = 0.0;
            else
                mat[w + h * width] = 1.0;
        }
    }
    struct letter_bin *bin = malloc(sizeof(struct BIN_Matrix));
    bin->inputs = mat;
    bin->len = height*width;
    return bin;
}
/*     
     *FOR ANTOINE*
 
size_letter = height*width
before hand, DB must be 32*32.
the mat will have the following struct: nb_fonts*nb_characters(62 by default) = lines,
32*32 = columns
order : aaaaaabbbbbb....AAAAABBBBBB...11111112222222... 
*/ 
double **get_database_in(size_t nb_fonts,size_t nb_characters){//add here if needed
	double **inputs = malloc(sizeof(double*)*nb_fonts*nb_characters);
	for(size_t i = 0; i < nb_fonts*nb_characters; i++){
		//get the letter_img
		SDL_Surface* letter_img;
		struct letter_bin *letter = IMGtoBIN(letter img);
		inputs[i] = l->inputs;
	}	
}

double **get_database_out(size_t nb_characters){
	double **outputs = malloc(sizeof(double*)*nb_characters);
	for(size_t i = 0; i < nb_characters;i++){
		outputs[i] = calloc(sizeof(double)*nb_characters);
		outputs[i][i] = 1.0;
	}
	return output;
}

