#ifndef CHEWING_H
#define CHEWING_H
//include this header file after oxim_setup_gtk_global.h
//since the struct dialog_data_header_t is defined at oxim_setup_gtk_global.h




typedef enum
{
	CMK_STD_PH=0, //標準注音鍵盤
	CMK_SHU,//許氏鍵盤
	CMK_IBM,//IBM
	CMK_SYSTEX,//精業
	CMK_ET,//椅天鍵盤
	CMK_ET26,//倚天26鍵
	CMK_DVORAK,//DVORAK
	CMK_DVORAK_SHU,//DVORAK 許氏
	CMK_HANYU,//漢語拚音
	CMK_SIZE,
} chewing_keyboard_map_t;
typedef enum
{
	CSM_1234=0,//1234567890
	CSM_GWER,//qwertyuiop
	CSM_ASDF,//asdfghjkl;
	CSM_ZXCV,//zxcvbnm,./
	CSM_SIZE,
} chewing_select_t;
typedef enum
{
	CCM_LOWER_CASE=0,
	CCM_UPPER_CASE,
	CCM_SIZE,
} chewing_capslock_t;

typedef struct
{
	dialog_data_header_t header;
	chewing_keyboard_map_t keymap;
	chewing_select_t select;
	chewing_capslock_t capslock;
} chewing_dialog_data_t;

void chewing_dialog_ctor(GtkWidget* me, gpointer data);
void chewing_dialog_dtor(GtkObject* me, gpointer data);
void chewing_dialog_accept(GtkButton* accept_button);
void chewing_dialog_reject(GtkButton* reject_button);



#endif //CHEWING_H
