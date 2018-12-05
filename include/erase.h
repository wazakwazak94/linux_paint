#ifndef _ERASE_H_
#define _ERASE_H_

void 
set_erase_thickness (GtkWidget *widget,
                     GtkWidget *entry);

void
set_erase_scroll (GtkScale *scale,
                  gdouble   value,
                  gpointer  user_data);

void
close_erase_window (void);

void
save_close_erase_window (void);

void
erase_util (GtkWidget *widget,
            gpointer   data);

#endif