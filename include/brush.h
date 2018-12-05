#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "global.h"

static cairo_surface_t *color_surface = NULL;

static GtkWidget *color_window;
static GtkWidget *color_frame;
static GtkWidget *color_area;

GtkWidget *entry_R;
GtkWidget *entry_G;
GtkWidget *entry_B;

//color of Brush
struct brush_color{
    double R;
    double G;
    double B;
};

struct char_brush_color{
    char R[4];
    char G[4];
    char B[4];
};

struct brush_color brushColor;
struct brush_color showColor;
struct char_brush_color charColor;

void
set_color_area (void);

void
set_brush_color(void);

void
set_entry_R(GtkWidget *widget,
            GtkWidget *entry);

void
set_entry_G(GtkWidget *widget,
            GtkWidget *entry);

void
set_entry_B(GtkWidget *widget,
            GtkWidget *entry);

void
close_color_window (void);

void
save_close_color_window (void);

gboolean
configure_color_cb (GtkWidget         *widget,
                    GdkEventConfigure *event,
                    gpointer           data);

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
gboolean
color_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data);

gboolean
draw_cb (GtkWidget *widget,
         cairo_t   *cr,
         gpointer   data);

// Draw a rectangle on the surface at the given position 
void
draw_brush (GtkWidget *widget,
            gdouble    x,
            gdouble    y);

void
color_util (GtkWidget *widget,
             gpointer   data);

#endif