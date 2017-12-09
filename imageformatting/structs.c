#include "structs.h"

void binarize_letter(SDL_Surface* img, struct letter* l)
{
  double **mat = calloc(sizeof(l->height * l->width));
  int x;
  int y;
  Uint32 pxl;
  Uint8 color;
  for (x = l->coord_x[0]; x < l->coord_x[1]; x++)
  {
    for (y = l->coord_y[0]; y < l->coord_y[1]; y++)
    {
      pxl = getpixel(img,x,y);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
        mat[y][x] = 1;
      else
        mat[y][x] = 0;
    }
  }
}

struct text* init_text(SDL_Surface* img)
{
  struct text* t = calloc(sizeof(struct text));
  t->lines_nb = get_number_lines(img); //FIXME
  t->nb_letters = get_number_letters(img); //FIXME
  //FIXME add letters in the mat
  int i;
  int j;
  for (i = 0; i < t->lines_nb; i++)
  {
    for (j = 0; j < t->nb_letters; j++)
    {
      //FIXME
    }
  }
}

int get_number_lines(SDL_Surface* img)
{
  int lines [img->h];
  int cols [img->w];
  //FIXME
}

//size of "n" for " " recognition
