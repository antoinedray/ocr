#include <stdio.h>
#include <stdlib.h>
#include "../mysdl/mysdl.h"

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

double *get_database_in

double *get_inputs_NN(struct letter_bin *l){
	return l->mat;
}
