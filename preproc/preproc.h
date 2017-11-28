/*
 *  PREPROC
 *  file: preproc.h
 *  description: header of preprocessing
 */

#ifndef PREPROC_H_
#define PREPROC_H_

#include"../mysdl/mysdl.h"

SDL_Surface *grayscale(SDL_Surface* im);
SDL_Surface *otzu(SDL_Surface* img);
SDL_Surface *contrast(SDL_Surface* img);
SDL_Surface *split(SDL_Surface* img);
#endif
