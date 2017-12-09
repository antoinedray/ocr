/*
 *  SEGMENTATION
 *  file: segmentation.c
 *  description: file containing all that has to do with the segmentation
 *  process
 */

#include "segmentation.h"
#include "../imageformatting/structs.h"


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
  return(text_blocks(img, 1, lines_cleaned, columns));
}


int           Line_Detection(SDL_Surface* img, int list_lines[])
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
          //consider curr line to be a line written on
          //if at least 2 pixels follow each other
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

SDL_Surface* box_letters(SDL_Surface* img, int lines[], int cols[])
{ //Boxes every letter of the text
  int y;
  int tmp;
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
              draw_line(img, cols[index], cols[index+1], tmp_y);
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

/*
 **  name: box_fit
 **  desc: take the box containing the letter and fit it in an optimal box
 */
struct letter* box_fit(struct letter* img) 
{
  //FIXME
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

int space_threshold(int cols[])
{
	int max_sp = 0;
	for (size_t i = 1; i < sizeof(cols)/sizeof(int); i++)
		if (cols[i] - cols[i-1] > maxsp)
			max_sp = cols[i] - cols[i-1];
	return max_sp;
}

int is_space(int pos1, int pos2, int threshold)
{
	if (pos2 - pos1 < threshold)
		return 0;
	return 1;
}
