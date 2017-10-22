// pixel_operations.h
 
# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
#include <stdlib.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void char_detection(SDL_Surface* img, int list[], int res[]);
struct BIN_Matrix{int lines; int cols; int *mat;};
SDL_Surface* Display_Character_Boxes(SDL_Surface* img, int startlines[],
        int columns[]);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* Grayscale(SDL_Surface* image);
SDL_Surface *BlackNWhite(SDL_Surface* image);
struct BIN_Matrix *Otzu(SDL_Surface* img);
SDL_Surface* Line_Detection(SDL_Surface* img);
SDL_Surface* DisplayLines (SDL_Surface* img, int y[], int nb_elts);
struct BIN_Matrix *IMGtoBIN(SDL_Surface* img);
int checklines(int l[], int nb_elts, int res[]);
# endif
