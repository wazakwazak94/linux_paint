#include "global_v.h"

cairo_surface_t *image;

static void do_drawing(cairo_t *cr)
{
    cairo_set_source_surface(cr, image, 0, 0);
	cairo_paint(cr);
	
}
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	do_drawing(cr);
	
	return FALSE;
}
static gboolean openPNG(gpointer arg) 
{
	char *filename = 
	filename = (char *)arg;
	
	int w, h;
    image = cairo_image_surface_create_from_png("filename");
    cairo_t *cr = cairo_create(surface);
	w = cairo_image_surface_get_width(image);
	h = cairo_image_surface_get_height(image);	
	
//	cairo_translate(cr, -10, -50);
//	cairo_scale(cr, 256.0/w, 256.0/h);
	g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw_event), NULL);

	//printf("%s\n", filename);	

	//g_free(filename);
    //cairo_surface_destroy(image);
}

static void open_dialog(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	
	dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), action,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_OK, NULL);
	
	chooser = GTK_FILE_CHOOSER(dialog);
	
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	
	gtk_widget_show_all(dialog);
	
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	
	gtk_file_chooser_set_current_folder(chooser, g_get_home_dir());
	if(res==GTK_RESPONSE_OK)
	{
		char *filename;
		
		filename = gtk_file_chooser_get_filename(chooser);
		g_timeout_add(10, openPNG, filename);
		printf("%s\n", filename);
		g_free(filename);
	}
	else
		g_print("You pressed the cancle\n");
	gtk_widget_destroy(dialog);
}

