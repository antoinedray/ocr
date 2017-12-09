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
  return(Display_Character_Boxes(img, lines_cleaned,columns)/*text_blocks(img, 1, lines, columns)*/);
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
    {
      top_of_char_line_index = i;
    }
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
          column_list_index++;
        }
        black = 0;
      }
    }
  }
}

SDL_Surface* DisplayLines (SDL_Surface* img, int y[], int nb_elts)
{
  for (int i = 0; i < nb_elts; i++)
    if (y[i] == 2 || y[i] == 1)
      for (int x = 0; x < img->w; x++)
        putpixel(img, x, i, SDL_MapRGB(img->format, 255, 0, 0));
  return img;
}

SDL_Surface* Display_Character_Boxes(SDL_Surface* img, int startlines[],
    int columns[])
  /*
   **   Display the lines and the columns at the same time, using the two lists
   **   Reminder: lines is filled with -1 (nothing),
   **   1 (top char line), 2 (end char line)
   **   columns is filled with the index (in pxl)
   **   of the leftmost/rightmost pxl of a letter, and -1
   */
{
  for (int l = 0; l < img->h; l++)
    if (startlines[l] == 1 || startlines[l] == 2)
      for (int x = 0; x < img->w; x++)
        putpixel(img, x, l, SDL_MapRGB(img->format,255, 0, 0));
  //All red lines are drawn, now we look for the characters
  int index = 0;
  int draw = 0;
  int tmp = 0;
  for (int h = 0; h < img->h; h++)
  {
    if (startlines[h] == 1)//(textlines[h] != -1)
      draw = 1;
    if (draw == 1)
    {
      for(;columns[index] < columns[index+1];index++)
        putpixel(img, columns[index], h, SDL_MapRGB(img->format,255,0,0));
      putpixel(img, columns[index], h, SDL_MapRGB(img->format,255,0,0));
    }
    if (startlines[h] == 2)
    {
      draw = 0;
      tmp = index+1;
    }
    index = tmp;
  }
  return img;
}


/*

   SDL_Surface* text_blocks(SDL_Surface* img, int scale, int lines[], int cols[])
 *
 ** Displays text blocks, depending on scale.
 ** 1: boxes around each letter
 ** 2: boxes around each word
 ** 3: boxes around each paragraph
 *
 {
 if (scale == 1)
 return box_letters(img, lines, cols);
 else
 return img;
 }
 */

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
      for (; cols[tmp] < cols[tmp + 2];)
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
      for (;cols[index] < cols[index + 2];)
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
              draw_line(img, cols[index], cols[index+1], tmp_y + 1);
              stop_checking = 1;
              index += 2;
              break;
            }
          }
        }
      }
    }
  }
  return (img);
}

/*
 **  name: box_fit
 **  description: take the box containing the letter and fit it in a optimal box
 */
SDL_Surface* box_fit(SDL_Surface* img) {
    // Remove bottom
    for(int h = 0; h < img->h; h++) {
        //
    }
}
return (img);
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
