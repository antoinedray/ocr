# include "../segmentation/segmentation.h"
# include "../mysdl/mysdl.h"

struct text
{
  struct letter* **mat;
  int lines_nb;
  int nb_letters;
}

SDL_Surface* line_detection(SDL_Surface* img)
{
  Uint8 pxlcolor;
  Uint32 pxl;
  for (int
}
