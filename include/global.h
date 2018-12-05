#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

cairo_surface_t *surface;

GtkWidget *color_window;
GtkWidget *color_frame;
GtkWidget *color_area;

GtkWidget *entry_R;
GtkWidget *entry_G;
GtkWidget *entry_B;

GtkWidget *window_th;
GtkWidget *entry_th;
GtkWidget *scale_th;

gint thickness_;
gint temp_th;
char char_th[4];

GtkWidget *window_erase;
GtkWidget *entry_erase;
GtkWidget *scale_erase;