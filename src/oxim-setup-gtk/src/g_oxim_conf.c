

#include "oxim_setup_gtk_global.h"
#include "oxim_setting_and_config.h"
#include "g_oxim_conf.h"
#include "im_default_value.h"
#include "default_input_methods.h"

static oxim_conf_t oxim_conf;
static GHashTable* h = NULL;

static const gchar* setting_filter(gconstpointer value, value_type_t value_type);
static gconstpointer getting_filter(const gchar* conststr,  value_type_t value_type);


static const gchar* g_oxim_conf_table(gint sel); //func(0)->systable, func(1)->first_imtable, func(2)->next_imtable

//gconstpointer of the function is a pointer point to sturct or build-in type, and it could be a cstring since it could also be a pointer point to gchar

static const gchar* g_oxim_conf_table(gint sel) 
{
//func(sel==0) -> systable, func(sel==1) -> first_imtable, func(sel==2) -> next_imtable
	static gchar tablename[256]="";
//	static GHashTableIter* piter = NULL;
//	static GHashTableIter iter;
	static GList* list=NULL;
	static GList* pl= NULL;
	//static gchar* pKey;
	//static gchar* pValue;
	
	if(h==NULL) return NULL;
	switch(sel)
	{
	case 0: //systable
		if(g_hash_table_lookup(h,"SystemSetting")==NULL)
		{
			return NULL;
		}
		else
		{
			g_utf8_strncpy(tablename,"SystemSetting",-1);
			return tablename;
		}
	break;
	case 1: //first_imtable
		//g_hash_table_iter_init(&iter, h);
		//piter = &iter;
		if(1)
		{
		  if(list!=NULL) g_list_free(list);
		  list = NULL;
		  list = g_hash_table_mget_keys(h);
		  if(list==NULL) return NULL;
		  list = g_list_sort(list,g_str_compare_func);
		  pl =NULL;
		  pl = g_list_first(list);
		  if(pl==NULL) return NULL;

		  if(!g_utf8_str_equal(pl->data, "SystemSetting")) return pl->data;
		  pl = g_list_next(pl);
		  if(pl==NULL) return NULL;
		  return pl->data;

		  return pl->data;
		}
		
	break;
	case 2: //next_imtable
		//if(piter==NULL) return NULL;
		if(1)
		{
		  if(list==NULL) return NULL;
		  if(pl==NULL) return NULL;
		  pl = g_list_next(pl);
		  if(pl==NULL) return NULL;
		  if(!g_utf8_str_equal(pl->data, "SystemSetting")) return pl->data;
		  pl = g_list_next(pl);
		  if(pl==NULL) return NULL;
		  return pl->data;
		}
	break;
	} //switch(sel)

#if 0
	if(g_hash_table_iter_next(piter,(gpointer*)&pKey, (gpointer*)&pValue) == TRUE)
	{
		if(g_utf8_str_equal(pKey, "SystemSetting"))
		{
			if(g_hash_table_iter_next(piter,(gpointer*)&pKey, (gpointer*)&pValue) == TRUE)
			{
				g_utf8_strncpy(tablename,pKey,-1);
				return tablename;
			}
			else
			{
				piter=NULL;
				return NULL;
			}
		}
		else
		{
			g_utf8_strncpy(tablename,pKey,-1);
			return tablename;
		}
	}
	else
	{	
		piter=NULL;
		return NULL;
	}
#endif 
	return NULL;
} //g_oxim_conf_table()


