/*
**  OCR 404
**  file: main.c
**  description: link all the parts together and run everything
*/

# include <gtk/gtk.h>
# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "ui/ui.h"
# include "mysdl/mysdl.h"
# include "preproc/preproc.h"
# include "segmentation/segmentation.h"
# include "neuralnet/data_base.h"

GtkWidget *window;

/*
**  name: run_convert
**  description: This function is called when the "convert" button is pressed
**      on the gtk interface, it is the function that will run all the OCR
**      functions.
*/
void run_convert(GtkButton* convert)
{
  // We close the file-choser window
  gtk_button_set_label (convert, "CONVERTING...");
  gtk_widget_destroy (window);

  // We start SDL and load the image
  init_sdl();
  gchar* file = get_filename();
  SDL_Surface* image = load_image(file);
  SDL_Surface* screen = NULL;

  /* Pre-processing
   * The 2nd arg of BnW is the multiplier of the split
   * If split set to 0 then img not splited
   */
  image = grayscale(image);
  //image = contrast(image);
  image = blackAndWhite(image, 0);

  // For testing purposes
  whole_segmentation(image);
  screen = display_image(image);
  SDL_FreeSurface(screen);
  SDL_Quit();
}

void OCR(struct letter **l, int nb_letters)
{
  double resul_mat [16*16];
  struct NN *mynet = loadNN("result");
  for (int i = 0; i < nb_letters; i++)
  {
    resizePixels(l[i]->mat, resul_mat, l[i]->width, l[i]->height, 16, 16);
    //FIXME we have l[i]->space_after and l[i]->newline to play with.
    double *output = feedforward(mynet, resul_mat);
    char *tmp = get_char(66, output);
    //FIXME;
  }
}

/*
**  PLEASE DO NOT MODIFY
**  description: The main function only run the gtk+3 ui
*/
int main (int argc, char *argv[])
{
  GdkPixbuf *icon;
  gtk_init (&argc, &argv);
  window = create_window ();
  icon = create_pixbuf();
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  gtk_widget_show_all (window);
  gtk_main ();
  return 0;
}
