#include <stdio.h>
#include <stdlib.h>
#include "../mysdl/mysdl.h"

struct BIN_Matrix *IMGtoBIN(SDL_Surface* img)
{  
	Uint8 r;
	Uint8 g;
	Uint8 b;
	int height = img->h;
    int width = img->w;
    int *mat = calloc(width*height, sizeof(int));
    for(int h = 0; height > h; h++)
    {
        for (int w = 0; width > w; w++)
        {
            SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);
            if (r ==255)
                mat[w + h * width] = 0;
            else
                mat[w + h * width] = 1;
        }
    }
    struct BIN_Matrix *bin = malloc(sizeof(struct BIN_Matrix));
    bin->mat = mat;
    bin->lines = height;
    bin->cols = width;
    return bin;
}

struct *letter_bin(struct BIN_Matrix *mat){
	struct letter_bin *l = malloc(sizeof(struct letter_bin));
	l->len = mat->height*mat->width;
	l->inputs = mat->mat;
}
struct *letter_bin get_letter(SDL_Surface* img){
	
}
