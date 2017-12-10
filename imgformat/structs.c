# include "structs.h"
# include "../segmentation/segmentation.h"

struct letter* init_letter(int topleft_x, int botright_x, int botright_y, SDL_Surface* img)
{
  struct letter* l = malloc(sizeof(struct letter));
  int line_has_black = 1;
  Uint32 pxl;
  Uint8 pxlcolor;
  int going_up;
  for (going_up = botright_y; line_has_black != 0; going_up--)
  {
    line_has_black = 0;
    for (int tmp = topleft_x; tmp < botright_x; tmp++)
    {
      pxl = getpixel(img, tmp, going_up);
      SDL_GetRGB(img, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
        line_has_black = 1;
    }
  }
  int topleft_y = going_up;
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
  int lines[img->h];
  int cols[img->w * 3];
  for (int tmp = 0; x < img->w * 3; x++)
    cols[tmp] = -1;
  Line_Detection(img, lines); //fills "lines" with 1 and -1
  int lines_final[img->h];
  checklines(lines, img->h, lines_final);
  char_detection(img, lines_final, cols);
  struct text* t = malloc(sizeof(struct text));
  t->lines_nb = get_number_lines(img, lines_final);
  t->nb_letters = get_number_letters(img, cols);
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