gboolean g_oxim_conf_query_eng_name(const gchar* chi_name, gchar** ret_eng_name)
{
#if 0
	if(h==NULL)
	{
		g_printf("(%s:%d)[%s] oxim.conf's hash_table has not been build\n",__FILE__,__LINE__,__func__);
		*ret_eng_name = NULL;
		return FALSE;
	}
	
	GHashTableIter iter;
	gchar* pKey;
	gchar* pValue;
	g_hash_table_iter_init(&iter,h);
	while(g_hash_table_iter_next(&iter,(gpointer*)&pKey, (gpointer*)&pValue))
	{
		if(g_utf8_str_equal(pKey,"SystemSetting")) continue;
		gchar* get_chi_name;
		gchar* eng_name = pKey;
		if(oxim_conf_query_chi_name(eng_name, &get_chi_name))
		{
			if(g_utf8_str_equal(chi_name, get_chi_name))
			{
				g_free(get_chi_name);
				*ret_eng_name = g_strdup(eng_name);
				return TRUE;
			}
			else
			{
				g_free(get_chi_name);
			}
		}//query chi name
	} //traversal hash
	*ret_eng_name = NULL;
	return FALSE;
#else

  *ret_eng_name = NULL;
#if 0
  if(g_utf8_str_equal(chi_name, "中標注音"))*ret_eng_name = g_strdup("cnsphone");
  if(g_utf8_str_equal(chi_name, "中標倉頡"))*ret_eng_name = g_strdup("cnscj");
  if(g_utf8_str_equal(chi_name, "新酷音"))*ret_eng_name = g_strdup("chewing");
  if(g_utf8_str_equal(chi_name, "萬國碼"))*ret_eng_name = g_strdup("unicode");
  if(*ret_eng_name != NULL) return TRUE;
#else
  if(NULL!=default_input_methods_get_engname(chi_name))
  {
    //g_printf("(%s:%d)[%s()] get_engname() get %s\n", __FILE__, __LINE__, __func__, default_input_methods_get_engname(chi_name));
    *ret_eng_name = g_strdup(default_input_methods_get_engname(chi_name));
    return TRUE;
  }
  else
  {
    //g_printf("(%s:%d)[%s()] get_engname() get %s\n", __FILE__, __LINE__, __func__, "NULL");
  }
#endif  



  static gchar tables_path[255];
  gint loopidx=0;
//  static gboolean find_valid=FALSE;

  g_dir_curdir_push();
  for(loopidx=0;loopidx<2;loopidx++)
  {
	if(loopidx==0)
		g_sprintf(tables_path,"%s/.oxim/tables", g_get_userhome_dir());
	else
		g_sprintf(tables_path,"%s/.oxim/tables/%s", g_get_usertmp_dir(), g_get_user_name());
	if(-1==g_chdir(tables_path))continue;

	GError* error=NULL;
	g_chdir(tables_path);
	GDir* gdir = g_dir_open(tables_path,0,&error);
	if(error!=NULL)
	{
	  g_printf("%s",error->message);
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
		eng_name[len-4] = '\0';
		gchar* get_chi_name;

		if(oxim_conf_query_chi_name(eng_name, &get_chi_name))
		{
			if(g_utf8_str_equal(chi_name, get_chi_name))
			{
				g_free(get_chi_name);
				*ret_eng_name = g_strdup(eng_name);
				g_dir_curdir_pop();
				return TRUE;
			}
			else
			{
				g_free(get_chi_name);
			}
		}//query chi name

		
		tmp_file = g_dir_read_name(gdir);
	}
  } //for(idx=0;idx<2;idx++)	
  g_dir_curdir_pop();
  return FALSE;
#endif 

}//g_oxim_conf_query_eng_name()

