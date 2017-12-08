//Imageformatting.c : New implementation of basically every segmentation func

# include "imageformatting.h"

struct text
{
  struct letter ***mat;
  int lines_nb;
  struct letter *letters_on_line;
  int nb_letters;
}

struct letter
{
  int coord [4];
  int height; //int coord_topleft
  int width; //int coord_botright
//int **mat; //Contains the binarized height*width letter in 0 and 1s
}

struct letter* initLetter(int topleft_x, int topleft_y,
                          int botright_x, int botright_y)
{
  struct letter* l = malloc(sizeof(struct letter));
  l->coord[0] = topleft_x;
  l->coord[1] = topleft_y;
  l->coord[2] = botright_x;
  l->coord[3] = botright_y;
  l->height = botright_x - topleft_x;
  l->width = botright_y - topleft_y;
}

