#ifndef _FLOODFILL_H_
#define _FLOODFILL_H_

#include <unix-print/gtk/gtkunixprint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern cairo_surface_t *surface;
static cairo_surface_t *color_surface = NULL;

static GtkWidget *color_window;
static GtkWidget *color_frame;
static GtkWidget *color_area;

GtkWidget *entry_R;
GtkWidget *entry_G;
GtkWidget *entry_B;

//Color Setting
struct Fill_color{
    double R;
    double G;
    double B;
};

struct char_Fill_color{
    char R[4];
    char G[4];
    char B[4];
};

struct Fill_color FillColor;
struct Fill_color showColor;
struct char_Fill_color charColor;

void
set_color_area (void)
{
    cairo_t *cr;

    cr = cairo_create (color_surface);

    cairo_set_source_rgb(cr, showColor.R, showColor.G, showColor.B);
    cairo_paint(cr);

    cairo_destroy (cr);
}

void
set_Fill_color(void)
{
    FillColor.R = showColor.R;
    FillColor.G = showColor.G;
    FillColor.B = showColor.B;
}

void
set_entry_R(GtkWidget *widget,
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
        showColor.R = red;
        set_Fill_color();
        set_color_area();
        gtk_widget_queue_draw (color_area);
    }
}

void
set_entry_G(GtkWidget *widget,
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
        showColor.G = green;
        set_Fill_color();
        set_color_area();
        gtk_widget_queue_draw (color_area);
    }
}

void
set_entry_B(GtkWidget *widget,
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
        showColor.B = blue;
        set_Fill_color();
        set_color_area();
        gtk_widget_queue_draw (color_area);
    }
}

void
close_color_window (void)
{
    if(color_window)
        gtk_widget_destroy (color_window);
}

void
save_close_color_window (void)
{
    if(color_window){
        set_entry_R(entry_R,entry_R);
        set_entry_G(entry_G,entry_G);
        set_entry_B(entry_B,entry_B);
        set_Fill_color();
        gtk_widget_destroy (color_window);
    }
}

gboolean
configure_color_cb (GtkWidget         *widget,
                    GdkEventConfigure *event,
                    gpointer           data)
{
    if (color_surface)
        cairo_surface_destroy (color_surface);

    color_surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
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
color_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
    cairo_set_source_surface (cr, color_surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}

gboolean
draw_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data)
{
    cairo_set_source_surface (cr, surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}
/*
void floodfill(GtkWidget *widget,
               gdouble    x,
               gdouble    y,
               unsigned char fillcolor[],unsigned char oldcolor[])
 {  //IF FILL COLOR IS SAME AS OLD COLOR< DON"T DO ANYTHING
	if(oldcolor[0]==fillcolor[0] && oldcolor[1]==fillcolor[1] && oldcolor[2]==fillcolor[2])
	 	return;
    unsigned char color[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,color);
    //IF OBTANED PIXEL DOES NOT BELONG TO INTERIOR OF POLYGON
    if(oldcolor[0]!=color[0] && oldcolor[1]!=color[1] && oldcolor[2]!=color[2])
	 {return;}
	glColor3ubv(fillcolor);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	printf("x=%d,y=%d\n",x,y);
	glEnd();
	glFlush();
    floodfill(x+1,y,fillcolor,oldcolor);
    floodfill(x,y+1,fillcolor,oldcolor);
    floodfill(x-1,y,fillcolor,oldcolor);
    floodfill(x,y-1,fillcolor,oldcolor);
}
*/
void
flood_util (GtkWidget *widget,
             gpointer   data)
{
  GtkWidget *fixed;
  GtkWidget *button_ok;
  GtkWidget *button_cancel;

  showColor.R = FillColor.R;
  showColor.G = FillColor.G;
  showColor.B = FillColor.B;

  sprintf(charColor.R,"%d",(int)(FillColor.R*255));
  sprintf(charColor.G,"%d",(int)(FillColor.G*255));
  sprintf(charColor.B,"%d",(int)(FillColor.B*255));

  color_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(color_window), "Color");
  gtk_window_set_default_size(GTK_WINDOW(color_window), 350, 250);

  gtk_container_set_border_width (GTK_CONTAINER(color_window),8);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(color_window),fixed);

  //show the current color 
  color_frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (color_frame), GTK_SHADOW_IN);
  gtk_widget_set_size_request(color_frame,150,150);

  color_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(color_area,150,150);
  gtk_container_add (GTK_CONTAINER(color_frame),color_area);

  g_signal_connect (color_area, "draw",
                        G_CALLBACK (color_cb), NULL);
  g_signal_connect (color_area, "configure-event",
                    G_CALLBACK(configure_color_cb), NULL);

  //button setting
  button_cancel = gtk_button_new_with_label("Cancel");
  g_signal_connect (button_cancel, "clicked", G_CALLBACK(close_color_window),NULL);
  
  button_ok = gtk_button_new_with_label ("Ok");
  g_signal_connect (button_ok, "clicked", G_CALLBACK(save_close_color_window),NULL);

  //entry setting
  entry_R = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_R), (const gchar *)charColor.R);
  g_signal_connect (entry_R, "activate", G_CALLBACK(set_entry_R), entry_R);
  entry_G = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_G), (const gchar *)charColor.G);
  g_signal_connect (entry_G, "activate", G_CALLBACK(set_entry_G), entry_G);
  entry_B = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(entry_B), (const gchar *)charColor.B);    
  g_signal_connect (entry_B, "activate", G_CALLBACK(set_entry_B), entry_B);


  gtk_fixed_put(GTK_FIXED (fixed), color_frame, 20, 20);
  gtk_fixed_put(GTK_FIXED (fixed), button_cancel, 250,200);
  gtk_fixed_put(GTK_FIXED (fixed), button_ok, 215,200);
  gtk_fixed_put(GTK_FIXED (fixed), entry_R, 180,30);
  gtk_fixed_put(GTK_FIXED (fixed), entry_G, 180,80);
  gtk_fixed_put(GTK_FIXED (fixed), entry_B, 180,130);

  gtk_widget_show_all(color_window);
}

#endif
