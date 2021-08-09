#include "oxim_setup_gtk_global.h"
#include "default_input_methods.h"
#include "tab_info.h"
#include <locale.h>
typedef struct _item_t item_t;
struct _item_t
{
	gchar* engname;
	gchar* chiname;
}; //_item_t
static GList* data_list = NULL;
static GHashTable* query_engname_table = NULL;
static GHashTable* query_chiname_table = NULL;
static void add_item(const gchar* engname, const gchar* chiname);
static void default_input_methods_init_module(void);
static gboolean has_init=FALSE;
static void default_input_methods_init_module(void);


static void add_item(const gchar* engname, const gchar* chiname)
{
  //precondition 1 is that caller are default_input_methods_init_module
  if(engname == NULL || chiname == NULL ) //precondition 2
	return; 
  gchar* eng = g_strdup(engname);
  gchar* chi = g_strdup(chiname);  
  g_hash_table_insert(query_chiname_table, eng,chi);
  g_hash_table_insert(query_engname_table, chi,eng);
  item_t* p_item = g_slice_alloc(sizeof(item_t));
  p_item->engname = eng;
  p_item->chiname = chi;
  data_list = g_list_append(data_list,p_item);

} //add_item()

static void default_input_methods_init_module(void)
{
  if(has_init==TRUE) return;

  query_chiname_table = g_hash_table_new_full(g_str_hash, g_str_equal ,NULL,NULL);
  query_engname_table = g_hash_table_new_full(g_str_hash, g_str_equal ,NULL,NULL);
  data_list = NULL;
  

#if 0
  gchar *loc = (gchar*)g_strdup(setlocale(LC_MESSAGES, NULL));
  if(!strncmp("zh_", (char*)loc,3))
  {
    add_item("cnsphone","中標注音");
    add_item("cnscj","中標倉頡");
  }
  else
  {
    add_item("cnsphone","CnsPhone");
    add_item("cnscj","CnsCJ");
  }
  g_free(loc);
#endif

#if 1

  g_dir_curdir_push();
  static gchar* tables_path=NULL;
  //static const gchar tables_path[] = "/usr/lib/oxim/tables/";
  if(tables_path==NULL) tables_path = g_strdup_printf("%s/oxim/tables/", g_get_usrlib_dir());
  if(-1==g_chdir(tables_path))
  {
    g_printf("(%s:%d)[%s()] g_chdir(%s) return -1, plz check whether %s is exist\n", __FILE__, __LINE__, __func__, tables_path, tables_path);
    return;
  }
  GError* error=NULL;
  GDir* gdir = g_dir_open(tables_path,0,&error);
  if(error!=NULL)
  {
    g_printf("%s", error->message);
    g_clear_error(&error);
  }
  g_dir_rewind(gdir);
  const gchar* tmp_file=NULL;
  
  tmp_file = g_dir_read_name(gdir);
  while(tmp_file!=NULL)
  {
    static gchar  eng_name[100];
    g_utf8_str_assign(eng_name, tmp_file);


    gint len=0;
    while(eng_name[len]!='\0')len++; 
    if(strcmp(&eng_name[len-3],"tab")) 
    {
	g_printf("(%s:%d)[%s()] %s is not .tab file\n",__FILE__,__LINE__, __func__, eng_name); 
        tmp_file = g_dir_read_name(gdir);
	continue;
    }

    g_printf("\n\n -- \n\n");
    eng_name[len-4] = '\0';

    gchar* filepath = g_strdup_printf("%s/%s", tables_path, tmp_file);
    if(! g_file_test(filepath, G_FILE_TEST_EXISTS) )
    g_printf("(%s:%d)[%s()] filepath is %s\n",__FILE__,__LINE__, __func__, filepath); 

    gchar* eng;
    gchar* get_chi_name;	
    if(tab_info_get_name(filepath, &get_chi_name, &eng))
    { 
	add_item(eng_name, (const gchar*)get_chi_name);
	g_free(get_chi_name);
    }
    g_free(filepath);
    tmp_file = g_dir_read_name(gdir);
  }

  g_dir_curdir_pop();
 
#endif 

#if 0
  add_item("chewing","新酷音");
  add_item("unicode","萬國碼");
#else
  add_item("chewing",_("chewing"));
  add_item("unicode",_("Unicode"));
#endif
  has_init=TRUE;
}



const gchar* default_input_methods_get_first_im(void)
{
  if(!has_init)default_input_methods_init_module();
  if(data_list==NULL) return NULL;
  data_list = g_list_first(data_list);
  if(data_list==NULL) return NULL;
  return ((item_t*)(data_list->data))->engname;
} //default_input_methods_get_first_im()


const gchar* default_input_methods_get_next_im(void)
{
  if(!has_init)default_input_methods_init_module();
  if(data_list==NULL) return NULL;
  GList* tmplist = NULL;
  tmplist  = g_list_next(data_list);
  if(tmplist==NULL) return NULL;
  data_list = g_list_next(data_list);
  return ((item_t*)(data_list->data))->engname;
} //default_input_methods_get_next_im()


gboolean default_input_methods_is_im_exist(const gchar* im)
{
  if(!has_init)default_input_methods_init_module();
  if(!g_hash_table_lookup(query_chiname_table,im))
	return FALSE;
  else
	return TRUE;
} //default_input_methods_is_im_exist()


const gchar* default_input_methods_get_chiname(const gchar* im)
{
  if(!has_init)default_input_methods_init_module();
  return (const gchar*) g_hash_table_lookup(query_chiname_table,im);
} //default_input_methods_get_chiname()


const gchar* default_input_methods_get_engname(const gchar* chiname)
{
  if(!has_init)default_input_methods_init_module();
  return (const gchar*) g_hash_table_lookup(query_engname_table,chiname);
} //default_input_methods_get_engname()

