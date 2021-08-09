#include "oxim_setup_gtk_global.h"
#include "gencin.h"
#include "im_default_value.h"
#include "g_oxim_conf.h"
static gencin_dialog_data_t dialog_data;


GtkDialog* dialog_me;   
static GtkLabel* InputMethodName_Label;
static GtkCheckButton* IsOnAutoShowResultWhenTypeing_CheckButton;
static GtkCheckButton* IsStartUpGeneralUsedCharacter_CheckButton;
static GtkCheckButton* IsToPressSpaceToClearWhenError_CheckButton;

static GtkCheckButton* IsAutoShowWordMode_CheckButton;
static GtkCheckButton* IsOutputWordWhenTypeSpace_CheckButton;
static GtkCheckButton* IsShiftPositionWhenSelect_CheckButton;

static GtkCheckButton* IsAutoOutputWordWhenLetterFull_CheckButton;
static GtkRadioButton* ContinuedSpaceInfluent_RadioButton;
static GtkRadioButton* NotContinuedSpaceInfluent_RadioButton;

static GtkCheckButton* IsToOutputWordWhenPressEnd;
static GtkEntry* SpecialLetter_Entry;


void internal_toggle_event_manager(GtkToggleButton* btn);
static void dialog_data_assign_to_gui(gencin_dialog_data_t* d);


static void internal_sensitive_filter(void);
static void internal_copy_data(gencin_dialog_data_t* from, gencin_dialog_data_t* to);
static void internal_copy_data(gencin_dialog_data_t* from, gencin_dialog_data_t* to)
{
	to->header.is_dialog_press_accept = from->header.is_dialog_press_accept;
//	to->header.xml = from->header.xml;
	to->header.builder = from->header.builder;
	to->default_value = from->default_value;
	g_strlcpy(to->input_method_name,from->input_method_name,100);
	to->is_on_auto_show_result_when_typeing = from->is_on_auto_show_result_when_typeing;
	to->is_start_up_general_used_character = from->is_start_up_general_used_character;
	to->is_to_press_space_to_clear_when_error = from->is_to_press_space_to_clear_when_error;
	to->is_auto_show_word_mode = from->is_auto_show_word_mode;
	to->is_output_word_when_type_space = from->is_output_word_when_type_space;
	to->is_shift_position_when_select = from->is_shift_position_when_select;
	to->is_auto_output_word_when_letter_full = from->is_auto_output_word_when_letter_full;
	to->is_continued_space_influent = from->is_continued_space_influent;
	to->is_to_output_word_when_press_end = from->is_to_output_word_when_press_end;
g_debug("[[[[[[[[[%d]]]]]]]]]]]]", to->header.is_dialog_press_accept);
puts("gfdgsgsgdsbgbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
} //internal_copy_data()

static void internal_sensitive_filter(void)
{
      

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(IsAutoShowWordMode_CheckButton))==TRUE)
	{
		gtk_widget_set_sensitive(GTK_WIDGET(IsOutputWordWhenTypeSpace_CheckButton), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(IsShiftPositionWhenSelect_CheckButton), TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(GTK_WIDGET(IsOutputWordWhenTypeSpace_CheckButton), FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(IsShiftPositionWhenSelect_CheckButton), FALSE);
	}
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(IsAutoOutputWordWhenLetterFull_CheckButton))==TRUE)
	{
		gtk_widget_set_sensitive(GTK_WIDGET(ContinuedSpaceInfluent_RadioButton), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(NotContinuedSpaceInfluent_RadioButton), TRUE);
	}
	else
	{	
		gtk_widget_set_sensitive(GTK_WIDGET(ContinuedSpaceInfluent_RadioButton), FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(NotContinuedSpaceInfluent_RadioButton), FALSE);
	}
} //internal_sensitive_filter()

