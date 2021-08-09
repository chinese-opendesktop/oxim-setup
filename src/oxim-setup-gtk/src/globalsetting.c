#include "oxim_setup_gtk_global.h"
#include "globalsetting.h"

static globalsetting_dialog_data_t dialog_data;

GtkDialog* dialog_me;
static GtkLabel* InputMethodName_Label;
static GtkEntry* InputMethodAliasName_Entry;
static GtkCheckButton* IsComboUsed_CheckButton;
static GtkSpinButton* ComboNumber_SpinButton;


void globalsetting_dialog_is_combo_used_checkbutton_toggled(GtkSpinButton* spinbutton,GtkCheckButton* check);
static void internal_copy_data( globalsetting_dialog_data_t* from, globalsetting_dialog_data_t* to);
static void internal_copy_data( globalsetting_dialog_data_t* from, globalsetting_dialog_data_t* to)
{
	to->header.is_dialog_press_accept = from->header.is_dialog_press_accept;
//	to->header.xml = from->header.xml;
	to->header.builder = from->header.builder;
	g_strlcpy(to->input_method_name,from->input_method_name,100);
	g_strlcpy(to->input_method_alias_name,from->input_method_alias_name,100);
	to->is_combo_used = from->is_combo_used;
	to->combo_number = from->combo_number;
} //internal_copy_data()

void globalsetting_dialog_ctor(GtkWidget* me, gpointer data)
{
	
	printf("  [Func %s() is invoked]\n",__func__);
	internal_copy_data( (globalsetting_dialog_data_t*)data, &(dialog_data));
	dialog_me= GTK_DIALOG(me);
/*
	GladeXML *xml = dialog_data.header.xml;
	InputMethodName_Label = GTK_LABEL(glade_xml_get_widget(xml,"globalsetting_dialog_input_method_name_label"));
	InputMethodAliasName_Entry = GTK_ENTRY(glade_xml_get_widget(xml,"globalsetting_dialog_input_method_alias_name_entry"));
	IsComboUsed_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"globalsetting_dialog_is_combo_used_checkbutton"));
	ComboNumber_SpinButton = GTK_SPIN_BUTTON(glade_xml_get_widget(xml,"globalsetting_dialog_combo_number_spinbutton"));
*/
	GtkBuilder *builder = dialog_data.header.builder;
	InputMethodName_Label = GTK_LABEL( GTK_WIDGET( gtk_builder_get_object(builder, "globalsetting_dialog_input_method_name_label") ) );
	InputMethodAliasName_Entry = GTK_ENTRY( GTK_WIDGET( gtk_builder_get_object(builder, "globalsetting_dialog_input_method_alias_name_entry") ) );
	IsComboUsed_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "globalsetting_dialog_is_combo_used_checkbutton") ) );
	ComboNumber_SpinButton = GTK_SPIN_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "globalsetting_dialog_combo_number_spinbutton") ) );


	gtk_label_set_text(InputMethodName_Label,dialog_data.input_method_name);
	gtk_entry_set_text(InputMethodAliasName_Entry,dialog_data.input_method_alias_name);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsComboUsed_CheckButton), dialog_data.is_combo_used);
	gtk_spin_button_set_value(ComboNumber_SpinButton,(gdouble)dialog_data.combo_number);
	gtk_widget_set_sensitive(GTK_WIDGET(ComboNumber_SpinButton), dialog_data.is_combo_used);
	dialog_data.header.is_dialog_press_accept = FALSE;
} //globalsetting_dialog_ctor()

//void globalsetting_dialog_is_combo_used_checkbutton_toggled(GtkCheckButton* check, GtkSpinButton* spinbutton)
void globalsetting_dialog_is_combo_used_checkbutton_toggled(GtkSpinButton* spinbutton,GtkCheckButton* check)
{
	printf("[Func %s() is invoked] >>\n",__func__);
	gtk_widget_set_sensitive(GTK_WIDGET(spinbutton), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)));
}
void globalsetting_dialog_dtor(GtkObject* me, gpointer data)
{
	printf("[Func %s() is invoked] >>\n",__func__);
	g_strlcpy(dialog_data.input_method_alias_name,gtk_entry_get_text(InputMethodAliasName_Entry),-1);
	dialog_data.is_combo_used = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(IsComboUsed_CheckButton));
	dialog_data.combo_number = (gint)gtk_spin_button_get_value(ComboNumber_SpinButton);

	if(dialog_data.header.is_dialog_press_accept == TRUE)
		internal_copy_data( &(dialog_data),(globalsetting_dialog_data_t*)data );
} //globalsetting_dialog_dtor()
void globalsetting_dialog_accept(GtkButton* accept_button)
{
	printf("[Func %s() is invoked]\n",__func__);
	dialog_data.header.is_dialog_press_accept = TRUE;
//	gtk_widget_hide_all(GTK_WIDGET(dialog_me));
} //globalsetting_dialog_accept()
void globalsetting_dialog_reject(GtkButton* reject_button)
{
	printf("[Func %s() is invoked]\n",__func__);
//	gtk_widget_hide_all(GTK_WIDGET(dialog_me));
} //globalsetting_dialog_reject()


