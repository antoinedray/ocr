# include "structs.h"
# include "segmentation.h"

struct letter* init_letter(int topleft_x, int topleft_y, int botright_x, int botright_y, SDL_Surface* img)
{
  struct letter* l = malloc(sizeof(struct letter));
  l->coord_x[0] = topleft_x;
  l->coord_x[1] = botright_x;
  l->coord_y[0] = topleft_y;
  l->coord_y[1] = botright_y;
  l->height = botright_x - topleft_x;
  l->width = botright_y - topleft_y;
  binarize_letter(img, l);
  return l;
}

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
      SDL_GetRGB(pxl, img->format, &color, &color, &color);
      if (color == 0)
        mat[y][x] = 1;
      else
        mat[y][x] = 0;
    }
  }
}

struct text* init_text(SDL_Surface* img)
{
  struct text* t = malloc(sizeof(struct text));
  t->lines_nb = get_number_lines(img);
  t->nb_letters = get_number_letters(img);
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