void gencin_dialog_ctor(GtkWidget* me, gpointer data)
{
	printf("[Func %s() is invoked]\n",__func__);
	


	internal_copy_data((gencin_dialog_data_t*)data, &(dialog_data)); 

    
	dialog_me= GTK_DIALOG(me);    
/*	GladeXML *xml = dialog_data.header.xml;
	InputMethodName_Label = GTK_LABEL(glade_xml_get_widget(xml,"gencin_dialog_input_method_name_label"));
	IsOnAutoShowResultWhenTypeing_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"typeinput_checkbutton1"));
	IsStartUpGeneralUsedCharacter_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"typeinput_checkbutton2"));
	IsToPressSpaceToClearWhenError_CheckButton =GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"typeinput_checkbutton3"));
	IsAutoShowWordMode_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"autoout_checkbutton"));
	IsOutputWordWhenTypeSpace_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"autoout_checkbutton1"));
	IsShiftPositionWhenSelect_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"autoout_checkbutton2"));
	IsAutoOutputWordWhenLetterFull_CheckButton = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"emptyout_checkbutton"));
	ContinuedSpaceInfluent_RadioButton = GTK_RADIO_BUTTON(glade_xml_get_widget(xml,"emptyout_radiobutton2"));
	NotContinuedSpaceInfluent_RadioButton = GTK_RADIO_BUTTON(glade_xml_get_widget(xml,"emptyout_radiobutton1"));
	IsToOutputWordWhenPressEnd = GTK_CHECK_BUTTON(glade_xml_get_widget(xml,"pressend_checkbutton"));
	SpecialLetter_Entry = GTK_ENTRY(glade_xml_get_widget(xml,"special_letter_entry"));
*/


	
	GtkBuilder *builder = dialog_data.header.builder;
	InputMethodName_Label = GTK_LABEL( GTK_WIDGET( gtk_builder_get_object(builder, "gencin_dialog_input_method_name_label") ) );
	IsOnAutoShowResultWhenTypeing_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "typeinput_checkbutton1") ) );
	IsStartUpGeneralUsedCharacter_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "typeinput_checkbutton2") ) );
	IsToPressSpaceToClearWhenError_CheckButton =GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "typeinput_checkbutton3") ) );
	IsAutoShowWordMode_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "autoout_checkbutton") ) );
	IsOutputWordWhenTypeSpace_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "autoout_checkbutton1") ) );
	IsShiftPositionWhenSelect_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "autoout_checkbutton2") ) );
	IsAutoOutputWordWhenLetterFull_CheckButton = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "emptyout_checkbutton") ) );
	ContinuedSpaceInfluent_RadioButton = GTK_RADIO_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "emptyout_radiobutton2") ) );
	NotContinuedSpaceInfluent_RadioButton = GTK_RADIO_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "emptyout_radiobutton1") ) );
	IsToOutputWordWhenPressEnd = GTK_CHECK_BUTTON( GTK_WIDGET( gtk_builder_get_object(builder, "pressend_checkbutton") ) );
	SpecialLetter_Entry = GTK_ENTRY( GTK_WIDGET( gtk_builder_get_object(builder, "special_letter_entry") ) );



	 
#if 1
	gtk_label_set_text(InputMethodName_Label, dialog_data.input_method_name);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsOnAutoShowResultWhenTypeing_CheckButton), dialog_data.is_on_auto_show_result_when_typeing);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsStartUpGeneralUsedCharacter_CheckButton), dialog_data.is_start_up_general_used_character);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsToPressSpaceToClearWhenError_CheckButton),dialog_data.is_to_press_space_to_clear_when_error);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsAutoShowWordMode_CheckButton), dialog_data.is_auto_show_word_mode);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsOutputWordWhenTypeSpace_CheckButton), dialog_data.is_output_word_when_type_space);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsShiftPositionWhenSelect_CheckButton), dialog_data.is_shift_position_when_select);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsAutoOutputWordWhenLetterFull_CheckButton), dialog_data.is_auto_output_word_when_letter_full);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ContinuedSpaceInfluent_RadioButton),dialog_data.is_continued_space_influent);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(NotContinuedSpaceInfluent_RadioButton), !dialog_data.is_continued_space_influent);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsToOutputWordWhenPressEnd), dialog_data.is_to_output_word_when_press_end);
	gtk_entry_set_text(SpecialLetter_Entry,dialog_data.special_letter);
#else
	dialog_data_assign_to_gui(&dialog_data);
#endif //#if 0	


	internal_sensitive_filter();
	dialog_data.header.is_dialog_press_accept = FALSE;

} //gencin_dialog_ctor()

static void dialog_data_assign_to_gui(gencin_dialog_data_t* d)
{
	gtk_label_set_text(InputMethodName_Label, d->input_method_name);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsOnAutoShowResultWhenTypeing_CheckButton), d->is_on_auto_show_result_when_typeing);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsStartUpGeneralUsedCharacter_CheckButton), d->is_start_up_general_used_character);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsToPressSpaceToClearWhenError_CheckButton),d->is_to_press_space_to_clear_when_error);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsAutoShowWordMode_CheckButton), d->is_auto_show_word_mode);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsOutputWordWhenTypeSpace_CheckButton), d->is_output_word_when_type_space);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsShiftPositionWhenSelect_CheckButton), d->is_shift_position_when_select);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsAutoOutputWordWhenLetterFull_CheckButton), d->is_auto_output_word_when_letter_full);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ContinuedSpaceInfluent_RadioButton),d->is_continued_space_influent);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(NotContinuedSpaceInfluent_RadioButton), !(d->is_continued_space_influent));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(IsToOutputWordWhenPressEnd), d->is_to_output_word_when_press_end);
	gtk_entry_set_text(SpecialLetter_Entry,d->special_letter);
} //dialog_data_assign_to_gui()


void gencin_dialog_dtor(GtkObject* me, gpointer data)
{
	printf("[Func %s() is invoked]\n",__func__);


	if(dialog_data.header.is_dialog_press_accept == TRUE)    
		internal_copy_data( &(dialog_data),(gencin_dialog_data_t*)data); 


} //gencin_dialog_dtor()

