/*
 * OCR 404
 * file: main.c
 * description: link all the parts together and run everything
 */

#include <dirent.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "ui/ui.h"
#include "mysdl/mysdl.h"
#include "preproc/preproc.h"
#include "segmentation/segmentation.h"

GtkWidget *window;

void run_convert(GtkButton* convert)
{
  // We close the file-choser window
  gtk_button_set_label (convert, "CONVERTING...");
  gtk_widget_destroy (window);

  // We start SDL and load the image
  init_sdl();
  gchar* file = get_filename();
  SDL_Surface* image = load_image(file);
  SDL_Surface* screen;

  /* Pre-processing
   * The 2nd arg of BnW is the multiplier of the split
   * If split set to 0 then img not splited
   */
  image = grayscale(image);
  //image = contrast(image);
  image = blackAndWhite(image, 0);

  // For testing purposes
  image = Line_Detection(image);
  screen = display_image(image);
  SDL_FreeSurface(screen);
  SDL_Quit();
}

// The main function only run the gtk+3 ui, PLEASE DO NOT MODIFY
int main (/* int argc, char *argv[] */)
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
