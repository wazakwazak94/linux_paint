#include <stdio.h>
#include <gtk/gtk.h>

static void 
activate (GtkApplication* app,
          gpointer        user_data)
{
    GtkWidget *window;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Linus Paint");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_window_show_all (window);
}
