#include "global.h"

static void do_drawing(cairo_t *cr)
{      
    cairo_set_source_surface(cr, surface, 0, 0);
	
	cairo_paint(cr);
}
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    do_drawing(cr);
	
	return FALSE;
}

static gboolean openPNG(gpointer arg) 
{
	char *filename = (char *)arg;
	
	surface = cairo_image_surface_create_from_png("Test.png");
		
	g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw_event), NULL);
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
	}
		
	gtk_widget_destroy(dialog);
}

