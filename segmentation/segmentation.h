/*
 *  SEGMENTATION
 *  file: segmentation.h
 *  description: header for segmentation
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

# include "../mysdl/mysdl.h"

void char_detection(SDL_Surface* img, int list[], int res[]);
SDL_Surface* Display_Character_Boxes(SDL_Surface* img, int startlines[],
        int columns[]);
int Line_Detection(SDL_Surface* img, int lines[]);
SDL_Surface* DisplayLines (SDL_Surface* img, int y[], int nb_elts);
SDL_Surface* text_blocks(SDL_Surface* img, int scale, int lines[], int cols[]);
SDL_Surface* box_letters(SDL_Surface* img, int lines[], int cols[]);
SDL_Surface* draw_line(SDL_Surface* img, int start_x, int end_x, int y);
SDL_Surface* draw_column(SDL_Surface* img, int start_y, int end_y, int x);
int checklines(int l[], int nb_elts, int res[]);
SDL_Surface* whole_segmentation(SDL_Surface* img);
#endif
