#include "global.h"

static gboolean savePNG(gpointer arg) 
{
	char *filename; 
	filename = (char *)arg;

    cairo_surface_t *surface = cairo_image_surface_create(
        CAIRO_FORMAT_RGB24, 800, 600
    );
    cairo_t *cr = cairo_create(surface);
	
	cairo_translate(cr, -10, -50);
    gdk_cairo_set_source_window(
        cr,
        gtk_widget_get_window(GTK_WIDGET(window)),
        0, 0
    );

	cairo_paint(cr);

    cairo_surface_write_to_png(surface, "Test.png");
}

static void save_dialog(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;
	
	dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), action,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_OK, NULL);
	
	chooser = GTK_FILE_CHOOSER(dialog);
	
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	
	gtk_widget_show_all(dialog);
	
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	
	gtk_file_chooser_set_current_folder(chooser, g_get_home_dir());
	if(res==GTK_RESPONSE_OK)
	{
		char *filename;
		
		filename = gtk_file_chooser_get_filename(chooser);
		g_timeout_add(10, savePNG, filename);
		g_free(filename);
	}
	
	gtk_widget_destroy(dialog);
}

