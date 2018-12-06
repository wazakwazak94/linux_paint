#ifndef _OPEN_H_
#define _OPEN_H_

static void do_drawing(cairo_t *cr);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);

static gboolean openPNG(gpointer arg);

void open_dialog(GtkWidget *button, gpointer window);

#endif