void gencin_dialog_accept(GtkButton* accept_button, gpointer data)
{
	printf("[Func %s() is invoked]\n",__func__);

	dialog_data.header.is_dialog_press_accept = TRUE;
    gtk_widget_destroy(GTK_WIDGET(dialog_me)); 
/*
gchar* im;
gchar* vstr;
#define SET(a,b,c,d) g_oxim_conf_set((a),(b),(c),(d))
	int VT_BOOL=1;
	gencin_dialog_data_t* r = (gencin_dialog_data_t*)data;
		SET(im,"AutoCompose",&(r->is_on_auto_show_result_when_typeing),VT_BOOL);
		SET(im,"WildEnable",&(r->is_start_up_general_used_character),VT_BOOL);
		SET(im,"SpaceReset",&(r->is_to_press_space_to_clear_when_error),VT_BOOL);

		SET(im,"AutoUpChar",&(r->is_auto_show_word_mode),VT_BOOL);
		SET(im,"SpaceAutoUp",&(r->is_output_word_when_type_space),VT_BOOL);
		SET(im,"SelectKeyShift",&(r->is_shift_position_when_select),VT_BOOL);

		SET(im,"AutoFullUp",&(r->is_auto_output_word_when_letter_full),VT_BOOL);
		SET(im,"SpaceIgnore",(r->is_continued_space_influent)?pFALSE():pTRUE(),VT_BOOL);

		SET(im,"EndKey",&(r->is_to_output_word_when_press_end),VT_BOOL);

		if(r->special_letter==NULL)
			g_utf8_str_assign(vstr,"None");
		else
			if(r->special_letter[0]=='\0')
				g_utf8_str_assign(vstr,"None");
			else
				g_utf8_str_assign(vstr,r->special_letter);
		SET(im,"DisableSelectList",r->special_letter,VT_STRING);
#undef SET
*/

//	if(dialog_data.header.is_dialog_press_accept == TRUE)
//		internal_copy_data( &(dialog_data),(gencin_dialog_data_t*)data);  

//  gtk_widget_hide_all(dialog_me);
//	gtk_dialog_response(dialog_me,0);
 // gtk_main_quit ();
} //gencin_dialog_accept()

void gencin_dialog_reject(GtkButton* reject_button)
{
	printf("[Func %s() is invoked]\n",__func__);
    gtk_widget_destroy(GTK_WIDGET(dialog_me));
//    gtk_widget_hide_all(dialog_me);
//	gtk_dialog_response(dialog_me,0);
 // gtk_main_quit ();
} //gencin_dialog_reject()

void gencin_dialog_default(GtkButton* default_button)
{
	printf("[Func %s() is invoked]\n",__func__);
	dialog_data_assign_to_gui(dialog_data.default_value);
	internal_sensitive_filter();
} //gencin_dialog_default()


void internal_toggle_event_manager(GtkToggleButton* btn)
{
	typedef struct
	{
		gpointer* pToggle;
		gboolean* pBool;
	} toggle_gboolean_map_t;

	static toggle_gboolean_map_t toggle_gboolean_map[]=
	{
		{(gpointer*)&IsOnAutoShowResultWhenTypeing_CheckButton, &dialog_data.is_on_auto_show_result_when_typeing},
		{(gpointer*)&IsStartUpGeneralUsedCharacter_CheckButton, &dialog_data.is_start_up_general_used_character},
		{(gpointer*)&IsToPressSpaceToClearWhenError_CheckButton, &dialog_data.is_to_press_space_to_clear_when_error},
	
		{(gpointer*)&IsAutoShowWordMode_CheckButton, &dialog_data.is_auto_show_word_mode},
		{(gpointer*)&IsOutputWordWhenTypeSpace_CheckButton, &dialog_data.is_output_word_when_type_space},
		{(gpointer*)&IsShiftPositionWhenSelect_CheckButton, &dialog_data.is_shift_position_when_select},
		
		{(gpointer*)&IsAutoOutputWordWhenLetterFull_CheckButton, &dialog_data.is_auto_output_word_when_letter_full},
		{(gpointer*)&ContinuedSpaceInfluent_RadioButton, &dialog_data.is_continued_space_influent},
	
		{(gpointer*)&IsToOutputWordWhenPressEnd, &dialog_data.is_to_output_word_when_press_end},
	};

	static gint toggle_gboolean_map_size = sizeof(toggle_gboolean_map)/sizeof(toggle_gboolean_map_t);
	
	gint idx;
	for(idx=0;idx < toggle_gboolean_map_size; idx++)
		if( *(toggle_gboolean_map[idx].pToggle) ==btn)
			*(toggle_gboolean_map[idx].pBool) = gtk_toggle_button_get_active(btn);
	
	internal_sensitive_filter();
} //internal_toggle_event_manager()

