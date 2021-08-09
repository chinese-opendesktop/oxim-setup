
#ifndef _G_OXIM_CONF_H 
#define _G_OXIM_CONF_H

typedef enum
{
	VT_STRING,//to store orginal string, or get orginal string
	VT_INT,//to store string converted from integer.
	VT_BOOL, //TRUE/FALSE to store Yes/No, True/False etc. ret 
	VT_RGB, //triple to store RGB color, or get RGB color.
}value_type_t;

typedef struct
{
	guint8 red;
	guint8 green;
	guint8 blue;
}RGB_t;
#define g_oxim_conf_set(table,attribute,value,value_type)	g_oxim_conf_c_set( (table), (attribute), (gpointer)(value), (value_type))
#define g_oxim_conf_get(table,attribute,ret_value,value_type)	g_oxim_conf_c_get( (table), (attribute), (gconstpointer*)(ret_value), (value_type))

gboolean g_oxim_conf_c_set( const gchar* table, gchar* attribute, gpointer value, value_type_t value_type);
gboolean g_oxim_conf_c_get( const gchar* table, gchar* attribute, gconstpointer* ret_value, value_type_t value_type);
gboolean g_oxim_conf_remove(const gchar* table, gchar* attribute);
gboolean g_oxim_conf_update(void); //update the data into the file oxim.conf
gboolean g_oxim_conf_reload(void); //reload data from file oxim.conf
gboolean g_oxim_conf_correct(void); //correct the data stored in g_oxim_conf_ according to oxim.conf and  $HOME/.oxim/*.tab

gboolean g_oxim_conf_systable(gchar** ret_systable);
//return FALSE if there is no any systable
//g_free the ret_systable when there is no used

gboolean g_oxim_conf_first_imtable(gchar** ret_imtable);
//return FALSE if there is no any imtable
//g_free the ret_imtable when there is no used
gboolean g_oxim_conf_next_imtable(gchar** ret_imtable); 
//return FALSE if there is no next imtable
//g_free the ret_imtable when there is no used.

gboolean g_oxim_conf_has_imtable(const gchar* imtable);


gboolean g_oxim_conf_remove_imtable(const gchar* table);
gboolean g_oxim_conf_add_imtable(const gchar* table);

gboolean g_oxim_conf_query_eng_name(const gchar* chi_name, gchar** ret_eng_name);
const gboolean* pTRUE(void);
const gboolean* pFALSE(void);
const gboolean* pBOOL(const gboolean boolvalue );
const RGB_t* pRGB(const guint8 r, const guint8 g, const guint8 b );
const gint* pINT(const gint integer);

#endif //_OXIM_CONF_INTERFACE_H 