#if 0
static void API_sample_code(void)
{

if(1) //sample for how to use g_oxim_conf_set and g_oxim_conf_get
{
  g_oxim_conf_reload();
  RGB_t rgb={127,254,255};
  gint attrs[8]={0,111,-2223,333,444,555,666,777};
 
  g_oxim_conf_set("SystemSetting", "ATTR1", "StringAttr1", VT_STRING);
  g_oxim_conf_set("SystemSetting", "ATTR2", &attrs[2], VT_INT);
  g_oxim_conf_set("SystemSetting", "ATTR3", pINT(27), VT_INT);
  g_oxim_conf_set("SystemSetting", "ATTR4", &rgb, VT_RGB);
  g_oxim_conf_set("SystemSetting", "ATTR5", &rgb, VT_RGB);
  g_oxim_conf_set("SystemSetting", "ATTR6", pTRUE(), VT_BOOL);
  g_oxim_conf_set("SystemSetting", "ATTR7", pFALSE(), VT_BOOL);
  g_oxim_conf_set("SystemSetting", "ATTR8", pRGB(1,2,3), VT_RGB);
  
  gchar *ss;
  gint *ii;
  gboolean *bb;
  RGB_t *prgb;
  
  g_oxim_conf_get("SystemSetting","ATTR1",&ss, VT_STRING );
  g_printf("\nget ATTR1's value is %s\n", ss);

  g_oxim_conf_get("SystemSetting","ATTR2",&ii, VT_INT );
  g_printf("\nget ATTR2's value is %d\n", *ii);

  g_oxim_conf_get("SystemSetting","ATTR4",&prgb, VT_RGB);
  g_printf("\nget ATTR4's value is RGB=(%d,%d,%d)\n", prgb->red, prgb->green, prgb->blue);

  g_oxim_conf_get("SystemSetting","ATTR6",&bb, VT_BOOL );
  g_printf("\nget ATTR6's value is %d\n", *bb);

  g_oxim_conf_get("SystemSetting","ATTR7",&bb, VT_BOOL );
  g_printf("\nget ATTR7's value is %d\n", *bb);

  g_oxim_conf_get("SystemSetting","ATTR7",&ss, VT_STRING );
  g_printf("\nget ATTR7's value is %s\n", ss);


  g_oxim_conf_update();
}//if(1)


if(1) //sample of how to travesal InputMethod and SystemSetting table
{

  g_oxim_conf_reload();
  gchar* systable;
  gchar* imtables[100];
  gint imtable_num = 0;
  if(TRUE == g_oxim_conf_systable(&systable))
  {
	
  }
  gint idx = 0;
  if(TRUE == g_oxim_conf_first_imtable(&imtables[0]))
  {
	idx=1;
	while(TRUE==g_oxim_conf_next_imtable(&(imtables[idx])))
	{
		idx++;
	} //while(g_oxim_conf_next_imtable((&imtables[idx])))
  }
  imtable_num = idx;
  if(systable ==NULL)
  {
    g_printf("No SystemSetting Table\n");
  }
  else
  {
    g_printf("%s\n", systable);
  }

  if(imtable_num==0) g_printf("No any imtable \n");
  for(idx=0;idx<imtable_num; idx++)
  {
    if(imtables[idx]==NULL)
    {
      g_printf("imtables[%d] is NULL\n", idx);
    }
    else
    {
      g_printf("imtables[%d] = %s\n",idx, imtables[idx]);
    }
  }

  if(systable != NULL)g_free(systable);
  for(idx=0;idx<imtable_num; idx++)
  {
    if(imtables[idx]==NULL)g_free(imtables[idx]);
  }
  g_oxim_conf_update();

}//if(1)

} //API_sample_code()
#endif //if 0

gboolean g_oxim_conf_remove(const gchar* table, gchar* attribute)
{
	GHashTable* sh;
	if(h==NULL) return FALSE;
	sh = g_hash_table_lookup(h, table);
	if(sh==NULL)return FALSE;
	g_hash_table_remove(sh, attribute);
	return TRUE;
}

gboolean g_oxim_conf_add_imtable(const gchar* table)
{
	g_printf("(%s:%d)[%s(table=%s)] is invoked\n",__FILE__, __LINE__, __func__,table);
	GHashTable* sh=NULL;
	if(h==NULL)
	{ 
	  g_printf("(%s:%d)[%s(table=%s)] Error since h==NULL\n",__FILE__, __LINE__, __func__,table);
	  return FALSE;
	}
	sh = g_hash_table_lookup(h, table);
	if(sh!=NULL)
	{
	  g_printf("(%s:%d)[%s(table=%s)] Error since the inserted imtable has exist\n",__FILE__, __LINE__, __func__,table);
	  return FALSE;
	}
	//sh = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_hash_table_free);
	sh = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
	g_hash_table_insert(h, g_strdup(table), sh);
	
	//Setting initial value here
	g_oxim_conf_set(table, "Circular",pTRUE(), VT_BOOL);
	g_oxim_conf_set(table, "AliasName","",VT_STRING);
	im_default_value_load(table);
	gchar *attr;
	gchar *val;
	if(im_default_value_get_first_attr(&attr))
	{
	  do
	  {
		if(im_default_value_get_value(attr,&val))
		{
		  g_printf("(%s:%d)[%s()] add {%s:%s}\n",__FILE__, __LINE__, __func__, attr,val);
		  g_oxim_conf_set(table, attr, val, VT_STRING);
		  g_free(val);
		}
		g_free(attr);
	  }while(im_default_value_get_next_attr(&attr));
	}
#if 1
  if(1)
  {
	GHashTable* imt=NULL;
	imt = g_hash_table_lookup(h,table);
	if(imt==NULL)
	{
	  g_printf("\n\n(%s:%d)[%s()]\n\n",__FILE__,__LINE__,__func__);
	}
	else
	{
  	  GList* list =NULL;
	  list = g_hash_table_mget_keys(imt);
	  if(list==NULL)
	  {
	    g_printf("\n\n(%s:%d)[%s()]\n\n",__FILE__,__LINE__,__func__);
	  }
	  else
	  {
	    list = g_list_first(list);
	    if(list==NULL)
	    {
		g_printf("\n\n(%s:%d)[%s()]\n\n",__FILE__,__LINE__,__func__);
	    }
	    else
	    {
		g_printf("\n\n attrs=[");
		while(list!=NULL)
		{
		  g_printf("{%s:%s}, ",(gchar*)list->data, (gchar*)g_hash_table_lookup(imt,list->data));
		  
		  list = g_list_next(list);
		}
		g_printf("]\n\n");
	    }
	  }
	}

  }
#endif 
	return TRUE;
}// g_oxim_conf_add_imtable()

