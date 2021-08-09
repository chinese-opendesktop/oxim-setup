#ifndef _UTILS_H
#define _UTILS_H


void g_utf8_str_append(gchar* str, const gchar* append);
void g_utf8_str_assign(gchar* str, const gchar* assign);
gboolean g_utf8_str_equal(const gchar* str1, const gchar* str2);
gboolean g_utf8_str_from_int(gint integer, gchar** ret_str);
void g_hash_table_free(gpointer mem);

gboolean g_dir_curdir_push(void);
gboolean g_dir_curdir_pop(void);
gboolean g_dir_mkpath(const gchar* basepath, const gchar* path); //make a path from a exist basepath
//if basepath is not exist, then return FALSE;

gint g_str_compare_func(gconstpointer a, gconstpointer b); //GCompareFunc

GList* g_hash_table_mget_keys(GHashTable* hash_table);

//g_font_family_list is implement by gnome API
//but we need to change it to be implemeneted by Pango API in future
GList* gtk_font_family_list(GtkWidget *widget);
gint gtk_font_family_list_sort_callback(gchar *a, gchar *b);
void gtk_font_family_list_free(GList* list);
void g_slice_int_free(gpointer mem);

const gchar* g_get_usertmp_dir(void);
const gchar* g_get_usrlib_dir(void);
const gchar* g_get_userhome_dir(void);
gboolean is_zhtw(void);
const gchar* g_get_glade_fp(void);
const gchar* g_get_gtkrc_fp(void);
#endif //_UTILS_H
