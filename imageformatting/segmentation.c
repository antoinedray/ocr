# include "../segmentation/segmentation.h"
# include "../mysdl/mysdl.h"

/*struct text
{
  struct letter* **mat;
  int lines_nb;
  int nb_letters;
}*/

int* line_detection(SDL_Surface* img)
{
  Uint8 pxlcolor;
  Uint32 pxl;
  int index;
  int x;
  int y;
  int black_pixels_on_line;
  int* lines = malloc(sizeof(int));
  for (y = 0; y < img->h; y++)
  {
    black_pixels_on_line = 0;
    for (x = 0; x < img->w; x++)
    {
      pxl = getpixel(img, x, y);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (black_pixels_on_line >= 100)
      {
        lines[index] = y;
        index++;
        break;
      }
    }
  }
  return lines;
}

int* clean_lines(int* lines)
{
  int index;
  int index_clean = 1;
  int* lines_cleaned = malloc(sizeof(int));
  lines_cleaned[0] = lines[0];
  for (index = 1; lines[index + 1] != NULL; index++)
    if (lines[index] + 1 != lines[index + 1])
    {
      lines_cleaned[index_clean] = lines[index];
      index++;
      index_clean++;
      lines_cleaned[index_clean] = lines[index];
    }
  return lines_cleaned;
}

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
