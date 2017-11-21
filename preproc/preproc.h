/*
 *  PREPROC
 *  file: preproc.h
 *  description: header of preprocessing
 */

#ifndef PREPROC_H_
#define PREPROC_H_

#include"../mysdl/mysdl.h"

SDL_Surface* Grayscale(SDL_Surface* image);
SDL_Surface *BlackNWhite(SDL_Surface* image);
SDL_Surface *Otzu(SDL_Surface* img);
#endif
