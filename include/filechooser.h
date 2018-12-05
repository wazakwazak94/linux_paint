# include <gtk/gtk.h>
# include <string.h>

void save_to_file (char *_src_filename, char *_dst_filename)
{
	int length;
	unsigned char *inData;
	char Buffer[9];
	int c = 0;
	int x;
	
	FILE *reader = fopen(_src_filename, "r");
	FILE *writer = fopen(_dst_filename, "wb");
	
	fseek(reader, 0, SEEK_END);
	length = ftell(reader);	
	fseek(reader, 0, SEEK_SET);
	
	for (x=0; x < length; x++)
	{
		fscanf(reader, "%d", &inData);
		if(c <= 8)
			Buffer[c] = inData;
		else
		{
			fwrite(&Buffer, sizeof(Buffer), 1, writer);
			c = 0;
		}
		c++;
	}
	
	fclose(reader);
	fclose(writer);
	
}

static gboolean savePNG(gpointer arg) 
{
	char *filename = arg;
    cairo_surface_t *surface = cairo_image_surface_create(
        CAIRO_FORMAT_RGB24, 800, 600
    );
    cairo_t *cr = cairo_create(surface);

    gdk_cairo_set_source_window(
        cr,
        gtk_widget_get_window(GTK_WIDGET(window)),
        0, 0
    );

    printf("cairo_status(cr): %s\ncairo_surface_status(surface): %s\n",
        cairo_status_to_string(cairo_status(cr)),
        cairo_status_to_string(cairo_surface_status(surface)));

    cairo_surface_write_to_png(surface, arg);
}

static void open_dialog(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;
	char *existing_filename;
	char *user_edited_a_new_document;
	
	dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), action,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, _("_Save"), GTK_RESPONSE_OK, NULL);
	
	chooser = GTK_FILE_CHOOSER(dialog);
	
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	
	gtk_widget_show_all(dialog);
	
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	
	gtk_file_chooser_set_current_folder(chooser, g_get_home_dir());
	gtk_file_chooser_set_current_name(chooser, _("Untiled Document"));
	if(res==GTK_RESPONSE_OK)
	{
		char *filename;
		
		filename = gtk_file_chooser_get_filename(chooser);
		g_timeout_add(1000, savePNG, filename);
		g_free(filename);
	}
	else
		g_print("You pressed the cancle\n");
	gtk_widget_destroy(dialog);
}

