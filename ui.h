// ui.h
 
# ifndef UI_H_
# define UI_H_
 
# include <stdlib.h>
# include <gtk/gtk.h>

gchar* get_filename();
void run_convert(GtkButton* convert);
void on_open_image(GtkButton* openf, gpointer user_data);
GtkWidget* create_window ();
GdkPixbuf *create_pixbuf();

# endif
