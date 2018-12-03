#include "util.h"
#include "brush.h"

void
clear_surface (void)
{
    cairo_t *cr;

    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_destroy (cr);
}

/* Create a new surface of the appropriate size to store our scribbles */
gboolean
configure_event_cb (GtkWidget         *widget,
                    GdkEventConfigure *event,
                    gpointer           data)
{
    if (surface)
        cairo_surface_destroy (surface);

    surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                                CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width (widget),
                                                gtk_widget_get_allocated_height (widget));

    /* Initialize the surface to white */
    clear_surface ();

    /* We've handled the configure event, no need for further processing. */
    return TRUE;
}

gboolean
button_press_event_cb (GtkWidget      *widget,
                       GdkEventButton *event,
                       gpointer        data)
{
    /* paranoia check, in case we haven't gotten a configure event */
    if (surface == NULL)
        return FALSE;

    if (event->button == GDK_BUTTON_PRIMARY)
        {
        draw_brush (widget, event->x, event->y);
        }
    /*else if (event->button == GDK_BUTTON_SECONDARY)
        {
        clear_surface ();
        gtk_widget_queue_draw (widget);
        }*/

    /* We've handled the event, stop processing */
    return TRUE;
}

gboolean
motion_notify_event_cb (GtkWidget      *widget,
                        GdkEventMotion *event,
                        gpointer        data)
{
    /* paranoia check, in case we haven't gotten a configure event */
    if (surface == NULL)
        return FALSE;

    if (event->state & GDK_BUTTON1_MASK)
        draw_brush (widget, event->x, event->y);

    /* We've handled it, stop processing */
    return TRUE;
}

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
    g_signal_connect (button_color, "clicked", G_CALLBACK (color_util), NULL);
    
    button_flood = gtk_button_new_with_label ("Flood Fill");
    g_signal_connect (button_color, "clicked", G_CALLBACK (flood_util), NULL);

    gtk_fixed_put(GTK_FIXED (fixed), button_save, 0, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_open, 50, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_brush, 105, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_erase, 165, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_thickness, 220, 0);
    gtk_fixed_put(GTK_FIXED (fixed), button_color, 305, 0);
	gtk_fixed_put(GTK_FIXED (fixed), button_color, 355, 0);
    gtk_fixed_put(GTK_FIXED (fixed), frame, 0, 40);
    
    //gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_widget_show_all (window);
}   
