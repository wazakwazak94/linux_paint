#ifndef _FLOODflood_H_
#define _FLOODflood_H_

#include "global_v.h"

static cairo_surface_t *flood_color_surface = NULL;

static GtkWidget *flood_color_window;
static GtkWidget *flood_color_frame;
static GtkWidget *flood_color_area;

GtkWidget *flood_entry_R;
GtkWidget *flood_entry_G;
GtkWidget *flood_entry_B;

//Color Setting
struct flood_color{
    double R;
    double G;
    double B;
};

struct char_flood_color{
    char R[4];
    char G[4];
    char B[4];
};

struct flood_color floodColor;
struct flood_color flood_showColor;
struct char_flood_color flood_charColor;


void
set_flood_color_area (void)
{
    cairo_t *cr;

    cr = cairo_create(flood_color_surface);

    cairo_set_source_rgb(cr, flood_showColor.R, flood_showColor.G, flood_showColor.B);
    cairo_paint(cr);

    cairo_destroy (cr);
}

void
set_flood_color(void)
{
    floodColor.R = flood_showColor.R;
    floodColor.G = flood_showColor.G;
    floodColor.B = flood_showColor.B;
}

void
set_flood_entry_R(GtkWidget *widget,
            GtkWidget *entry)
{
    const gchar *entry_text;
    double red;

    entry_text = gtk_entry_get_text (GTK_ENTRY(entry));
    red = (double)(atoi(entry_text))/255;
    
    if(red < 0.0 || red > 1.0)
    {
        g_print ("enter the number between 0 ~ 255\n");
    }
    else
    {
        flood_showColor.R = red;
        set_flood_color();
        set_flood_color_area();
        gtk_widget_queue_draw (flood_color_area);
    }
}

void
set_flood_entry_G(GtkWidget *widget,
            GtkWidget *entry)
{
    const gchar *entry_text;
    double green;

    entry_text = gtk_entry_get_text (GTK_ENTRY(entry));
    green = (double)(atoi(entry_text))/255;
    
    if(green < 0.0 || green > 1.0)
    {
        g_print ("enter the number between 0 ~ 255\n");
    }
    else
    {
        flood_showColor.G = green;
        set_flood_color();
        set_flood_color_area();
        gtk_widget_queue_draw (flood_color_area);
    }
}

void
set_flood_entry_B(GtkWidget *widget,
            GtkWidget *entry)
{
    const gchar *entry_text;
    double blue;

    entry_text = gtk_entry_get_text (GTK_ENTRY(entry));
    blue = (double)(atoi(entry_text))/255;
    
    if(blue < 0.0 || blue > 1.0)
    {
        g_print ("enter the number between 0 ~ 255\n");
    }
    else
    {
        flood_showColor.B = blue;
        set_flood_color(); 
        set_flood_color_area();
        gtk_widget_queue_draw (flood_color_area);
    }
}

void
close_flood_color_window (void)
{
    if(flood_color_window)
        gtk_widget_destroy (flood_color_window);
}
gboolean
flood_configure_color_cb (GtkWidget	*widget,
	                      GdkEventConfigure *event,
                          gpointer data)
{
    if (flood_color_surface)
        cairo_surface_destroy (flood_color_surface);

    flood_color_surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                                       CAIRO_CONTENT_COLOR,
                                                       gtk_widget_get_allocated_width (widget),
                                                       gtk_widget_get_allocated_height (widget));

    set_color_area ();
    return TRUE;
}

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
gboolean
flood_color_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
    cairo_set_source_surface (cr, flood_color_surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}

gboolean
flood_draw_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
    cairo_set_source_surface (cr, surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}

void
flood_fill ()
{
	if(flood_color_window){
        set_flood_entry_R(flood_entry_R,flood_entry_R);
        set_flood_entry_G(flood_entry_G,flood_entry_G);
        set_flood_entry_B(flood_entry_B,flood_entry_B);
        set_flood_color();
        gtk_widget_destroy (flood_color_window);
    }
	
	cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, floodColor.R, floodColor.G, floodColor.B);
    
    cairo_paint (cr);
    cairo_destroy(cr);

}

static gboolean fill_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	flood_fill();
	return FALSE;
}
void
flood_util (GtkWidget *widget,
             gpointer   data)
{
  GtkWidget *flood_fixed;
  GtkWidget *flood_button_ok;
  GtkWidget *flood_button_cancel;
  
  flood_showColor.R = floodColor.R;
  flood_showColor.G = floodColor.G;
  flood_showColor.B = floodColor.B;

  sprintf(flood_charColor.R,"%d",(int)(floodColor.R*255));
  sprintf(flood_charColor.G,"%d",(int)(floodColor.G*255));
  sprintf(flood_charColor.B,"%d",(int)(floodColor.B*255));

  flood_color_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(flood_color_window), "Flood Color");
  gtk_window_set_default_size(GTK_WINDOW(flood_color_window), 350, 250);

  gtk_container_set_border_width (GTK_CONTAINER(flood_color_window),8);

  flood_fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(flood_color_window),flood_fixed);

  //show the current color 
  flood_color_frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (flood_color_frame), GTK_SHADOW_IN);
  gtk_widget_set_size_request(flood_color_frame,150,150);

  flood_color_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(flood_color_area,150,150);
  gtk_container_add (GTK_CONTAINER(flood_color_frame),flood_color_area);


  g_signal_connect (drawing_area, "draw",
                        G_CALLBACK (flood_draw_cb), NULL);
  g_signal_connect (flood_color_area, "draw",
                        G_CALLBACK (flood_color_cb), NULL);
  g_signal_connect (flood_color_area, "configure-event",
                    G_CALLBACK(flood_configure_color_cb), NULL);
                    
                    

  //button setting
  flood_button_cancel = gtk_button_new_with_label("Cancel");
  g_signal_connect (flood_button_cancel, "clicked", 
  G_CALLBACK(close_flood_color_window),NULL);
  
  flood_button_ok = gtk_button_new_with_label ("Ok");
  g_signal_connect (flood_button_ok, "clicked", G_CALLBACK(fill_event),NULL);

  //entry setting
  flood_entry_R = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(flood_entry_R), (const gchar *)flood_charColor.R);
  g_signal_connect (flood_entry_R, "activate", G_CALLBACK(set_flood_entry_R), flood_entry_R);
  flood_entry_G = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(flood_entry_G), (const gchar *)flood_charColor.G);
  g_signal_connect (flood_entry_G, "activate", G_CALLBACK(set_flood_entry_G), flood_entry_G);
  flood_entry_B = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(flood_entry_B), (const gchar *)flood_charColor.B);    
  g_signal_connect (flood_entry_B, "activate", G_CALLBACK(set_flood_entry_B), flood_entry_B);


  gtk_fixed_put(GTK_FIXED (flood_fixed), flood_color_frame, 20, 20);
  gtk_fixed_put(GTK_FIXED (flood_fixed), flood_button_cancel, 250,200);
  gtk_fixed_put(GTK_FIXED (flood_fixed), flood_button_ok, 215,200);
  gtk_fixed_put(GTK_FIXED (flood_fixed), flood_entry_R, 180,30);
  gtk_fixed_put(GTK_FIXED (flood_fixed), flood_entry_G, 180,80);
  gtk_fixed_put(GTK_FIXED (flood_fixed), flood_entry_B, 180,130);

  gtk_widget_show_all(flood_color_window);
}

#endif
