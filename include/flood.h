#ifndef _FLOOD_H_
#define _FLOOD_H_

// flood color : back ground color is changed //
static cairo_surface_t *flood_color_surface = NULL;

static GtkWidget *flood_color_window;
static GtkWidget *flood_color_frame;
static GtkWidget *flood_color_area;

GtkWidget *flood_entry_R;
GtkWidget *flood_entry_G;
GtkWidget *flood_entry_B;

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

void set_flood_color_area (void);

void set_flood_color(void);

void set_flood_entry_R(GtkWidget *widget, GtkWidget *entry);
void set_flood_entry_G(GtkWidget *widget, GtkWidget *entry);
void set_flood_entry_B(GtkWidget *widget, GtkWidget *entry);

void close_flood_color_window (void);

gboolean flood_configure_color_cb (GtkWidget		 *widget,
		  	                       GdkEventConfigure *event,
                          		   gpointer 		 data);
                          		   
gboolean flood_color_cb (GtkWidget *widget,
						 cairo_t   *cr,
						 gpointer  data);
						 
gboolean flood_draw_cb (GtkWidget *widget,
						cairo_t   *cr,
			            gpointer  data);
			            
void flood_fill (void);

static gboolean fill_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);

void flood_util (GtkWidget *widget, gpointer   data);


#endif
