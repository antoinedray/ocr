#include <stdio.h>
#include "../mysdl/mysdl.h"

struct text
{
  struct letter* **text;
  int lines_nb;
  int nb_letters;
};

struct letter
{
  int coord_x [2];
  int coord_y [2];
  int height; //int coord_topleft
  int width; //int coord_botright
  double **mat; //Contains the binarized height*width letter in 0 and 1s
};

struct letter* init_letter(int topleft_x, int topleft_y, int botright_x, int botright_y, SDL_Surface* img);
void binarize_letter(SDL_Surface* img, struct letter* l);
struct text* init_text(SDL_Surface* img);
int get_number_letters(SDL_Surface* img);
int get_number_lines(SDL_Surface* img);
