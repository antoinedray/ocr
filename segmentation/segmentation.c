/*
**  SEGMENTATION
**  file: segmentation.c
**  description: file containing all that has to do with the segmentation
**  process
*/
#include "segmentation.h"
#include <err.h>

SDL_Surface* whole_segmentation(SDL_Surface* img)
{
  int lines[img->h];
  Line_Detection(img, lines);
  int height = img->h;
  int lines_cleaned[height];
  checklines(lines, height, lines_cleaned);
  int columns[(img->w) * 3];
  for (int x = 0; x < img->w * 3; x++)
    columns[x] = -1;
  char_detection(img, lines_cleaned, columns);
  int nb_letters = get_number_letters(img, columns);
  printf("This image has %i letters\n", nb_letters);
  int nb_lines = get_number_lines(img, lines_cleaned);
  printf("It also has %i lines, according to my great intellect.\n", nb_lines);
  struct letter **l = create_letter_list(img, lines_cleaned, columns);
  printf("letter[0]->coord_x[0] = %i\n", l[0]->coord_x[0]);
  printf("letter[0]->coord_x[1] = %i\n", l[0]->coord_x[1]);
  printf("letter[0]->coord_y[0] = %i\n", l[0]->coord_y[0]);
  printf("letter[0]->coord_y[1] = %i\n", l[0]->coord_y[1]);
  /*double resized_inputs[1024];
  struct letter_bin *l_b = resize_image(l[0]->mat, resized_inputs,
      l[0]->width, l[0]->height);
  for (int n = 0; n < 32; n++)
  {
    for (int j = 0; j < 32; j++)
    {
      printf("| %f ", l_b->inputs[j + n * 32]);
    }
    printf("|\n");
  }
  printf("\n");*/
  return(text_blocks(img, 1, lines_cleaned, columns));
}

struct letter_bin *resize_image(double inputs[], double resized_inputs[],
    int width , int height)
{
  int dim = 32;
  //double resized_inputs[1024];
  double xscale = (float)(dim) / width;
  double yscale = (float)(dim) / height;
  double threshold = 0.5 / (xscale * yscale);
  double yend = 0.0;
  for (int f = 0; f < dim; f++)
  { // y on output
    double ystart = yend;
    yend = (f + 1) / yscale;
    if (yend >= height)
      yend = height - 0.000001;
    double xend = 0.0;
    for (int g = 0; g < dim; g++)
    { // x on output
      double xstart = xend;
      xend = (g + 1) / xscale;
      if (xend >= width)
        xend = width - 0.000001;
      double sum = 0.0;
      for (int y = (int)ystart; y <= (int)yend; ++y)
      {
        double yportion = 1.0;
        if (y == (int)ystart)
          yportion -= ystart - y;
        if (y == (int)yend)
          yportion -= y+1 - yend;
        for (int x = (int)xstart; x <= (int)xend; ++x)
        {
          double xportion = 1.0;
          if (x == (int)xstart)
            xportion -= xstart - x;
          if (x == (int)xend)
            xportion -= x+1 - xend;
          sum += inputs[x + y*width] * yportion * xportion;
        }
      }
      resized_inputs[g + f * dim] = (sum > threshold) ? 1 : 0;
    }
  }
  struct letter_bin *bin = malloc(sizeof(struct letter_bin));
  bin->inputs = resized_inputs;
  bin->len = dim * dim;
  return bin;
}

int Line_Detection(SDL_Surface* img, int list_lines[])
{
  Uint32      pxl;
  Uint8       pxlcolor;
  for (int x = 0; x < img->h; x++)
    list_lines[x] = -1;
  int         i = 0; //list index
  int         prev_pxl = 0;
  for (int y = 0; y < img->h; y++)
  {
    for (int x = 0; x < img->w; x++)
    {
      pxl = getpixel(img, x, y);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
      {
        if(prev_pxl == 1) //is previous pixel black?
        {
          list_lines[y] = 1;
          i++;
          break;
        }
        else
          prev_pxl = 1;
      }
      else
        prev_pxl = 0;
    }
  }
  return list_lines[img->h];
}