gboolean g_oxim_conf_remove_imtable(const gchar* table)
{
	g_printf("(%s:%d)[%s(%s)] invoked\n", __FILE__, __LINE__, __func__, table);
	if(g_utf8_str_equal("SystemSetting",table))
	{
	  g_printf("(%s:%d)[%s(%s)] Cannot remove sys table by this caller\n", __FILE__, __LINE__, __func__, table);
	 return FALSE;
	}
	//g_printf("(%s:%d)[%s(%s)] invoked\n", __FILE__, __LINE__, __func__, table);
	GHashTable* sh;
	if(h==NULL) return FALSE;
	sh = g_hash_table_lookup(h, table);
	if(sh==NULL)return FALSE;
	if(!g_hash_table_remove(h, table))g_printf("(%s:%d)[%s()] g_hash_table_remove failed! \n",__FILE__, __LINE__, __func__);
	return TRUE;
/*
	g_hash_table_remove(sh, attribute);
*/
	return TRUE;
}
//const gchar* setting_filter(gpointer value, value_type_t value_type);
//static gconstpointer getting_filter(const gchar* conststr,  value_type_t value_type);
gboolean g_oxim_conf_c_set( const gchar* table, gchar* attribute, gpointer  value, value_type_t value_type)
{
	GHashTable* sh;
	if(h==NULL) return FALSE;
	sh = g_hash_table_lookup(h, table);
	if(sh==NULL)return FALSE;
	g_hash_table_remove(sh, attribute);
	g_hash_table_insert(sh, g_strdup(attribute), g_strdup(setting_filter(value,value_type)));
	return TRUE;
}// g_oxim_conf_set()

const gboolean* pTRUE(void)
{
	static gboolean vbool=TRUE;
	return &vbool;
}//pTRUE()
const gboolean* pFALSE(void)
{
	static gboolean vbool=FALSE;
	return &vbool;
}//pFALSE()

const gboolean* pBOOL(const gboolean boolvalue )
{
	static gboolean vbool;
	vbool=boolvalue;
	return &vbool;
}//pFALSE()

const RGB_t* pRGB(const guint8 r, const guint8 g, const guint8 b )
{
	static RGB_t vrgb;
	vrgb.red =r;
	vrgb.green = g;
	vrgb.blue = b;
	return &vrgb;
	
}//pRGB()
const gint* pINT(const gint integer)
{
	static gint internal_int;
	internal_int=integer;
	return &internal_int;
}//pINT()

