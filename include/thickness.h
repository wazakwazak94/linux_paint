#ifndef _THICKNESS_H_
#define _THICKNESS_H_

void 
set_thickness (GtkWidget *widget,
               GtkWidget *entry);

void
set_th_scroll (GtkScale *scale,
               gdouble   value,
               gpointer  user_data);

void
close_th_window (void);

void
save_close_th_window (void);

void
thickness_util (GtkWidget *widget,
                gpointer   data);

#endif