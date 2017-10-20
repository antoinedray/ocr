/*
	OCR 404
	main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "ui.h"
#include "pixel_operations.h"

GtkWidget *window;

void print_matrix(int mat[], int lines, int cols)
{
    for(int l = 0; l < lines; l++)
    {
        for(int c = 0; c < cols; c++)
            printf("%i", mat[c+l*cols]);
        printf("\n");
    
    }
}

void run_convert(GtkButton* convert, gpointer user_data)
{
	// We close the file-choser window
	gtk_widget_destroy (window);

	init_sdl();
	gchar* file = get_filename();
	SDL_Surface* image = load_image(file);
	SDL_Surface* screen;

	// Pre-processing
	image = Grayscale(image);
	image = BlackNWhite(image);
		// Binariztion
    struct BIN_Matrix *bin = IMGtoBIN(image);
    //print_matrix(bin->mat,bin->lines,bin->cols); // For testing purposes    

	screen = display_image(image);
	SDL_FreeSurface(screen);
	SDL_Quit();
}


int main (int argc, char *argv[])
{
 	GdkPixbuf *icon;
	
	gtk_init (&argc, &argv);

	window = create_window ();

	icon = create_pixbuf();  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	gtk_widget_show_all (window);

	gtk_main ();
}
