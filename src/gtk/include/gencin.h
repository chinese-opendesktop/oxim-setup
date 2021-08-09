#ifndef GENCIN_H
#define GENCIN_H
//include this header file after oxim_setup_gtk_global.h
//since the struct dialog_data_header_t is defined at oxim_setup_gtk_global.h





typedef struct _gencin_dialog_data_t gencin_dialog_data_t;
struct _gencin_dialog_data_t
{
	dialog_data_header_t header;
	gchar input_method_name[100]; //written in AliasName
	gboolean is_on_auto_show_result_when_typeing; 
	gboolean is_start_up_general_used_character;
	gboolean is_to_press_space_to_clear_when_error;

	gboolean is_auto_show_word_mode;
	gboolean is_output_word_when_type_space;
	gboolean is_shift_position_when_select;

	gboolean is_auto_output_word_when_letter_full;
	gboolean is_continued_space_influent;
	
	gboolean is_to_output_word_when_press_end;
	gchar special_letter[100];
	gencin_dialog_data_t* default_value;

}; //struct _gencin_dialog_data_t

void gencin_dialog_accept(GtkButton* accept_button, gpointer data);
void gencin_dialog_reject(GtkButton* reject_button);
void gencin_dialog_default(GtkButton* default_button);
void gencin_dialog_ctor(GtkWidget* me, gpointer data);
void gencin_dialog_dtor(GtkObject* me, gpointer data);


#endif //GENCIN_H
