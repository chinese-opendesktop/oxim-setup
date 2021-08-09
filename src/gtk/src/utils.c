#include "oxim_setup_gtk_global.h"
#include "utils.h"

void g_utf8_str_assign(gchar* str, const gchar* assign)
{	
	g_utf8_strncpy(str, assign,-1);
} //g_utf8_str_assign()


gboolean is_zhtw(void) //check whether it's zh_TW
{
	
	if(!strncmp(g_getenv("LANG"),"zh_TW",5))
	  return TRUE;
	else
	  return FALSE;
}//is_zh_tw()

void g_utf8_str_append(gchar* str, const gchar* append)
{
	
	GString *gstr = g_string_new(str);
	g_string_append(gstr, append);
	g_utf8_strncpy(str, gstr->str,-1);
	g_string_free(gstr, TRUE);
} //g_utf8_str_append()


gboolean g_utf8_str_equal(const gchar* str1, const gchar* str2)
{
	GString *gstr1 = g_string_new(str1);
	GString *gstr2 = g_string_new(str2);
	gboolean isEqual = g_string_equal(gstr1, gstr2);
	g_string_free(gstr1,TRUE);
	g_string_free(gstr2,TRUE);
	return isEqual;
	
/*
	if ( g_strcasecmp((str1),(str2))==0 )
		return TRUE;
	else
		return FALSE;
*/
} //g_utf8_str_euqal()


gboolean g_utf8_str_from_int(gint integer, gchar** ret_str)
{
	static gchar strstore[100];
	g_sprintf(strstore,"%d",integer);
	*ret_str = g_strdup(strstore);
	return TRUE;

}//g_utf8_str_from_int


void g_hash_table_free(gpointer mem)
{
	g_hash_table_destroy((GHashTable*)mem);

} // g_hash_table_free()

void g_slice_int_free(gpointer mem)
{
	g_slice_free(gint,mem);
	//g_hash_table_destroy((GHashTable*)mem);
} // g_slice_int_free()



static gchar* curdir_stack[100];
static gint curdir_stack_top=0; //0 is empty
gboolean g_dir_curdir_push(void)
{
	if(curdir_stack_top>=100) return FALSE;
	curdir_stack[curdir_stack_top++] = g_get_current_dir();
	return TRUE;
} //g_dir_curdir_push()

gboolean g_dir_curdir_pop(void)
{
	if(curdir_stack_top<=0) return FALSE;
	g_chdir(curdir_stack[curdir_stack_top-1]);
	g_free(curdir_stack[curdir_stack_top-1]);
	curdir_stack_top-=1;
	return TRUE;
} //g_dir_curdir_pop()

gboolean g_dir_mkpath(const gchar* basepath, const gchar* path_arg)
{
  g_dir_curdir_push();
  if(-1==g_chdir(basepath))
  {
	g_dir_curdir_pop();
	return FALSE; //dir is on the basepath now...
  }
  static gchar path[1000];
  g_utf8_str_assign(path, path_arg);
  static gchar cur_dir[256];
  gchar sep_ch = '/'; //separator character of filepath
  gchar* path_indicator;
  gchar* begin;
  gchar* end;
  path_indicator = (path[0]==sep_ch)?(&(path[1])):(&(path[0]));
  g_utf8_str_assign(cur_dir, basepath); 

  gint len=0;
  while(cur_dir[len]!='\0')len++;
  if(cur_dir[len-1]==sep_ch) cur_dir[len-1]='\0';
 
  begin=path_indicator;
  end=begin;

  cur_dir[len-1]=sep_ch;
  cur_dir[len]='\0';

  while(!( end[0]=='\0' || (end[0]==sep_ch && end[1]=='\0')) )
  {
	
	if(*end!=sep_ch)
	{
	  end++;
	}
	else
	{
	  *end='\0';
	  g_mkdir( (begin[0]==sep_ch)?(&begin[1]):(&begin[0]) ,0777);
	  g_utf8_str_append(cur_dir, begin);
	  g_chdir(cur_dir);
	  *end=sep_ch;
	  begin=end;
	  end++;
	}
  }
  g_mkdir( (begin[0]==sep_ch)?(&begin[1]):(&begin[0]) ,0777);
  g_dir_curdir_pop();
  return TRUE;
} //g_dir_mkpath()

gint g_str_compare_func(gconstpointer a, gconstpointer b) //GCompareFunc
{
	const gchar* A = a;
	const gchar* B = b;
	gint idx=0;

	while(!(A[idx]!=B[idx] || A[idx]=='\0'))idx++;
	return (A[idx]-B[idx]);
} //g_str_compare_func()





