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
  int **mat; //Contains the binarized 32*32 letter
}

struct letter* initLetter(struct letter* l)
{
  l = malloc(sizeof(struct letter));
  l
}

