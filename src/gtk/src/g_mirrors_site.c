

#include "oxim_setup_gtk_global.h"
#include "oxim_setting_and_config.h"
#include "g_mirrors_site.h"

//static gboolean ever_reload = FALSE;
static GHashTable* h_sites = NULL;
static const char* g_mirrors_site_hostname(gint sel);
static mirrors_site_t mirrors_site;




gboolean g_mirrors_site_update(void)
{
	return TRUE;
} //g_mirrors_site_update()

gboolean g_mirrors_site_reload(void)
{
	static gboolean ever_reload = FALSE;
	if(ever_reload==FALSE)
	{
		ever_reload= TRUE;
		mirrors_site_readfile(&mirrors_site);
		mirrors_site_parse(&mirrors_site);
		h_sites = mirrors_site_get_top_hash_table(&mirrors_site);
	}
	else
	{	
		ever_reload= TRUE;
		mirrors_site_readfile(&mirrors_site);
		mirrors_site_parse(&mirrors_site);
		h_sites = mirrors_site_get_top_hash_table(&mirrors_site);
	}
	return TRUE;
} //g_mirrors_site_reload()



static const char* g_mirrors_site_hostname(gint sel)
{
//func(0)->first_hostname, func(1)->next_hostname
	//static gchar hostname[255]="";

	//static GHashTableIter* piter = NULL;
	//static GHashTableIter iter;
	//static gchar* pKey;
	//static gchar* pValue;
	if(h_sites == NULL) return NULL;


	static GList *list = NULL;
	static GList *pl = NULL;
	switch(sel)
	{
	case 0: //first_hostname

		//g_hash_table_iter_init(&iter, h_sites); 	
		//piter = &iter;

		if(1)//g_hash_table_iter_init(&iter, h_sites); & //g_hash_table_iter_next()
		{
		  if(list!=NULL) g_list_free(list);
		  list = NULL;
		  list = g_hash_table_mget_keys(h_sites);
		  if(list==NULL) return NULL;
		  list = g_list_sort(list,g_str_compare_func);
		  pl = NULL;
		  pl = g_list_first(list);
		  if(pl == NULL) return NULL;
		  return pl->data;
		} //if(1) //g_hash_table_iter_init(&iter, h_sites);
	break;
	case 1: //next_hostname
		//if(piter==NULL) return NULL;
		if(1)
		{
		  if(list==NULL) return NULL;
		  if(pl==NULL) return NULL;
		  pl = g_list_next(pl);
		  if(pl==NULL) return NULL;
		  return pl->data;
		}
	break;
	} //switch(sel)
#if 0
	if(g_hash_table_iter_next(piter, (gpointer*)&pKey, (gpointer*)&pValue) == TRUE)
	{
		g_utf8_str_assign(hostname, pKey);
		return hostname;	
	}
	else
	{
		piter=NULL;
		return NULL;
	}
#endif 
	return NULL;
} //g_mirrors_site_hostname()

gboolean g_mirrors_site_first_hostname(gchar** ret_hostname)
{
	const gchar* ptr = g_mirrors_site_hostname(0);
	if(ptr==NULL)
	{
		*ret_hostname = NULL;
		return FALSE;
	}
	*ret_hostname = g_strdup(ptr);
	return TRUE;
} //g_mirrors_site_first_hostname()

gboolean g_mirrors_site_next_hostname(gchar** ret_hostname)
{
	const gchar* ptr = g_mirrors_site_hostname(1);
	if(ptr==NULL)
	{
		*ret_hostname = NULL;
		return FALSE;
	}
	*ret_hostname = g_strdup(ptr);
	return TRUE;
} //g_mirrors_site_next_hostname()

gboolean g_mirrors_site_set( const gchar* hostname, const gchar* attribute, const gchar* value)
{
	if(h_sites==NULL) return FALSE;
	//static gchar* tmp=NULL;
	if(g_utf8_str_equal(attribute,"ftp"))
	{
		g_hash_table_insert(h_sites,g_strdup(hostname),g_strdup(value));
		return TRUE;
	}
	
	if(g_utf8_str_equal(attribute,"connect"))
	{
		
		gchar* ftp_addr = g_strdup(g_hash_table_lookup(h_sites,(gconstpointer)hostname));
		if(ftp_addr==NULL) return FALSE;
		//TODO: Connect FTP to ftp_addr
		

		g_free(ftp_addr);
	}
	
	if(g_utf8_str_equal(attribute,"disconnect"))
	{
		//TODO: Disconnect FTP 
	}

	return TRUE;
} //g_mirrors_site_set()

gboolean g_mirrors_site_get( const gchar* hostname, const gchar* attribute, gchar** ret_value)
{
	*ret_value=NULL;
	if(h_sites==NULL) return FALSE;	
	static gchar* tmp=NULL;
	if(g_utf8_str_equal(attribute,"ftp"))
	{
		tmp = g_hash_table_lookup(h_sites,(gconstpointer)hostname);
		if(tmp)
		{
			*ret_value = g_strdup(tmp);
			return TRUE;
		}
	}
	
	return FALSE;
} //g_mirrors_site_get()

#if 0
void g_mirrors_site_API_sample_code(void)
{
  g_printf("show host name start\n");
  gchar* ret_hostname;
  if(g_mirrors_site_first_hostname(&ret_hostname))
  {
    do{
        gchar* ss;
        gchar empty_str[]="";
        g_printf("hostname = %s , ftp = %s\n", ret_hostname, g_mirrors_site_get(ret_hostname,"ftp",&ss)? ss: empty_str );
        if(ss=NULL)g_free(ss);
        g_free(ret_hostname);
    }while(g_mirrors_site_next_hostname(&ret_hostname));
  }
  g_printf("show host name end\n");


}
#endif 