//removes lines from list when less than 5 consecutive line
int checklines(int l[], int nb_elts, int res[])
{
  for (int x = 0; x < nb_elts; x++)
    res[x] = -1;
  int consecutive_lines = 0;
  int top = 0;
  int bot = 0;
  for (int index = 0; index < nb_elts; index++)
  {
    if (l[index] == 1)
    {
      if (l[index] == l[index+1] && top == 0)
      {
        top = index;
        consecutive_lines++;
      }
      else if (l[index] == l[index+1] && top != 0)
        //top already found, continue onwards to find bot
      {
        consecutive_lines++;
        continue;
      }
      else // line is not followed by any other
      {
        if (l[index] == l[index-1] && bot == 0)
          //it's the last of a sequence (bot of letter)
        {
          bot = index;
          consecutive_lines++;
        }
        else if (l[index] == l[index-1] && bot != 0)
          //it's the last of a sequence (bot of letter)
        {
          consecutive_lines++;
          continue;
        }
        else
        {
          consecutive_lines = 0;
          continue; //ignores line for res (line is noise.)
        }
      }

      if (consecutive_lines >= 6)
      {
        res[top] = 1;
        res[bot] = 2;
        top = 0;
        bot = 0;
        consecutive_lines = 0;
      }
    }
  }
  return *res;
}

void char_detection(SDL_Surface* img, int list[], int res[])
{
  int black = 0;
  Uint8 pxlcolor;
  Uint32 pxl;
  int column_list_index = 0;
  int top_of_char_line_index = 0;
  int letter = 0;
  for (int i = 0; i < img->h; i++) //Goes through the line list
  {
    if (list[i] == 1) //We found the top of a char line
      top_of_char_line_index = i;
    if (list[i] == 2)
    {
      for (int x = 0; x < img->w; x++)
      {
        for (int y = top_of_char_line_index; y < i; y++)
        {
          pxl = getpixel(img,x,y);
          SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
          if (pxlcolor == 0)
            black = 1;
        }
        if (black == 1 && letter == 0)
        {
          // Warnx("column_list_index is :%d\n",column_list_index);
          letter = 1;
          res[column_list_index] = x;
          column_list_index++;
        }
        else if (black == 0 && letter == 1)
        {
          // Warnx("column_list_index is :%d\n",column_list_index);
          letter = 0;
          res[column_list_index] = x;
          //res[column_list_index + 1] = -1;
          column_list_index += 1;//2;
        }
        black = 0;
      }
      res[column_list_index] = -42; //EOL char
      column_list_index++;
    }
  }
}

SDL_Surface* text_blocks(SDL_Surface* img, int scale, int lines[], int cols[])
/*
 ** Displays text blocks, depending on scale.
 ** 1: boxes around each letter
 ** 2: boxes around each word
 ** 3: boxes around each paragraph
 */
{
  if (scale == 1)
    return box_letters(img, lines, cols);
  else
    return img;
}

struct letter** create_letter_list(SDL_Surface* img, int lines[], int cols[])
{ //Boxes every letter of the text
  struct letter **list = malloc(sizeof(struct letter)
                                  * get_number_letters(img, cols));
  int y;
  //int tmp; //To not go to next line when we check for top of letters
  int index = 0;
  Uint8 pxlcolor;
  Uint32 pxl;
  int index_list_letter = 0;
  for (y = 0; y < img->h; y++)
  {
    if (lines[y] == 2)
    {
      for (; cols[index] != -42; )
      {
        int stop_checking = 0;
        for (int tmp_y = y; stop_checking != 1; tmp_y--)
        {
          for (int check_x = cols[index]; check_x < cols[index + 1]; check_x++)
          {
            pxl = getpixel(img, check_x, tmp_y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
              struct letter* l = init_letter(cols[index], cols[index+1], tmp_y,
                  img);
              list[index_list_letter] = l;
              index_list_letter++;
              stop_checking = 1;
              index += 2;
              break;
            }
          }
        }
      }
      index++;
    }
  }
  return list;
}


