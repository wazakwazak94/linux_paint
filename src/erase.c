#include "global.h"
#include "erase.h"
#include "thickness.h"

void 
set_erase_thickness (GtkWidget *widget,
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
        gtk_range_set_value (GTK_RANGE(scale_erase),(gdouble)data_);
    }
    else
    {
        g_print ("enter the number between 1~100\n");
    }
}

void
set_erase_scroll (GtkScale *scale,
                  gdouble   value,
                  gpointer  user_data)
{
    gdouble value_ = gtk_range_get_value (GTK_RANGE(scale_erase));
    char pos_[4];
    sprintf(pos_,"%d",(int)value_);

    thickness_ = (gint)value_;
    temp_th = thickness_;
    gtk_entry_set_text(GTK_ENTRY(entry_erase),(const gchar *)pos_);
}

void
close_erase_window (void)
{
    if(window_erase){
        thickness_ = temp_th;
        gtk_widget_destroy (window_erase);
    }
}

void
save_close_erase_window (void)
{
    if(window_erase){
        set_thickness(entry_th,entry_th);
        gtk_widget_destroy (window_erase);
    }
}

void
erase_util (GtkWidget *widget,
            gpointer   data)
{
    GtkWidget *button_ok;
    GtkWidget *button_cancel;

    GtkWidget *fixed;

    temp_th = thickness_;
    sprintf(char_th,"%d",(int)thickness_);

    window_erase = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(window_erase), "Eraser");
    gtk_window_set_default_size (GTK_WINDOW(window_erase),400,80);
    gtk_container_set_border_width (GTK_CONTAINER(window_erase),8);

    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER(window_erase),fixed);

    scale_erase = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1,100,1);
    gtk_widget_set_size_request (GTK_WIDGET (scale_erase), 200, -1);
    g_signal_connect (scale_erase, "format_value", G_CALLBACK(set_erase_scroll), scale_erase);

    entry_erase = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_erase),(const gchar *)char_th);
    g_signal_connect (entry_erase, "activate", G_CALLBACK(set_erase_thickness), entry_erase);

    button_cancel = gtk_button_new_with_label("Cancel");
    g_signal_connect (button_cancel, "clicked", G_CALLBACK(close_erase_window),NULL);
  
    button_ok = gtk_button_new_with_label ("Ok");
    g_signal_connect (button_ok, "clicked", G_CALLBACK(save_close_erase_window),NULL);

    gtk_fixed_put (GTK_FIXED(fixed), entry_erase, 215, 15);
    gtk_fixed_put (GTK_FIXED(fixed), scale_erase, 0, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_cancel, 320,50);
    gtk_fixed_put(GTK_FIXED (fixed), button_ok, 285,50);

    gtk_widget_show_all(window_erase);
}