gboolean g_oxim_conf_c_get( const gchar* table, gchar* attribute, gconstpointer* ret_value, value_type_t value_type)
{
//	if(g_utf8_str_equal(table,"SystemSetting")==TRUE)
	if(!g_utf8_str_equal(table,"SystemSetting"))
	{
		if(g_utf8_str_equal(attribute,"OriginalChineseName"))
		{
			gchar* get_chi_name;
			if(oxim_conf_query_chi_name(table, &get_chi_name))
			{
				static gchar temp_chi_name[256];
				g_utf8_strncpy(temp_chi_name, get_chi_name,-1);
				g_free(get_chi_name);
				*ret_value = temp_chi_name;
				return TRUE;
			}
			else
			{	
				*ret_value = NULL;
				return FALSE;

			}
		}
	}
	gchar *str;
	GHashTable* sh;
	if(h==NULL) return FALSE;
	sh = g_hash_table_lookup(h, table);
	if(sh==NULL)return FALSE;
	
	str = g_hash_table_lookup(sh, attribute);
	if(str==NULL)return FALSE;
	
	*ret_value = getting_filter(str,value_type);
	return TRUE;
}// g_oxim_conf_get()

gboolean g_oxim_conf_update(void)
{
	g_printf("[%s () is invoked]\n", __func__);
	oxim_conf_invert(&oxim_conf);

#if 0
	gint idx;
	for(idx=0;idx<=oxim_conf.content.eof_idx; idx++)
	g_printf("%c",oxim_conf.content.content[idx]);
#endif //for debug

	oxim_conf_writefile(&oxim_conf);
	
	return TRUE;
} //g_oxim_conf_update()

gboolean g_oxim_conf_reload(void)
{
	
	static gboolean ever_reload = FALSE;
	if(ever_reload==FALSE)
	{
		ever_reload= TRUE;
		oxim_conf_readfile(&oxim_conf);
		oxim_conf_parse(&oxim_conf);
		h = oxim_conf_get_top_hash_table(&oxim_conf);
	}
	else
	{	
		ever_reload= TRUE;
		oxim_conf_readfile(&oxim_conf);
		oxim_conf_parse(&oxim_conf);
		h = oxim_conf_get_top_hash_table(&oxim_conf);
	}
	return TRUE;
} //g_oxim_conf_reload()



gboolean g_oxim_conf_systable(gchar** ret_systable)
{
	const gchar* ptr = g_oxim_conf_table(0);
	if(ptr==NULL) 
	{
		*ret_systable = NULL;
		return FALSE;
	}
	*ret_systable = g_strdup(ptr);
	return TRUE;
} //g_oxim_conf_systable()

gboolean g_oxim_conf_first_imtable(gchar** ret_imtable)
{
	const gchar* ptr = g_oxim_conf_table(1);
	if(ptr==NULL)
	{
		*ret_imtable = NULL;
		return FALSE;
	}
	*ret_imtable = g_strdup(ptr);
	return TRUE;
} //g_oxim_conf_first_imtable()

gboolean g_oxim_conf_next_imtable(gchar** ret_imtable)
{	
	const gchar* ptr = g_oxim_conf_table(2);
	if(ptr==NULL)
	{
		*ret_imtable = NULL;
		return FALSE;
	}
	*ret_imtable = g_strdup(ptr);
	return TRUE;
} //g_oxim_conf_next_imtable()


static const gchar* setting_filter(gconstpointer value, value_type_t value_type)
{
	static gchar str[256];
	switch(value_type)
	{
	case VT_STRING:
		g_utf8_strncpy(str, (gchar*)value, -1); 
	break;
	case VT_INT:
		g_sprintf(str,"%d", *((gint*)value));
	break;
	case VT_RGB:
		g_sprintf(str,"#%02x%02x%02x", ((RGB_t*)value)->red, ((RGB_t*)value)->green, ((RGB_t*)value)->blue);
	break;
	case VT_BOOL:
		if( *((gboolean*)value) ==TRUE )
			g_utf8_strncpy(str,"Yes",-1);
		else
			g_utf8_strncpy(str,"No",-1);

	break;

	default:
		g_utf8_strncpy(str, "SETTING_FILTER_NO_PROCESS",-1);
	break;
	}
	return str;
} //setting_filter()

