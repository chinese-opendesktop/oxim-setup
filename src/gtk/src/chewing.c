
#include "oxim_setup_gtk_global.h"
#include "chewing.h"


static chewing_dialog_data_t dialog_data;

GtkWidget* dialog_me;
static GtkRadioButton* Keymap_RadioButton[CMK_SIZE];
static GtkRadioButton* Select_RadioButton[CSM_SIZE];
static GtkRadioButton* Capslock_RadioButton[CCM_SIZE];



static void internal_copy_data( chewing_dialog_data_t* from, chewing_dialog_data_t* to);

static void internal_copy_data( chewing_dialog_data_t* from, chewing_dialog_data_t* to)
{
	to->header.is_dialog_press_accept = from->header.is_dialog_press_accept;
//	to->header.xml = from->header.xml;
	to->header.builder = from->header.builder;
	to->keymap = from->keymap;
	to->select = from->select;
	to->capslock = from->capslock;
}

void chewing_dialog_ctor(GtkWidget* me, gpointer data)
{
	
	printf("[Func %s() is invoked]\n",__func__);
		             //0123456789 123456789
	gchar keymap_str[]  = "keymap_radiobutton1";
	gchar select_str[]  = "select_radiobutton1";
	gchar capslock_str[]= "capslock_radiobutton1";
	int idx;
	internal_copy_data((chewing_dialog_data_t*)data, &dialog_data);
	dialog_me = me;  
//	GladeXML *xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;


	for(idx=0; idx<CMK_SIZE;idx++)
	{
		keymap_str[ (sizeof(keymap_str)/sizeof(gchar)) - 2]=(gchar)( '1'+idx);
//		Keymap_RadioButton[idx]=GTK_RADIO_BUTTON(glade_xml_get_widget(xml,keymap_str));
		Keymap_RadioButton[idx]=GTK_RADIO_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, keymap_str) ) );
	}

	for(idx=0; idx<CSM_SIZE; idx++)
	{
		select_str[(sizeof(select_str)/sizeof(gchar)) - 2]=(gchar)('1'+idx);
//		Select_RadioButton[idx]=GTK_RADIO_BUTTON(glade_xml_get_widget(xml, select_str));
		Select_RadioButton[idx]=GTK_RADIO_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, select_str) ) );
	}

	for(idx=0; idx<CCM_SIZE ;idx++)
	{
		capslock_str[(sizeof(capslock_str)/sizeof(gchar)) - 2]=(gchar)('1'+idx);
//		Capslock_RadioButton[idx]=GTK_RADIO_BUTTON(glade_xml_get_widget(xml, capslock_str));
		Capslock_RadioButton[idx]=GTK_RADIO_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, capslock_str) ) );
	}

	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(Keymap_RadioButton[dialog_data.keymap]),TRUE);
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(Select_RadioButton[dialog_data.select]),TRUE);
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(Capslock_RadioButton[dialog_data.capslock]),TRUE);

	dialog_data.header.is_dialog_press_accept = FALSE;
}



void chewing_dialog_dtor(GtkObject* me, gpointer data)
{

	printf("[Func %s() is invoked]\n",__func__);
	
	if(dialog_data.header.is_dialog_press_accept == TRUE)
		internal_copy_data( &(dialog_data),(chewing_dialog_data_t*)data);
	
    
}

void chewing_dialog_accept(GtkButton* accept_button)
{
	
	printf("[Func %s() is invoked]\n",__func__);
	dialog_data.header.is_dialog_press_accept = TRUE;

	//gtk_widget_hide_all(GTK_WIDGET(dialog_me));
} //chewing_dialog_accept()

void chewing_dialog_reject(GtkButton* reject_button)
{
	printf("[Func %s() is invoked]\n",__func__);
//	gtk_widget_hide_all(GTK_WIDGET(dialog_me));
} //chewing_dialog_reject()


void keymap_radiobutton_toggled(GtkRadioButton* me)
{
	printf("[Func %s() is invoked]\n",__func__);
	gint idx=0;
	for(idx=0; idx<CMK_SIZE; idx++)	
		if(me == Keymap_RadioButton[idx] && gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(me))==TRUE)
			dialog_data.keymap = (chewing_keyboard_map_t)idx;	
} //keymap_radiobutton_toggled()

void select_radiobutton_toggled(GtkRadioButton* me)
{	
	printf("[Func %s() is invoked]\n",__func__);
	gint idx=0;
	for(idx=0; idx<CSM_SIZE; idx++)	
		if(me == Select_RadioButton[idx] && gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(me))==TRUE)
			dialog_data.select = (chewing_select_t)idx;	

} //select_radiobutton_toggled()

void capslock_radiobutton_toggled(GtkRadioButton* me)
{	
	printf("[Func %s() is invoked]\n",__func__);
	gint idx=0;
	for(idx=0; idx<CCM_SIZE; idx++)	
		if(me == Capslock_RadioButton[idx] && gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(me))==TRUE)
			dialog_data.capslock = (chewing_capslock_t)idx;	

} //capslock_radiobutton_toggled()


