# include "../segmentation/segmentation.h"
# include "../mysdl/mysdl.h"

/*struct text
{
  struct letter* **mat;
  int lines_nb;
  int nb_letters;
}*/

int       line_detection(SDL_Surface* img)
{
  Uint8   pxlcolor;
  Uint32  pxl;
  int     index = 0;
  int     x;
  int     y;
  int     prev_pxl_black = 0;
  int     lines [img->h];
  for (y = 0; y < img->h; y++)
  {
    for (x = 0, prev_pxl_black = 0; x < img->w; x++)
    {
      pxl = getpixel(img, x, y);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
      {
        if (prev_pxl_black == 1)
        {
          printf("lines[%i] = %i.\n",index,y);
          lines[index] = y;
          index++;
          break;
        }
        else
          prev_pxl_black = 1;
      }
      else
        prev_pxl_black = 0;
    }
  }
  printf("I beg you please reach this point.");
  index++;
  lines[index] = -42;
  return lines[img->h];
}

int    *clean_lines(int* lines)
{
  int   index;
  int   index_clean     = 1;
  int  *lines_cleaned   = malloc(sizeof(int));
  lines_cleaned[0] = lines[0];
  for (index = 1; lines[index + 1] != -42; index++)
  {
    if (lines[index] + 1 != lines[index + 1])
    {
      lines_cleaned[index_clean] = lines[index];
      index++;
      index_clean++;
      lines_cleaned[index_clean] = -1;
      index_clean++;
      lines_cleaned[index_clean] = lines[index];
      index_clean++;
    }
  }
  lines_cleaned[index_clean] = lines[index];
  lines_cleaned[index_clean + 1] = -1;
  lines_cleaned[index_clean + 2] = -42;
  return lines_cleaned;
}

/*
int* column_detection(SDL_Surface* img, int* lines)
{
  Uint8 pxlcolor;
  Uint32 pxl;
  int x;
  int index;
  int* cols = malloc(sizeof(int));
  for (index = 0; lines[index] != NULL; index++)
  {
    //FIXME
  }















  return cols;
}
*/