static gconstpointer getting_filter(const gchar* conststr,  value_type_t value_type)
{
	//TODO: argument list is wait to changed.
	static gchar str[256]="";
	static gboolean vbool=FALSE;
	static gint vgint=0;
	static RGB_t vrgb={0,0,0};
	g_utf8_strncpy(str,conststr,-1);
	switch(value_type)
	{
	case VT_STRING:
		return (gconstpointer)(str);
	break;
	case VT_INT:
		if(1)
		{
			vgint=0;
			gint idx= ( (str[0]=='-') ? 1 : 0 );
			while(!( str[idx]=='\0' || str[idx]<'0' || str[idx]>'9'))
			{
				vgint=vgint*10 + (str[idx]-'0');
				idx++;
			}
			if(str[idx]!='\0')
			{
g_printf("(%s:%d)[%s()]%s\n",__FILE__,__LINE__,__func__,"GetValueError when parsing string!");
			}
			vgint*= ((str[0]=='-')?-1:1);
		}
		return (gconstpointer)(&vgint);
	break;
	case VT_RGB:
		if(1)
		{
			gint indices[3]={1,3,5};
			guint8* rgbs[3];
			gint idx;
			rgbs[0] = &vrgb.red;
			rgbs[1] = &vrgb.green;
			rgbs[2] = &vrgb.blue;
			for(idx=0;idx<3;idx++)
			{
				gchar *s = &(str[indices[idx]]);
				guint8 *u =rgbs[idx];
				gint vidx;
				for(vidx=0;vidx<2;vidx++)
				{
					guint8 v=s[vidx];
					(*u)= (*u) * 16 + ( (v<='f' && v>='a') ? (10 + v - 'a') : (v-'0') );
				}
			}
		}
		return (gconstpointer)(&vrgb);
	break;
	case VT_BOOL:
		if(g_utf8_str_equal(str, "Yes"))
			vbool=TRUE;
		else
			vbool=FALSE;
		return (gconstpointer)(&vbool);
	break;
	default:
	break;
	}

	return str;
} //getting_filter()






