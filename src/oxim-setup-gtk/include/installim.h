#ifndef INSTALLIM_H
#define INSTALLIM_H
//include this header file after oxim_setup_gtk_global.h
//since the struct dialog_data_header_t is defined at oxim_setup_gtk_global.h
typedef struct
{
	dialog_data_header_t header;
	gchar filename[1024];
} installim_dialog_data_t;

void installim_dialog_ctor(GtkWidget* me, gpointer data);
void installim_dialog_dtor(GtkObject* me, gpointer data);
void installim_dialog_accept(GtkButton* accept_button);
void installim_dialog_reject(GtkButton* reject_button);

#endif //INSTALLIM_H
