// seg.h

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include"../mysdl/mysdl.h"
#include"../preproc/preproc.h"

void char_detection(SDL_Surface* img, int list[], int res[]);
SDL_Surface* Display_Character_Boxes(SDL_Surface* img, int startlines[],
        int columns[]);
SDL_Surface* Line_Detection(SDL_Surface* img);
SDL_Surface* DisplayLines (SDL_Surface* img, int y[], int nb_elts);
int checklines(int l[], int nb_elts, int res[]);

#endif
