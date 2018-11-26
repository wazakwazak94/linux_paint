#include "util.h"

#define ICON_COLOR_ADDR "/icon/color.png"

void
close_window (void)
{
    if (surface)
        cairo_surface_destroy (surface);
}

void 
activate (GtkApplication* app,
          gpointer        user_data)
{
    GtkWidget *window;
    
    GtkWidget *frame;
    GtkWidget *drawing_area;

    GtkWidget *button_color;
    GtkWidget *button_save;
    GtkWidget *button_open;
    GtkWidget *button_brush;
    GtkWidget *button_erase;
    GtkWidget *button_thickness;
    GtkWidget *fixed;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Linux Paint");
    gtk_window_set_default_size(GTK_WINDOW (window),800,640);

    g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 8);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_widget_set_size_request(frame,800,600);

    drawing_area = gtk_drawing_area_new ();
    /* set a minimum size */
    gtk_widget_set_size_request (drawing_area, 800, 600);

    gtk_container_add (GTK_CONTAINER (frame), drawing_area);
    
    /* Signals used to handle the backing surface */
    g_signal_connect (drawing_area, "draw",
                        G_CALLBACK (draw_cb), NULL);
    g_signal_connect (drawing_area,"configure-event",
                        G_CALLBACK (configure_event_cb), NULL);

    /* Event signals */
    g_signal_connect (drawing_area, "motion-notify-event",
                        G_CALLBACK (motion_notify_event_cb), NULL);
    g_signal_connect (drawing_area, "button-press-event",
                        G_CALLBACK (button_press_event_cb), NULL);

    /* Ask to receive events the drawing area doesn't normally
    * subscribe to. In particular, we need to ask for the
    * button press and motion notify events that want to handle.
    */
    gtk_widget_set_events (drawing_area, gtk_widget_get_events (drawing_area)
                                        | GDK_BUTTON_PRESS_MASK
                                        | GDK_POINTER_MOTION_MASK);

    /* Button box */
    button_save = gtk_button_new_with_label ("Save");
    g_signal_connect (button_save, "clicked", G_CALLBACK (print_hello), NULL);

    button_open = gtk_button_new_with_label ("Open");
    g_signal_connect (button_open, "clicked", G_CALLBACK (print_hello), NULL);

    button_brush = gtk_button_new_with_label ("Brush");
    g_signal_connect (button_brush, "clicked", G_CALLBACK (print_hello), NULL);
    
    button_erase = gtk_button_new_with_label ("Erase");
    g_signal_connect (button_erase, "clicked", G_CALLBACK (print_hello), NULL);

    button_thickness = gtk_button_new_with_label ("Thickness");
    g_signal_connect (button_thickness, "clicked", G_CALLBACK (print_hello), NULL);
    
    button_color = gtk_button_new_with_label ("Color");
    g_signal_connect (button_color, "clicked", G_CALLBACK (print_hello), NULL);

    gtk_fixed_put(GTK_FIXED (fixed), button_save, 0, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_open, 50, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_brush, 100, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_erase, 150, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_thickness, 200, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_color, 250, 1);
    gtk_fixed_put(GTK_FIXED (fixed), frame, 0, 40);
    
    //gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_widget_show_all (window);
}