gboolean g_oxim_conf_correct(void) //correct the data stored in g_oxim_conf_ according to oxim.conf and  $HOME/.oxim/tables/*.tab
{

  //(o) Step 1: compare ~/.oxim/tables/*.tab and g_oxim_conf
  //(o) Step 1.1:for e in {g_oxim_conf} - {~/.oxim/tables/*.tab}; do remove e from g_oxim_conf; done
  //(x) Step 1.2:for e in {~/.oxim/tables/*.tab}-{g_oxim_conf}; do add e to g_oxim_conf with default setting; done
  //(x) Step 2: g_oxim_update 
  //(x) Step 3: list_store read g_oxim_conf

  GList* oxim_conf_im_set=NULL;
  GList* tables_im_set=NULL;
  GList* lptr1=NULL;
  static gchar tables_dir[256]="";
  if(tables_dir[0]=='\0')
	g_sprintf(tables_dir,"%s/.oxim/tables/",g_get_userhome_dir());
  
  g_dir_curdir_push();
  if(-1 == g_chdir(tables_dir))
  {
	g_printf("(%s:%d)[%s()] Error! g_chdir(\"%s\")  return -1\n", __FILE__, __LINE__, __func__, tables_dir);
	g_dir_curdir_pop();
	return FALSE;
  }
  GError *error = NULL;
  
  GDir* gdir = g_dir_open(tables_dir, 0,&error);
  if(error !=NULL)
  {
	g_printf("(%s:%d)[%s()] Error! g_dir_open(\"%s\",0,&error) \n", __FILE__, __LINE__, __func__, tables_dir);
	g_print(error->message);
	g_clear_error(&error);	
	g_dir_curdir_pop();
	return FALSE;
  }

  //Here, the dir is sucessful to indicate to ~/.oxim/tables
  if(1) //build tables_im_set
  {
    g_dir_rewind(gdir);
    const gchar* readname;
    do 
    {
      readname = g_dir_read_name(gdir);
      if(readname!=NULL)
      {
	gint len=0;
	while(readname[len]!='\0')len++;
	if(len>4)
	{
	  if(g_utf8_str_equal(&(readname[len-4]), ".tab"))
	  {
		static gchar im[100];
		g_utf8_str_assign(im,readname);
		im[len-4]='\0';
		tables_im_set=g_list_append(tables_im_set, g_strdup(im));
	  }
	}
      }
    }while(readname!=NULL);
  }//if(1) //build tables_im_set

  g_dir_curdir_pop();

  if(1) //build oxim_conf_im_set
  {
    if(h==NULL)
    {
	g_printf("(%s:%d)[%s()] (GHashTable*)h is NULL\n", __FILE__, __LINE__, __func__ );
	return FALSE;
    }
    oxim_conf_im_set = g_hash_table_mget_keys(h);   
  } //if(1) //build oxim_conf_im_set

  if(1) //set a default SystemSetting when there is no SystemSetting
  {
    gboolean need_add_default_SystemSetting = TRUE;
    GList *list = NULL;
    list = g_list_first(oxim_conf_im_set);
    while(list!=NULL)
    {
	if(g_utf8_str_equal(list->data,"SystemSetting"))
	  need_add_default_SystemSetting=FALSE;
	list=g_list_next(list);
    }
    if(need_add_default_SystemSetting)
    {
	g_printf("need_add_default_SystemSetting\n");


	GHashTable* sh = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
	g_hash_table_insert(h,g_strdup("SystemSetting"),sh);
#define add(a,b) g_hash_table_insert(sh,g_strdup((#a)), g_strdup((b)))
	add(DefaultFontName,"AR PL New Sung");
	add(DefaultFontSize,"16");
	add(PreeditFontSize,"13");
	add(SelectFontSize,"16");
	add(StatusFontSize,"16");
	add(MenuFontSize,"13");
	add(SymbolFontSize,"13");
	add(XcinFontSize,"16");
	add(WinBoxColor,"#737173");
	add(BorderColor,"#eeeee6");
	add(LightColor,"#ffffff");
	add(DarkColor,"#b4b29c");
	add(CursorColor, "#7f0000");
	add(CursorFontColor, "#ffff00");
	add(FontColor, "#000000");
	add(ConvertNameColor, "#7f0000");
	add(InputNameColor, "#00007f");
	add(UnderlineColor, "#000000");
	add(KeystrokeColor, "#0000ff");
	add(KeystrokeBoxColor, "#ffffff");
	add(SelectFontColor, "#ffffff");
	add(SelectBoxColor, "#3179ac");
	add(MenuBGColor, "#4c59a6");
	add(MenuFontColor, "#ffffff");
	add(XcinBorderColor, "#ffffff");
	add(XcinBGColor, "#0000ff");
	add(XcinFontColor, "#ffffff");
	add(XcinStatusFGColor, "#00ffff");
	add(XcinStatusBGColor, "#000000");
	add(XcinCursorFGColor, "#ffff00");
	add(XcinCursorBGColor, "#7f0000");
	add(XcinUnderlineColor, "#00ffff");
	add(DefauleInputMethod, "chewing");
	add(XcinStyleEnabled, "No");
	add(OnSpotEnabled, "Yes");
#undef add
	g_printf("need_add_default_SystemSetting\n");
    }//if(need_add_default_SystemSetting)
  } //set a default SystemSetting when there is no SystemSetting


  //TODO: do something here...
  if(1) //show oxim_conf_im_set and tables_im_set
  {
    GList* list;
    g_printf("oxim_conf_im_set = [");
    list = g_list_first(oxim_conf_im_set);
    while(list!=NULL)
    {
	g_printf(",%s ",(gchar*)list->data);
	list = g_list_next(list);
    }
    g_printf("]\n");

    g_printf("tables_im_set = [");

    list = g_list_first(tables_im_set);

    while(list!=NULL)
    {
	g_printf(",%s ",(gchar*)list->data);
	list = g_list_next(list);
    }
    g_printf("]\n");
  }

  if(1) //remove {g_oxim_conf} - {*.tab} from g_oxim_conf, except default im
  {
	GList* l4ocis=NULL;//list for oxim_conf_im_set
	GList* l4tis=NULL; //list for tables_im_set
	l4ocis = g_list_first(oxim_conf_im_set);
	while(l4ocis!=NULL)
	{
	  
	  if(!default_input_methods_is_im_exist(l4ocis->data) && !g_utf8_str_equal("SystemSetting",l4ocis->data))
	  {
	    gboolean need_delete=TRUE;
	    l4tis=NULL;
	    l4tis = g_list_first(tables_im_set);
	    while(l4tis!=NULL)
	    {
		if(g_utf8_str_equal(l4tis->data, l4ocis->data)) need_delete=FALSE;
		l4tis = g_list_next(l4tis);
	    }
	    if(need_delete) 
	    {
		if(!g_oxim_conf_remove_imtable((const gchar*)(l4ocis->data)) )
		{
		  g_printf("(%s:%d)[%s()] Error when deleting  im in g_oxim_conf\n", __FILE__, __LINE__, __func__);
		}
	    }
	  }
	  l4ocis = g_list_next(l4ocis);
	}
  } //if(1) //remove {g_oxim_conf} - {*.tab} from g_oxim_conf, except default im

  if(1) //add {*.tab} - {g_oxim_conf} into *.tab
  {
	GList* l4ocis=NULL;//list for oxim_conf_im_set
	GList* l4tis=NULL; //list for tables_im_set
	l4tis = g_list_first(tables_im_set);
	while(l4tis!=NULL)
	{
	  gboolean need_add=TRUE;
	  l4ocis=NULL;
	  l4ocis = g_list_first(oxim_conf_im_set);
	  while(l4ocis!=NULL)
	  {
		if(g_utf8_str_equal(l4tis->data, l4ocis->data)) need_add=FALSE;
		l4ocis = g_list_next(l4ocis);
	  }
	  if(need_add) 
	  {
		if(!g_oxim_conf_add_imtable(l4tis->data)) g_printf("(%s:%d)[%s()] Error when add im into g_oxim_conf by invoked g_oxim_conf_add_imtable(%s)\n", __FILE__, __LINE__, __func__,(gchar*)l4tis->data);
	  }
 	  l4tis = g_list_next(l4tis);
	} 
  }

  if(1) //add build-in input methods 
  {
    const gchar *im = NULL;
    im = default_input_methods_get_first_im();
    while(im!=NULL)
    {
	g_printf("default im =%s\n",im);
	GList* list=NULL;
	list = g_list_first(oxim_conf_im_set);
	gboolean need_add_buildin_setting_to_oxim_conf = TRUE;
	while(list!=NULL)
	{
	  if(g_utf8_str_equal(list->data,im))
		need_add_buildin_setting_to_oxim_conf=FALSE;
	  list=g_list_next(list);
	}
	if(need_add_buildin_setting_to_oxim_conf)
	{
		g_oxim_conf_add_imtable(im);
	}
	
	im = default_input_methods_get_next_im();
    }
  } //add build-in input methods 

  if(0) //test the function in default_input_methods.h
  {
    const gchar* text;
    text = default_input_methods_get_first_im();
    while(text!=NULL)
    {
	const gchar *eng; 
	const gchar *chi;
	chi = default_input_methods_get_chiname(text);
	eng = default_input_methods_get_engname(chi);
	g_printf("default im=%s, get_eng=%s, get_chi=%s\n",text,eng,chi);
	text = default_input_methods_get_next_im();

    }
    text = default_input_methods_get_first_im();
    while(text!=NULL)
    {
	const gchar *eng; 
	const gchar *chi;
	chi = default_input_methods_get_chiname(text);
	eng = default_input_methods_get_engname(chi);
	g_printf("default im=%s, get_eng=%s, get_chi=%s\n",text,eng,chi);
	text = default_input_methods_get_next_im();

    }
  }

  //release oxim_conf_im_set
  g_list_free(oxim_conf_im_set);

  if(1) //release tables_im_set
  {
    lptr1 = g_list_first(tables_im_set);

    while(lptr1 != NULL)
    {
	g_free(lptr1->data);
	lptr1 = g_list_next(lptr1);
    }
    g_list_free(tables_im_set);

  } //if(1) //release tables_im_set  

  g_dir_curdir_pop();
  return TRUE;
} //g_oxim_conf_correct()




gboolean g_oxim_conf_has_imtable(const gchar* imtable)
{
	if(h==NULL) return FALSE;
	GHashTable* sh = NULL;
	sh = g_hash_table_lookup(h,imtable);
	if(sh == NULL)
	  return FALSE;
	else
	  return TRUE;
} //g_oxim_conf_has_imtable()