void g_hash_table_get_keys_foreach_callback(gpointer key, gpointer value, gpointer user_data);
void g_hash_table_get_keys_foreach_callback(gpointer key, gpointer value, gpointer user_data)
{
	GList* list = *((GList**)(user_data));
	list = g_list_append(list, key);
	//g_printf("(%s:%d)[%s()] key=%s\n", __FILE__, __LINE__, __func__,key);
	list = g_list_first(list);
	 *((GList**)(user_data)) = list;
} //g_hash_table_get_keys_foreach_callback()
GList* g_hash_table_mget_keys(GHashTable* hash_table)
{
	if(hash_table==NULL) return NULL;
	GList** plist;	
	GList* list = NULL;
	plist =&list;
	g_hash_table_foreach(hash_table,  (GHFunc)(g_hash_table_get_keys_foreach_callback),(gpointer)(plist));
	return *plist;
} //g_hash_table_get_keys()



GList* gtk_font_family_list(GtkWidget *widget)
{
  PangoContext *pangoCtx = gtk_widget_create_pango_context(widget);
  PangoFontFamily **pangoFontFamily = NULL;
  int i, n_families;
  GList *list = NULL;

  pango_context_list_families(pangoCtx, &pangoFontFamily, &n_families);
  printf("%d\n", n_families);
  for(i=0; i<n_families; i++)
  {
	list = g_list_append(list, (char *)pango_font_family_get_name(pangoFontFamily[i]));
  }
  list = g_list_sort(list, GINT_TO_POINTER(gtk_font_family_list_sort_callback));
  g_free(pangoFontFamily);
  g_object_unref(pangoCtx);
  return list;

// 	return gnome_font_family_list();
} //g_font_family_list()

gint gtk_font_family_list_sort_callback(gchar *a, gchar *b)
{
  char j = a[0];
  char k = b[0];
  if(j>k)
	return -1;
  if(j==k)
	return 0;
  if(j<k)
	return 1;
}

void gtk_font_family_list_free(GList* list)
{
  return;
// 	gnome_font_family_list_free(list);
} //gtk_font_family_list_free()


const gchar* g_get_usrlib_dir(void)
{
	static gchar* usrlib_str = NULL;
	if(usrlib_str==NULL)
	{
//#if __WORDSIZE == 64
//	  usrlib_str = g_strdup("/usr/lib64");
//#else
	  usrlib_str = g_strdup("/usr/lib");
//#endif
	}
	return usrlib_str;
} // g_get_usrlib_dir()
const gchar* g_get_userhome_dir(void)
{
	static gchar* userhome = NULL;
	if(userhome==NULL)
	{
		userhome = g_strdup(g_getenv("HOME"));
	}
	return userhome;
}//g_get_userhome_dir()

const gchar* g_get_usertmp_dir(void)
{
	static gchar* usertmp = NULL;
	if(usertmp ==NULL)
	{
	  usertmp = g_strdup_printf("%s/oxim-setup-gtk.%s", g_get_tmp_dir(), g_get_user_name());
	}
	return usertmp;
} //g_get_usertmp_dir()

const gchar* g_get_glade_fp(void)
{
	static gchar* fp=NULL;
	if(!fp)
	{
	  fp = g_strdup_printf("%s/oxim-setup/oxim-setup-gtk/oxim-setup-glade.xml", g_get_usrlib_dir());
	  if(! g_file_test(fp, G_FILE_TEST_EXISTS) ) 
	  {
	    g_printf("(%s:%d)[%s()] return %s, but the file is not exist\n", __FILE__, __LINE__, __func__,fp);
	  }	
	  else
	  {
	    g_printf("(%s:%d)[%s()] return %s, and the file is already exist\n", __FILE__, __LINE__, __func__,fp);
	  }

	}
	return fp;
}//g_get_glade_fp()

const gchar* g_get_gtkrc_fp(void)
{
	static gchar* fp=NULL;
	if(!fp)
	{
	  fp = g_strdup_printf("%s/oxim-setup/oxim-setup-gtk/gtkrc", g_get_usrlib_dir());
	  if(! g_file_test(fp, G_FILE_TEST_EXISTS) ) 
	  {
	    g_printf("(%s:%d)[%s()] return %s, but the file is not exist\n", __FILE__, __LINE__, __func__,fp);
	  }
	  else
	  {
	    g_printf("(%s:%d)[%s()] return %s, and the file is already exist\n", __FILE__, __LINE__, __func__,fp);
	  }
	}

	return fp;
}//g_get_glade_fp()