SDL_Surface* box_letters(SDL_Surface* img, int lines[], int cols[])
{ //Boxes every letter of the text
  int y;
  int tmp; //To not go to next line when we check for top of letters
  int index = 0;
  Uint8 pxlcolor;
  Uint32 pxl;
  for (y = 0; y < img->h; y++)
  {
    if (lines[y] == 1)
    {
      tmp = index;
      for (; cols[tmp] != -42; )
      {
        int keep_checking = 1;
        for (int tmp_y = y; keep_checking; tmp_y++)
        {
          for (int check_x = cols[tmp]; check_x < cols[tmp + 1]; check_x++)
          {
            pxl = getpixel(img, check_x, tmp_y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
              draw_line(img, cols[tmp], cols[tmp + 1], tmp_y - 1);
              keep_checking = 0;
              tmp += 2;
              break;
            }
          }
        }
      }
    }
    if (lines[y] == 2)
    {
      for (; cols[index] != -42; )
      {
        int stop_checking = 0;
        for (int tmp_y = y; stop_checking != 1; tmp_y--)
        {
          for (int check_x = cols[index]; check_x < cols[index + 1]; check_x++)
          {
            pxl = getpixel(img, check_x, tmp_y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
              draw_line(img, cols[index], cols[index + 1], tmp_y);
              stop_checking = 1;
              index += 2;
              break;
            }
          }
        }
      }
      index++;
    }
  }
  return img;
}

SDL_Surface* draw_line(SDL_Surface *img, int start_x, int end_x, int y)
{ //Draws a line on img, at height y, between points s_x and end_x
  for (; start_x < end_x; start_x++)
    putpixel(img, start_x, y, SDL_MapRGB(img->format, 255, 0, 0));
  return (img);
}

SDL_Surface* draw_column(SDL_Surface *img, int start_y, int end_y, int x)
{ //Draws a column on img, at width x, between points s_y and end_y
  for (; start_y < end_y; start_y++)
    putpixel(img, x, start_y, SDL_MapRGB(img->format, 255, 0, 0));
  return (img);
}


int get_number_letters(SDL_Surface *img, int cols[])
{
  int count_letters = 0;
  int tmp;
  int count_it = 1;
  for (tmp = 0; tmp < img->w * 3; tmp++)
  {
    if (cols[tmp] < 0)
      continue;
    if (count_it == 1)
    {
      count_letters++;
      count_it = 0;
    }
    else
      count_it = 1;
  }
  return count_letters;
}

int get_number_lines(SDL_Surface* img, int lines[])
{
  int count_lines = 0;
  int tmp;
  for (tmp = 0; tmp < img->h; tmp++)
    if (lines[tmp] == 2)
      count_lines++;
  return count_lines;
}

struct letter* init_letter(int topleft_x, int botright_x, int botright_y,
    SDL_Surface* img)
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
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
        line_has_black = 1;
    }
  }
  int topleft_y = going_up;
  l->space_before = 0;
  l->coord_x[0] = topleft_x;
  l->coord_x[1] = botright_x;
  l->coord_y[0] = topleft_y;
  l->coord_y[1] = botright_y;
  l->height = botright_y - topleft_y;
  l->width = botright_x - topleft_x;
  binarize_letter(img, l);
  return l;
}

void binarize_letter(SDL_Surface* img, struct letter* l)
{
  Uint8 r, g, b;
  int height = l->height;
  int width = l->width;
  int max = height > width ? height : width;
  double *mat = calloc(max * max, sizeof(double));
  for(int i = l->coord_y[0]; i < l->coord_y[1]; i++)
  {
    for (int j = l->coord_x[0]; j < l->coord_x[1]; j++)
    {
      SDL_GetRGB(getpixel(img, j, i),img->format,&r,&g,&b);
      if (r == 0)
        mat[(j - l->coord_x[0]) + (i - l->coord_y[0]) * max] = 1.0;
      else
        mat[(j - l->coord_x[0]) + (i - l->coord_y[0]) * max] = 0.0;
    }
  }
  l->mat = mat;
}

void print_letter(struct letter *l)
{
  printf("l->coord_x[0] = %i\n", l->coord_x[0]);
  printf("l->coord_x[1] = %i\n", l->coord_x[1]);
  printf("l->coord_y[0] = %i\n", l->coord_y[0]);
  printf("l->coord_y[1] = %i\n", l->coord_y[1]);
  printf("l->height = %i\n", l->height);
  printf("l->width = %i\n", l->width);
}
