/*
**  SEGMENTATION
**  file: segmentation.c
**  description: file containing all that has to do with the segmentation
**  process
*/
# include "segmentation.h"
# include <err.h>

SDL_Surface* whole_segmentation(SDL_Surface* img)
{
  int lines[img->h];
  Line_Detection(img, lines);
  int height = img->h;
  int lines_cleaned[height];
  checklines(lines, height, lines_cleaned);
  int columns[(img->w)*3];
  for (int x = 0; x < img->w; x++)
    columns[x] = -1;
  char_detection(img, lines_cleaned, columns);
  //int nb_letters = get_number_letters(img, columns);
  //int nb_lines = get_number_lines(img, lines_cleaned);
  struct letter **l = create_letter_list(img, lines_cleaned, columns);
  printf("letter[0]->coord_x[0] = %i\n", l[0]->coord_x[0]);
  printf("letter[0]->coord_x[1] = %i\n", l[0]->coord_x[1]);
  printf("letter[0]->coord_y[0] = %i\n", l[0]->coord_y[0]);
  printf("letter[0]->coord_y[1] = %i\n", l[0]->coord_y[1]);
  return(text_blocks(img, 1, lines_cleaned, columns));
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
  //            warn("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
              struct letter* l = init_letter(cols[index], cols[index+1], tmp_y,
                  img);
    //          warn("############################################");
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

SDL_Surface* draw_line(SDL_Surface* img, int start_x, int end_x, int y)
{ //Draws a line on img, at height y, between points s_x and end_x
  for (; start_x < end_x; start_x++)
    putpixel(img, start_x, y, SDL_MapRGB(img->format, 255, 0, 0));
  return (img);
}

SDL_Surface* draw_column(SDL_Surface* img, int start_y, int end_y, int x)
{ //Draws a column on img, at width x, between points s_y and end_y
  for (; start_y < end_y; start_y++)
    putpixel(img, x, start_y, SDL_MapRGB(img->format, 255, 0, 0));
  return (img);
}


int get_number_letters(SDL_Surface* img, int cols[])
{
  int count_letters = 0;
  int tmp;
  int count_it = 1;
  for (tmp = 0; tmp < img->w; tmp++)
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
  Uint8 r, g, b;
  int height = l->height;
  int width = l->width;
  int max = height > width ? height : width;
  double *mat = calloc(width * height, sizeof(double));
  warn("malloced");
  for(int i = l->coord_y[0]; i < l->coord_y[1]; i++)
  {
    for (int j = l->coord_x[0]; j < l->coord_x[1]; j++)
    {
      SDL_GetRGB(getpixel(img, j, i),img->format,&r,&g,&b);
      if (r == 0)
        mat[(j - l->coord_x[0]) + (i - l->coord_y[0]) * max] = 1.111111;
      else
        mat[(j - l->coord_x[0]) + (i - l->coord_y[0]) * max] = 0.0;
    }
  }

  for (int n =0; n < l->height; n++)
  {
    for (int j = 0; j < l->width; j++)
    {
      printf("| %f ", mat[j + n * width]);
    }
    printf("|\n");
  }
  printf("\n");

  l->mat = mat;
}

/*
void binarize_letter(SDL_Surface* img, struct letter* l)
{
  printf("l->height = %i\n", l->height);
  printf("l->width = %i\n", l->width);
  printf("l->coord_x[0] = %i\n", l->coord_x[0]);
  printf("l->coord_x[1] = %i\n", l->coord_x[1]);
  printf("l->coord_y[0] = %i\n", l->coord_y[0]);
  printf("l->coord_y[1] = %i\n", l->coord_y[1]);
  double **mat = calloc(sizeof(*mat), l->height);
  for (int i = 0; i < l->height; i++)
    mat[i] = calloc(sizeof(**mat),l->width);
  int x;
  int mat_x = 0;
  int y;
  int mat_y;
  Uint32 pxl;
  Uint8 color;
  for (x = l->coord_x[0]; x < l->coord_x[1]; x++, mat_x++)
  {
    warn("first loop");
    for (y = l->coord_y[0], mat_y = 0; y < l->coord_y[1]; y++, mat_y++)
    {
      pxl = getpixel(img,x,y);
      SDL_GetRGB(pxl, img->format, &color, &color, &color);
      warn("second loop, color is %i", color);
      if (color == 0)
      {
        mat[mat_y][mat_x] = 1.111111;
        warn("m[%i][%i] = %f", mat_y, mat_x, mat[mat_y][mat_x]);
        warn("x = %i, y = %i", x, y);
      }
      else
      {
        mat[mat_y][mat_x] = 0.0;
        warn("m[%i][%i] = %f", mat_y, mat_x, mat[mat_y][mat_x]);
        warn("x = %i, y = %i", x, y);
      }
    }
    warn("finishing second loop");
  }
  for (int n =0; n < l->height; n++)
  {
    for (int j = 0; j < l->width; j++)
    {
      printf("| %f", mat[n][j]);
    }
    printf("|\n");
  }
  printf("\n");
  warn("setting l->mat");
  l->mat = mat;
}*/
