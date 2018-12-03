#ifndef _ERASE_H_
#define _ERASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *window_erase;
GtkWidget *entry_erase;
GtkWidget *scale_erase;

void
erase_util (GtkWidget *widget,
                gpointer   data)
{
    GtkWidget *button_ok;
    GtkWidget *button_cancel;

    GtkWidget *fixed;

    window_erase = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(window_erase), "Eraser");
    gtk_window_set_default_size (GTK_WINDOW(window_erase),400,80);
    gtk_container_set_border_width (GTK_CONTAINER(window_erase),8);

    gtk_widget_show_all(window_erase);
}

#endif