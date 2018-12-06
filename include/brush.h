#ifndef _BRUSH_H_
#define _BRUSH_H_

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
