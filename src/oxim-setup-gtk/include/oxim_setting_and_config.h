

#ifndef OXIM_SETTING_AND_CONFIG_H_
#define OXIM_SETTING_AND_CONFIG_H_


typedef struct 
{
	gchar content[65535];
	gint eof_idx;
}file_content_t;

typedef struct
{
	file_content_t content;
	GHashTable* ocht; //ocht is abbrevation of  oxim.conf hash table
} oxim_conf_t;


typedef struct
{
	file_content_t content;
	GHashTable* h_sites;
} mirrors_site_t;

gboolean oxim_conf_readfile(oxim_conf_t* me);
gboolean oxim_conf_parse(oxim_conf_t* me);
GHashTable* oxim_conf_get_top_hash_table(oxim_conf_t* me);
void oxim_conf_invert(oxim_conf_t *me); 
void oxim_conf_writefile(oxim_conf_t* me);
void oxim_conf_showdata(oxim_conf_t* me);
gboolean oxim_conf_query_chi_name(const gchar* eng_name, gchar** ret_chi_name);


void mirrors_site_readfile(mirrors_site_t* me);
void mirrors_site_parse(mirrors_site_t* me);
GHashTable* mirrors_site_get_top_hash_table(mirrors_site_t* me);
void mirrors_site_invert(mirrors_site_t *me);
void mirrors_site_writefile(mirrors_site_t* me);


//static void file_content_readfile(file_content_t* me, const gchar* filename);
//static void file_content_writefile(file_content_t* me, const gchar* filename);




void show_result(void);

#endif //OXIM_SETTING_AND_CONFIG_H_
