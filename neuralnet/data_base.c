#include <stdio.h>
#include <err.h>
#include "data_base.h"

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
**  size_letter = height*width
**  before hand, DB must be 32*32.
**  the mat will have the following struct:
**      nb_fonts*nb_characters(62 by default + 13 special chars) = lines,
**  order : same font -> maj / min / num
*/

double *get_database_in(char *file) {
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
    size_t nbChars = 75;
    FILE *fp = fopen("database/data.txt", "r");
    if (fp == NULL) {
        printf("Data file does not exists");
        return;
    }
    //init_sdl();
    char line[64];
    size_t i = 0;
    double **output_train = get_database_out(nbChars);
    while(fscanf(fp, "%s", line) != EOF) {
        char filename[100] = "";
        char *location = "database/";
        strcat(filename,location);
        strcat(filename,line);
        double *train = get_database_in(filename);
        backprop(MyNet,train,output_train[i]);
        free(train);
        if (i == nbChars - 1)
            i = 0;
        else
            i++;
    }
    //IMG_Quit();
    for(size_t j = 0; j < nbChars; j++)
        free(output_train[j]);
    free(output_train);
    fclose(fp);
}
