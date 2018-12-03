#ifndef _THICKNESS_H_
#define _THICKNESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern cairo_surface_t *surface;

gint thickness_;
gint temp_th;
char char_th[4];

GtkWidget *window_th;
GtkWidget *entry_th;
GtkWidget *scale_th;

void 
set_thickness (GtkWidget *widget,
               GtkWidget *entry)
{
    const gchar *entry_text;
    int data_;

    entry_text = gtk_entry_get_text (GTK_ENTRY(entry));
    data_ = (int)(atoi(entry_text));

    if(data_ > 0 && data_<101)
    {
        thickness_ = (gint)data_;
        temp_th = thickness_;
        gtk_range_set_value (GTK_RANGE(scale_th),(gdouble)data_);
    }
    else
    {
        g_print ("enter the number between 1~100\n");
    }
}

void
set_th_scroll (GtkScale *scale,
               gdouble   value,
               gpointer  user_data)
{
    gdouble value_ = gtk_range_get_value (GTK_RANGE(scale_th));
    char pos_[4];
    sprintf(pos_,"%d",(int)value_);

    thickness_ = (gint)value_;
    temp_th = thickness_;
    gtk_entry_set_text(GTK_ENTRY(entry_th),(const gchar *)pos_);
}

void
close_th_window (void)
{
    if(window_th){
        thickness_ = temp_th;
        gtk_widget_destroy (window_th);
    }
}

void
save_close_th_window (void)
{
    if(window_th){
        set_thickness(entry_th,entry_th);
        gtk_widget_destroy (window_th);
    }
}

void
thickness_util (GtkWidget *widget,
                gpointer   data)
{
    GtkWidget *button_ok;
    GtkWidget *button_cancel;

    GtkWidget *fixed;

    temp_th = thickness_;
    sprintf(char_th,"%d",(int)thickness_);

    window_th = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(window_th), "thickness");
    gtk_window_set_default_size (GTK_WINDOW(window_th),400,80);
    gtk_container_set_border_width (GTK_CONTAINER(window_th),8);

    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER(window_th),fixed);

    scale_th = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1,100,1);
    gtk_widget_set_size_request (GTK_WIDGET (scale_th), 200, -1);
    g_signal_connect (scale_th, "format_value", G_CALLBACK(set_th_scroll), scale_th);

    entry_th = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_th),(const gchar *)char_th);
    g_signal_connect (entry_th, "activate", G_CALLBACK(set_thickness), entry_th);

    button_cancel = gtk_button_new_with_label("Cancel");
    g_signal_connect (button_cancel, "clicked", G_CALLBACK(close_th_window),NULL);
  
    button_ok = gtk_button_new_with_label ("Ok");
    g_signal_connect (button_ok, "clicked", G_CALLBACK(save_close_th_window),NULL);

    gtk_fixed_put (GTK_FIXED(fixed), entry_th, 215, 15);
    gtk_fixed_put (GTK_FIXED(fixed), scale_th, 0, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_cancel, 320,50);
    gtk_fixed_put(GTK_FIXED (fixed), button_ok, 285,50);

    gtk_widget_show_all(window_th);
}

#endif