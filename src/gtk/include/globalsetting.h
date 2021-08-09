#ifndef GLOBALSETTING_H
#define GLOBALSETTING_H
//include this header file after oxim_setup_gtk_global.h
//since the struct dialog_data_header_t is defined at oxim_setup_gtk_global.h
typedef struct
{
	dialog_data_header_t header;
	gchar input_method_name[100];
	gchar input_method_alias_name[100];
	gboolean is_combo_used;
	gint combo_number; //[0-9]
} globalsetting_dialog_data_t;
void globalsetting_dialog_ctor(GtkWidget* me, gpointer data);
void globalsetting_dialog_dtor(GtkObject* me, gpointer data);
void globalsetting_dialog_accept(GtkButton* accept_button);
void globalsetting_dialog_reject(GtkButton* reject_button);


#endif //GLOBALSETTING_H
