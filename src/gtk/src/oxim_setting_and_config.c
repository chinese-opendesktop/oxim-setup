

#include "oxim_setup_gtk_global.h"
#include "oxim_setting_and_config.h"
#include <zlib.h>
#include "default_input_methods.h"
#include "tab_info.h"
#define OXIM_CONF_FILEPATH "~/.oxim/oxim.conf"
#define MIRRORS_SITE_FILEPATH "~/.oxim/mirrors.site"

static gboolean file_content_readfile(file_content_t* me, const gchar* filename);
static void file_content_writefile(file_content_t* me, const gchar* filename);
static gboolean get_name(gchar *filepath, gchar **ret_chi_name, gchar** ret_eng_name);
static gboolean value_need_double_quotation(gchar* str);
//static gboolean value_need_sharp(gchar* str);
//static gboolean query_chi_name(gchar* eng_name, gchar** ret_chi_name);
//static oxim_conf_t oxim_conf;
//static mirrors_site_t mirrors_site;
//static char *realCname(char *c_name, char *e_name);
static gchar* oxim_conf_fp=NULL;
static gchar* mirrors_site_fp=NULL;
static void internal_init(void);
static void internal_init(void)
{
  if(oxim_conf_fp==NULL)
  {
    oxim_conf_fp = g_strdup_printf("%s/.oxim/oxim.conf", g_get_userhome_dir());
    mirrors_site_fp = g_strdup_printf("%s/.oxim/mirrors.site", g_get_userhome_dir());
  }


}

void show_result(void)
{

#if 0
	gchar* get;
	if( g_utf8_str_from_int(-1,&get))
	{
		g_printf("\ng_utf8_str_from_int() get %s\n", get);
		g_free(get);
	}
	else
	{
		g_printf("\nNONO\n");
	}
	
#endif 
#if 1
	static oxim_conf_t oxim_conf;
	oxim_conf_readfile(&oxim_conf);
	oxim_conf_parse(&oxim_conf);
	//GHashTable* ocht = oxim_conf_get_top_hash_table(&oxim_conf);
	//write code
	//oxim_conf_showdata(&oxim_conf);	
	oxim_conf_invert(&oxim_conf);
	oxim_conf_writefile(&oxim_conf);
#endif 	
#if 0
	gchar *chi_name;
	gchar *eng_name;
	if(TRUE==get_name("~/.oxim/tables/uniliu.tab", &chi_name, &eng_name))
	g_printf("\nChinese name is %s, English Name is %s \n", chi_name, eng_name);
	g_free(chi_name);
	g_free(eng_name);
#endif 
	//open gzip file (.tab) by gzopen 


	//g_printf("%s",_("milochen"));
} //show_result()


gboolean oxim_conf_readfile(oxim_conf_t* me)
{
	internal_init();

	//if(!file_content_readfile(&(me->content), OXIM_CONF_FILEPATH))
	if(!file_content_readfile(&(me->content), oxim_conf_fp))
	{
	  g_printf("(%s:%d)[%s()] file_content_readfile failed\n",__FILE__, __LINE__, __func__);
	  static gchar cmd[100];
	  //g_sprintf(cmd, "echo >%s",OXIM_CONF_FILEPATH);
	  g_sprintf(cmd, "cp /etc/oxim/oxim.conf %s/.oxim/",g_get_userhome_dir());
	  system(cmd);
	  //if(!file_content_readfile(&(me->content), OXIM_CONF_FILEPATH))
	  if(!file_content_readfile(&(me->content), oxim_conf_fp))
	  {	
	    g_printf("(%s:%d)[%s()] file_content_readfile failed\n",__FILE__, __LINE__, __func__);
	    return FALSE;
	  }
	  else
	  {
	    g_printf("(%s:%d)[%s()] write empty file and read it\n",__FILE__,__LINE__,__func__);
	    return TRUE;
	  }
	}
	return TRUE;
	//file_content_readfile(&(me->content), "./oxim.conf"); // above is correct

} //oxim_conf_readfile()
void oxim_conf_writefile(oxim_conf_t* me)
{
	
	//file_content_writefile(&(me->content), OXIM_CONF_FILEPATH);
	internal_init();
	file_content_writefile(&(me->content), oxim_conf_fp);

	//file_content_writefile(&(me->content), "./oxim.conf");
} //oxim_conf_writefile()
void mirrors_site_readfile(mirrors_site_t* me)
{
	internal_init();
#if 0
	static gchar fp[100]="\0";
	if(fp[0]=='\0')
		g_sprintf(fp,"%s/.oxim/mirrors.site", g_get_userhome_dir());
		//g_sprintf(fp,"/%s/.oxim/mirrors.site", g_get_user_name());
	g_printf("file is %s\n", fp);
	file_content_readfile(&(me->content), fp);
	g_printf("%s", me->content.content);
#else
	file_content_readfile(&(me->content),mirrors_site_fp);
#endif 
	//file_content_readfile(&(me->content), MIRRORS_SITE_FILEPATH);
	//file_content_readfile(&(me->content), "./mirrors.site");
} //mirrors_site_readfile()
void mirrors_site_writefile(mirrors_site_t* me)
{
	internal_init();
#if 0
	static gchar fp[100]="\0";
	if(fp[0]=='\0')
		g_sprintf(fp,"%s/.oxim/mirrors.site", g_get_userhome_dir());
		//g_sprintf(fp,"/%s/.oxim/mirrors.site", g_get_user_name());
	file_content_writefile(&(me->content), fp);
	//file_content_writefile(&(me->content), MIRRORS_SITE_FILEPATH);
	//file_content_writefile(&(me->content), "./mirrors.site");
#else
	file_content_writefile(&(me->content), mirrors_site_fp);
#endif 
} //mirrors_site_writefile()

void mirrors_site_parse(mirrors_site_t* me)
{
	internal_init();
	gboolean is_valid = TRUE;
	if(me->h_sites == NULL) me->h_sites = g_hash_table_new_full(g_str_hash, g_str_equal,g_free, g_free);
	gint32 idx;
	static gint parse_state; //parse_state=-1 -> error, parse_state=0 -> init_state,
	parse_state = 0;
	for(idx=0;idx < me->content.eof_idx; idx++)
	{
	
		static gchar token;
		token = me->content.content[idx];
		static gchar tmp_str[256];
		static gint tmp_str_idx;
		static gchar key[256];
		static gchar value[256];

		switch(parse_state)
		{
		case -1:
			is_valid=FALSE;
		break;
		case 0: //state for process \"
			value[0]=key[0]=tmp_str[0]='\0';
			tmp_str_idx=0;
			switch(token)
			{
			case '\"':
				parse_state+=1;
			case ' ':
			case '\t':
			case '\n':
			break;
			default:
				parse_state=-1;
			break;
			}//switch(token) for case 0
		break;
		case 1: //state for append left-side string
			switch(token)			
			{
			case '\"':
				//TODO : make key 
				tmp_str[tmp_str_idx]='\0';
				tmp_str_idx=0;
				g_utf8_str_assign(key, tmp_str);
				tmp_str[0]='\0';
				tmp_str_idx=0;
				parse_state+=1;
			break;
			case '\n':
				parse_state=-1;
			break;
			default:
				//TODO: append token to key
				tmp_str[tmp_str_idx++]=token;
			break;
			}//switch(token) for case 1
		break;
		case 2: //state for wait only one '='
			switch(token)
			{
			case '=':
				parse_state+=1;
			case ' ':
			case '\t':
			break;
			default:
				parse_state=-1;
			break;
			}//switch(token) for case 0
		break;
		case 3: //state for wait '\"'
			switch(token)
			{
			case '\"':
				tmp_str_idx=0;
				tmp_str[0]='\0';
				parse_state+=1;
			case ' ':
			case '\t':
			break;
			default:
				parse_state=-1;
			break;
			}//switch(token) for case 1
		break;
		case 4: //state for append right_side string
			switch(token)
			{
			case '\"':
				//TODO : make value
				tmp_str[tmp_str_idx]='\0';
				g_utf8_str_assign(value, tmp_str);
				tmp_str[0]='\0';
				tmp_str_idx=0;
				parse_state+=1;
			break;
			case '\n':
				parse_state=-1;
			break;
			default:
				//TODO: append token to value
				tmp_str[tmp_str_idx++]=token;
			break;
			} //switch(token) for case 4
		break;
		case 5: //state for 
			switch(token)
			{
			case '\n':
				g_hash_table_insert(me->h_sites, g_strdup(key), g_strdup(value));
				parse_state=0;
			case ' ':
			case '\t':
			break;
			default:
				parse_state=-1;
				g_printf("(%s:%d)[%s] %s\n",__FILE__, __LINE__, __func__, "parsing error in final position of a line");
			break;
			} //switch(token) for case 5
		break;
		}//switch(parse_state)
	} //for(idx=0;idx < me->content.eof_idx; idx++)
	//return is_valid;
	return;

} //mirrors_site_parse()

void mirrors_site_invert(mirrors_site_t* me)
{
  internal_init();

} //mirrors_site_invert()

GHashTable* mirrors_site_get_top_hash_table(mirrors_site_t* me)
{
  internal_init();
	return me->h_sites;
	return NULL;
}

static gboolean file_content_readfile(file_content_t* me, const gchar* filename)
{
	internal_init();
	GIOChannel *read;
	gchar *content;
	GError *error = NULL;
	gsize bytes;

	read = g_io_channel_new_file(filename, "r", &error);
	if(error!=NULL)
	{
	  g_printf("(%s:%d)[%s(filename=%s)] g_io_channel_new_file's error msg is[%s]\n",__FILE__, __LINE__, __func__,  filename ,error->message);
	  g_clear_error(&error);
	  return FALSE;
	}
	g_io_channel_read_to_end(read, &content, &bytes, NULL);
	me->eof_idx = bytes;
	g_utf8_strncpy(me->content, content, bytes);
	//g_snprintf(me->content, bytes+1, "%s", content);
	g_io_channel_close(read);
	g_free(content);
	//g_printf("read data is \"%s\"",me->content);
	return TRUE;
	
} //file_content_readfile()
static void file_content_writefile(file_content_t* me, const gchar* filename)
{
	internal_init();
	GIOChannel *write;
	//gchar *content;
	GError *error = NULL;
	gsize bytes;

	write = g_io_channel_new_file(filename, "w", &error);	
	if(error!=NULL)
	{
	  g_printf("(%s:%d)[%s(filename=%s)] g_io_channel_new_file's error msg is[%s]\n",__FILE__, __LINE__, __func__,  filename ,error->message);
	  g_clear_error(&error);
	  return;
	  //return FALSE;
	}

	//g_printf("\neof_idx = %d\n", me->eof_idx);
	//g_printf(me->content);
	
	g_io_channel_write_chars(write, me->content, -1, &bytes, NULL);

	g_io_channel_close(write);
	//return TRUE;
	return;

} // file_content_writefile()












void oxim_conf_showdata( oxim_conf_t *me)
{

#if 0	
	GHashTableIter h_iter;
	gpointer subh;
	gpointer key;
	gpointer value;
	for(g_hash_table_iter_init(&h_iter, me->ocht); g_hash_table_iter_next(&h_iter, &key,&subh) ; )
	{
		GHashTableIter s_iter;
		g_printf("Start Hash Table <%s>\n", (gchar*)key);
		for(g_hash_table_iter_init(&s_iter, subh); g_hash_table_iter_next(&s_iter, &key, &value) ; )
		{
			g_printf("    %s = %s\n",(gchar*)key, (gchar*)value);
		}
		g_printf("END of Hash Table\n");
	} 
#else
	g_printf("(%s:%d)[%s()] The code only can be used when the GLib is not too old to support GHashTableIter\n", __FILE__, __LINE__, __func__);
#endif //#if 0
} //g_oxim_conf_showdata()




static gboolean value_need_double_quotation(gchar* str)
{
	if(g_utf8_str_equal(str,"SetKey")) return FALSE;
	if(g_utf8_str_equal(str,"Circular")) return FALSE;
	return TRUE;
} //value_need_double_quotation()
#if 0
static gboolean value_need_sharp(gchar* str)
{
	static GHashTable* h = NULL;
	if(h==NULL)
	{
		h = g_hash_table_new_full(g_str_hash, g_str_equal,g_free,g_free);
		g_hash_table_insert(h,g_strdup("WinBoxColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("BorderColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("LightColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("DarkColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("CursorColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("CursorFontColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("FontColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("ConvertNameColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("InputNameColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("UnderlineColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("KeystrokeColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("KeystrokeBoxColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("SelectFontColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("SelectBoxColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("MenuBGColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("MenuFontColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinBorderColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinBGColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinFontColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinStatusFGColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinStatusBGColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinCursorFGColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinCursorBGColor") ,g_strdup(""));
		g_hash_table_insert(h,g_strdup("XcinUnderlineColor") ,g_strdup(""));
	}
	if(h==NULL) return FALSE;
	if(g_hash_table_lookup(h,str)==NULL) return FALSE;

	return TRUE;
} //value_need_sharp
#endif

void oxim_conf_invert(oxim_conf_t *me)
{	
	internal_init();
	gchar* str = me->content.content;
	g_utf8_str_assign(str,"");
	//gpointer key;
	//gpointer value;

#if 0
	GHashTableIter h_iter;
	gpointer subh;
	gpointer key;
	gpointer value;
	//static gchar line_data[256];

	for(g_hash_table_iter_init(&h_iter, me->ocht); g_hash_table_iter_next(&h_iter, &key,&subh) ; )
	{
		gboolean syssettingflag=FALSE;
		GHashTableIter s_iter;
		//g_printf("Start Hash Table <%s>\n", (gchar*)key);
		if(g_utf8_str_equal((gchar*)key,"SystemSetting"))
		{
			g_utf8_str_append(str,"<SystemSetting>\n");
			syssettingflag=TRUE;
		}
		else
		{
			g_utf8_str_append(str,"\n");
			g_utf8_str_append(str,"#\n");
			gchar* get_chi_name;
			if(oxim_conf_query_chi_name((gchar*)key, &get_chi_name))
			{
				g_utf8_str_append(str,"# ");
				g_utf8_str_append(str,get_chi_name);
				g_utf8_str_append(str,"\n");
				g_free(get_chi_name);
			}
			else
			{
				g_utf8_str_append(str,"# ErrorChineseName\n");
			}
			g_utf8_str_append(str,"#\n");
			g_utf8_str_append(str,"<InputMethod \"");
			g_utf8_str_append(str,(gchar*)key);
			g_utf8_str_append(str,"\">\n");

		}
	
		for(g_hash_table_iter_init(&s_iter, subh); g_hash_table_iter_next(&s_iter, &key, &value) ; )
		{
			static gchar tmpstr[100];
			if(value_need_double_quotation(key))
			{
				g_sprintf(tmpstr,"\t%s = \"%s\"\n", (gchar*)key, (gchar*)value);
			}
			else
			{
				g_sprintf(tmpstr,"\t%s = %s\n", (gchar*)key, (gchar*)value);
			}

			g_utf8_str_append(str,tmpstr);
		}
		//g_printf("END of Hash Table\n");

//		if(g_utf8_str_equal((gchar*)key,"SystemSetting"))
		if(syssettingflag==TRUE)
		{
			g_utf8_str_append(str,"</SystemSetting>\n");
		}
		else
		{		
			g_utf8_str_append(str,"</InputMethod>\n");

		}
	} //for(g_hash_table_iter_init(&h_iter, me->ocht); g_hash_table_iter_next(&h_iter, &key,&subh) ; )
#else

	GList* plist = NULL;
	GList* clist = NULL;
	GList* pl = NULL;
	GList* cl = NULL;
	
	plist = g_hash_table_mget_keys(me->ocht);
	if(plist == NULL) g_printf("(%s:%d)[%s()] \"plist = g_hash_table_get_keys(me->ocht)\" is failed\n", __FILE__, __LINE__, __func__);
	pl = g_list_first(plist);
	if(pl==NULL)  g_printf("(%s:%d)[%s()] \"pl = g_list_first(plist);\" is failed\n", __FILE__, __LINE__, __func__);
	while(pl!=NULL)
	{
	  //static gchar tablename[100]="";
	  GHashTable* subh=NULL;
	  if(pl->data==NULL) g_printf("(%s:%d)[%s()]  pl->data; is NULL\n", __FILE__, __LINE__, __func__);
	  subh = g_hash_table_lookup(me->ocht, pl->data);
	  if(subh==NULL) g_printf("(%s:%d)[%s()] \"   \" is failed\n", __FILE__, __LINE__, __func__);


	  gboolean syssettingflag=FALSE;
	  //GHashTableIter s_iter;
	  //g_printf("Start Hash Table <%s>\n", (gchar*)key);
	  if(g_utf8_str_equal((gchar*)(pl->data),"SystemSetting"))
	  {
	    g_utf8_str_append(str,"<SystemSetting>\n");
	    syssettingflag=TRUE;
	  }
	  else
	  {
	    g_utf8_str_append(str,"\n");
	    g_utf8_str_append(str,"#\n");
	    gchar* get_chi_name;
	    if(oxim_conf_query_chi_name((gchar*)(pl->data), &get_chi_name))
	    {
		g_utf8_str_append(str,"# ");
		g_utf8_str_append(str,get_chi_name);
		g_utf8_str_append(str,"\n");
		g_free(get_chi_name);
	    }
	    else
	    {
		g_utf8_str_append(str,"# ErrorChineseName\n");
	    }
	    g_utf8_str_append(str,"#\n");
	    g_utf8_str_append(str,"<InputMethod \"");
	    g_utf8_str_append(str,(gchar*)(pl->data));
	    g_utf8_str_append(str,"\">\n");
	  }

	  

	  cl = NULL;
	  clist = NULL;
	  clist = g_hash_table_mget_keys(subh);
	  if(clist == NULL) g_printf("(%s:%d)[%s()] \"clist = g_hash_table_get_keys(subh)\" is failed\n", __FILE__, __LINE__, __func__);
	  clist = g_list_sort(clist, g_str_compare_func);
	  cl = g_list_first(clist);
	  if(cl==NULL)  g_printf("(%s:%d)[%s()] \"cl = g_list_first(clist);\" is failed\n", __FILE__, __LINE__, __func__);
	  while(cl!=NULL)
	  {
	    static gchar tmpstr[100];
	    if(value_need_double_quotation(cl->data))
	    {
		g_sprintf(tmpstr,"\t%s = \"%s\"\n", (gchar*)(cl->data), (gchar*)(g_hash_table_lookup(subh,cl->data)));
	    }
	    else
	    {
		g_sprintf(tmpstr,"\t%s = %s\n", (gchar*)(cl->data), (gchar*)(g_hash_table_lookup(subh,cl->data)));
	    }
	    g_utf8_str_append(str,tmpstr);
	    cl=g_list_next(cl);
	  } //while(cl!=NULL);
	  g_list_free(clist);
	  clist = NULL;

	  if(syssettingflag==TRUE)
	  {
	    g_utf8_str_append(str,"</SystemSetting>\n");
	  }
	  else
	  {		
	    g_utf8_str_append(str,"</InputMethod>\n");
	  }
	  pl = g_list_next(pl);
	} //while(pl!=NULL)
	g_list_free(plist);
	plist = NULL;
	//for(g_hash_table_iter_init(&h_iter, me->ocht); g_hash_table_iter_next(&h_iter, &key,&subh) ; )	
	//	for(g_hash_table_iter_init(&s_iter, subh); g_hash_table_iter_next(&s_iter, &key, &value) ; )

#endif 


	//g_printf("START \n\n%s\n\n ENDE", str);


} //oxim_conf_invert()




































GHashTable* oxim_conf_get_top_hash_table(oxim_conf_t *me)
{
	return me->ocht;
} //oxim_conf_get_top_hash_table()


gboolean oxim_conf_parse(oxim_conf_t* me)
{

	gboolean is_valid = TRUE;


	//if(me->ocht== NULL) me->ocht = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,g_hash_table_destroy);
	
#if 1
	if(me->ocht!=NULL)
	{
		g_hash_table_destroy(me->ocht);
		me->ocht=NULL;
	}

#endif //milochen add

	if(me->ocht== NULL) me->ocht = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,g_hash_table_free);
	
	//oxim_conf_readfile(&oxim_conf);
	gint32 idx;
	for(idx=0; idx < me->content.eof_idx; idx++)
	{
		static gchar token;
		static gchar line_data[512];
		static gint line_data_idx=0;
		token  = me->content.content[idx];

		line_data[line_data_idx++] = token;

		if(token=='\n' || idx==me->content.eof_idx-1)
		{
			static gchar setting_on[100]="";

			line_data[line_data_idx++]='\0';
			if(line_data[0]=='#')
			{
				if(line_data_idx < 4 )
				{	
					//TODO: just have a '#' but without any useful information
				}
				else
				{
					//TODO: Chinese name of InputMethod that show out following at #
					gint idx;
					for(idx=2;idx<line_data_idx; idx++)
					{
						if(line_data[idx]=='\n') 
						{
							line_data[idx]='\0';
							//g_printf("# parse---%s---\n", &line_data[2]);
							line_data[idx]='\n';
						}
					}
				}
			} // if(line_data[0]=='#')
			else if(line_data[0]=='<')
			{
				if(line_data[1]=='I')
				{
					//TODO: parse what InputMethod is
					const gchar tag_prefix[] = "<InputMethod \"";
					gint tag_idx=sizeof(tag_prefix)-1;
					if(0!=g_strncasecmp( tag_prefix, line_data, sizeof(tag_prefix)-1))
					{
						g_printf("line=%d, parse error\n", __LINE__ );
						is_valid=FALSE;
					}
					else
					{
						static gchar input_method_name[100]="";
						gint str_idx=0;
						//g_printf("parse InputMethod---");
						while(!(line_data[tag_idx]=='\"' || tag_idx==line_data_idx))
						{
							//g_printf("%c",line_data[tag_idx]);
							input_method_name[str_idx++] = line_data[tag_idx];
							tag_idx++;
						}
						//g_printf("---END\n");
						input_method_name[str_idx]='\0';
						g_utf8_strncpy(setting_on, input_method_name, -1 );
						//g_printf("\n\ninput_method_name of setting_on is %s\n\n", setting_on);
						g_hash_table_insert( me->ocht, g_strdup(setting_on), g_hash_table_new_full(g_str_hash, g_str_equal,g_free,g_free));


					}
				}
				else if(line_data[1]=='S')
				{
					//TODO: parse what SystemSetting is
					const gchar tag_prefix[] = "<SystemSetting>";
					//gint tag_idx=sizeof(tag_prefix)-1;
					if(0!=g_strncasecmp( tag_prefix, line_data, sizeof(tag_prefix)-1))
					{
						g_printf("line=%d, parse error\n", __LINE__ );
						is_valid=FALSE;
					}
					//g_printf("parse SystemSetting---");
					//g_printf("---END\n");
					//setting_on = ""
					g_utf8_strncpy(setting_on, "SystemSetting",-1 );
					g_hash_table_insert( me->ocht, g_strdup(setting_on), g_hash_table_new_full(g_str_hash, g_str_equal,g_free,g_free));


				}
				else if(line_data[1]=='/')
				{
					//TODO: End of Input Method
					const gchar im_tag[]="</InputMethod>";
					const gchar sysset_tag[] = "</SystemSetting>";
					if(0!=g_strncasecmp( im_tag, line_data, sizeof(im_tag)-1) && 0!=g_strncasecmp(sysset_tag, line_data, sizeof(sysset_tag)-1))
					{
						g_printf("line=%d, parse error\n", __LINE__ );
						is_valid=FALSE;
					}
					else
					{
						if(0!=g_strncasecmp( im_tag, line_data, sizeof(im_tag)-1))
						{
							//g_printf("parse EndSystemSetting---END\n");
						}
						else
						{
							//g_printf("parse EndInputMethod---END\n");
						}
						g_utf8_strncpy(setting_on, "", -1 );

					}
				}
				else
				{
					//Parse Error
					g_printf("line=%d, parse error\n", __LINE__ );
					is_valid=FALSE;
				}
			} //else if(line_data[0]=='<')
			else if(line_data_idx < 6)
			{
				//TODO: the line without any info , it maybe empty line in the text
			} //else if(line_data_idx < 6)
			else
			{
				gchar left_side_str[100];
				gchar right_side_str[100];
			
				//TODO: find the symbol '=' in the line , or the line is a parsing error
				gboolean parse_ok = FALSE;
				gint equ_symbol_idx=0;
				while(! ((line_data[equ_symbol_idx]=='=')||equ_symbol_idx==line_data_idx ))equ_symbol_idx++;
				if(equ_symbol_idx==line_data_idx) 
				{
					g_printf("line=%d, parse error\n", __LINE__ ); //error since there is no symbol '=' in the line
					is_valid=FALSE;
				}
				else
				{
					gint idx=0;
					gint idx_start=0;
					gint idx_end=0;
					gint str_idx=0;
					//g_printf left-side string
					
					for(idx=0;idx<equ_symbol_idx;idx++)
					{
						if(	
							(line_data[idx]>='a' && line_data[idx]<='z') ||
							(line_data[idx]>='A' && line_data[idx]<='Z') ||
							(line_data[idx]>='0' && line_data[idx]<='9') 
						) left_side_str[str_idx++]=line_data[idx];
					}
					left_side_str[str_idx]='\0';

					str_idx=0;
					//g_printf right-side string
					idx=equ_symbol_idx+1;
					while(! ((line_data[idx]=='\"')||idx==line_data_idx ))idx++;
					if(idx==line_data_idx)
					{
						str_idx=0;
						for(idx=equ_symbol_idx+1;idx<line_data_idx;idx++)
						{
							if(	
								(line_data[idx]>='a' && line_data[idx]<='z') ||
								(line_data[idx]>='A' && line_data[idx]<='Z') ||
								(line_data[idx]>='0' && line_data[idx]<='9') ||
								(line_data[idx]==' ' && line_data[idx]=='#')
							) right_side_str[str_idx++]=line_data[idx];
						}
						right_side_str[str_idx]='\0';
						parse_ok = TRUE;
						
					}
					else
					{	//first symbol " have been found in above
						idx_start=idx++; //idx_start denote first symbol "
						while(! ((line_data[idx]=='\"')||idx==line_data_idx ))idx++;
						if(idx==line_data_idx)
						{
							g_printf("line=%d, parse error\n", __LINE__ );
							is_valid=FALSE;
						}
						else
						{
							str_idx=0;
							idx_end=idx; //idx_end denote second symbol "
							for(idx=idx_start+1;idx<idx_end;idx++)	
								right_side_str[str_idx++]=line_data[idx];
							right_side_str[str_idx]='\0';
							parse_ok = TRUE;
						}
					}
				}
				if(parse_ok == TRUE)
				{
					//g_printf("leftside---%s--- and ",left_side_str);
					//g_printf("rightside---%s---\n", right_side_str);
					if(setting_on[0]!='\0')
						g_hash_table_insert( g_hash_table_lookup(me->ocht,setting_on), g_strdup(left_side_str), g_strdup(right_side_str));				
				}

			} //else
			//g_printf("%2d %s", line_idx++, line_data);
			line_data_idx=0;
		}
	} // for(idx=0; idx < me->content.eof_idx; idx++)
	return is_valid;

	
} // oxim_conf_parse()





gboolean oxim_conf_query_chi_name(const gchar* eng_name, gchar** ret_chi_name)
{



#if 0
	static gchar chewing_chi_name[] = "新酷音";
	static gchar unicode_chi_name[] = "萬國碼";
	static gchar cnsphone_chi_name[]= "中標注音";
	static gchar cnscj_chi_name[] = "中標倉頡";

	if(g_utf8_str_equal(eng_name,"chewing")) 
	{
		*ret_chi_name = g_strdup(chewing_chi_name);
		return TRUE;
	}
	if(g_utf8_str_equal(eng_name,"unicode"))
	{
		*ret_chi_name = g_strdup(unicode_chi_name);
		return TRUE;
	}
	if(g_utf8_str_equal(eng_name,"cnsphone")) 
	{
		*ret_chi_name= g_strdup(cnsphone_chi_name);
		return TRUE;
	}
	
	if(g_utf8_str_equal(eng_name,"cnscj"))
	{
		*ret_chi_name = g_strdup(cnscj_chi_name);
		return TRUE;
	}
#else
	const gchar* default_chi_name=NULL;
	default_chi_name = default_input_methods_get_chiname(eng_name);
	if(default_chi_name!=NULL)
	{
	  *ret_chi_name = g_strdup(default_chi_name);
	  return TRUE;
	}
	
#endif //#if 0

		//h=g_hash_table_new(g_str_hash, g_str_equal);
		//traveral all files 
	gchar filename[256]; // will denote .tab file
#if 0
	g_utf8_str_assign(filename,g_get_userhome_dir());
	g_utf8_str_append(filename,"/.oxim/tables/");
	g_utf8_str_append(filename, eng_name);
	g_utf8_str_append(filename,".tab");
	//g_printf("\nfilename = %s\n",filename);

	//static gchar ret_chi_name[255];
	//static gchar ret_eng_name[255];
	//gboolean is_valid= TRUE;
#else
	g_sprintf(filename, "%s/.oxim/tables/%s.tab",g_get_userhome_dir(), eng_name);
	if(! g_file_test(filename, G_FILE_TEST_EXISTS) )
	{
	  g_sprintf(filename, "%s/.oxim/tables/%s/%s.tab",g_get_usertmp_dir(), g_get_user_name(), eng_name);
	  if(! g_file_test(filename, G_FILE_TEST_EXISTS) )
	  {
	    return FALSE;
	  }
	}
	
	
#endif 

	gchar* ret_eng_name;
	
	if(FALSE==get_name(filename, ret_chi_name, &ret_eng_name))
	{
		return FALSE;
	}
	else
	{
#if 0		
		if(TRUE==g_utf8_str_equal(eng_name, ret_eng_name))
		{	
			g_free(ret_eng_name);
			return TRUE;
		}
		else
		{
			g_free(ret_eng_name);
			g_free(*ret_chi_name);
			return FALSE;
		}	
#else
		g_free(ret_eng_name);
		return TRUE;

#endif //#if0
	}
	
} //query_chi_name()

static gboolean get_name(gchar *filepath, gchar **ret_chi_name, gchar** ret_eng_name)
{
  return tab_info_get_name(filepath, ret_chi_name, ret_eng_name);
#if 0

/* General char type: mbs encoding
 *
 * Note: In Linux, if uch_t.s = "a1 a4", then uch_t.uch = 0xa4a1, i.e.,
 *       the order reversed. This might not be the general case for all
 *       plateforms.
 */
//Macro defined in oximtool.h
#ifndef UCH_SIZE
#define uchar_t long long
#define UCH_SIZE sizeof(uchar_t) 
typedef union { 
    unsigned char s[UCH_SIZE];
    uchar_t uch;
} uch_t;
#endif

//Marco defined in module.h
#define  N_KEYCODE              50      /* # of valid keys 0-9, a-z, .... */
/* Max allowed # of selection keys */
#define SELECT_KEY_LENGTH       15

//Macro defined in gencin.h
#define VERLEN			20	/* Version buffer size */
#define ENCLEN			15	/* Encoding name buffer size */
#define CIN_ENAME_LENGTH	20      /* English name buffer size */
#define CIN_CNAME_LENGTH	20      /* Chinese name buffer size */
#define N_NAME_LENGTH	256 /* 輸入法名稱最大長度 */
#define  END_KEY_LENGTH         10      /* max # of end keys */
#define N_KEYS 128	/* 可用按鍵 */


	typedef struct
	{
	    char prefix[7]; /* Always "gencin\0" */
	    unsigned char version;
	    char dummy[12];
	} table_prefix_t;

	typedef struct {
	    char version[VERLEN];		/* version number. */
	    char encoding[ENCLEN];		/* table encoding. */
	    char ename[CIN_ENAME_LENGTH];	/* English name. */
	    char cname[CIN_CNAME_LENGTH];	/* Chinese name. */

	    uch_t keyname[N_KEYCODE];		/* key name define. */
	    char selkey[SELECT_KEY_LENGTH + 1];	/* select keys. */
	    char endkey[END_KEY_LENGTH + 1];	/* end keys. */

	    union
	    {
		unsigned int n_ichar;		/* # of total chars. */
		unsigned int n_word;
	    };
	    unsigned int n_icode;		/* # of total keystroke code */
	    unsigned char n_keyname;		/* # of keyname needed. */
	    unsigned char n_selkey;		/* # of select keys. */
	    unsigned char n_endkey;		/* # of end keys. */
	    unsigned char n_max_keystroke;	/* max # of keystroke for each char */
	    char icode_mode;
	} cintab_head_t;
 
	typedef struct
	{
	    unsigned int n_locale;  /* 內含多少個國家地區名稱 */
	    unsigned int locale_table_offset;
	
	    unsigned int n_setting; /* 內含多少個設定輸入法設定 */
	    unsigned int setting_table_offset;
	
	    unsigned int n_input_content; /* 有多少個輸入內容 */
	    unsigned int offset_table_offset;

	    unsigned int n_char;	/* 有幾個字元(UCS4) */
	    unsigned int char_offset;

	    unsigned int input_content_offset;
	
	    unsigned char n_max_keystroke; /* 最長的字根數量 */
	    unsigned char keep_key_case; /* 保持按鍵大小寫 */
	
	    char orig_name[N_NAME_LENGTH]; /* English Name */
	    char cname[N_NAME_LENGTH]; /* 中文名稱(相容於舊式 cin 規格) */
	
	    unsigned char n_key_name; /* 幾個字根 */
	    uch_t keyname[N_KEYS]; /* 組字時, 顯示的字根 */

	    unsigned char n_selection_key; /* 幾個選擇鍵 */
	    char selection_keys[N_KEYS];  /* 選擇按鍵內容 */
	
	    unsigned char n_end_key; /* 幾個結束鍵 */
	    char end_keys[N_KEYS]; /* 結束鍵 */
	    unsigned int chksum;
	} cintab_head_v1_t;

#endif


#if 0
	//char ret_cname[100]; //original code's parameter in oxim_CheckTable
	//char ret_ename[100];
	int rv;
	int* ret_ver=&rv;


	static gchar chi_name[100];
	static gchar eng_name[100];


    gzFile *fp;
    gboolean valid = TRUE;

    /* 檔案完整路徑 */
    //sprintf(fullpath, "%s/%s", path, name);
    #define GENCIN_VERSION "20040102"
    /* 開檔 */

    if ((fp = gzopen((char*)filepath, "rb")) != NULL)
    {

	table_prefix_t tp;
    	cintab_head_t tab_hd;
	cintab_head_v1_t tab_v1_hd;
	int read_size, hd_size;
	int size = sizeof(table_prefix_t);

	if (gzread(fp , &tp, size) == size && strcmp(tp.prefix, "gencin") == 0)
	{
	    switch (tp.version)
	    {
		case 0:
		    hd_size = sizeof(cintab_head_t);
		    read_size = gzread(fp, &tab_hd, hd_size);
		    break;
		case 1:
		    hd_size = sizeof(cintab_head_v1_t);
		    read_size = gzread(fp, &tab_v1_hd, hd_size);
		    break;
		default:
		    valid =FALSE;
	    }

	    /* 檔頭 */
	    if (valid && read_size == hd_size)
	    {

		switch (tp.version)
		{
		    case 0:

			if (strcmp(GENCIN_VERSION, tab_hd.version) != 0)
			{
			    valid = FALSE;
			}
			else
			{
			    g_utf8_strncpy(chi_name, (gchar*)tab_hd.cname, -1);
			    g_utf8_strncpy(eng_name, (gchar*)tab_hd.ename, -1);
			    if (ret_ver)
			    {
				*ret_ver = 0;
			    }
			}
			break;
		    case 1:
			{

			    unsigned int checksum = crc32(0L,  (Bytef *)&tab_v1_hd, sizeof(cintab_head_v1_t) - sizeof(unsigned int));
			    if (checksum == tab_v1_hd.chksum)
			    {
#if 0
				g_utf8_strncpy(chi_name, (gchar*) realCname(tab_v1_hd.cname, tab_v1_hd.orig_name),-1);
				g_utf8_strncpy( eng_name, (gchar*)tab_v1_hd.orig_name, -1);
#else
				g_utf8_strncpy(chi_name, (gchar*) realCname(tab_v1_hd.cname, tab_v1_hd.orig_name),-1);
				g_utf8_strncpy( eng_name, (gchar*)tab_v1_hd.orig_name, -1);				
#endif 


				if (ret_ver)
				{
				    *ret_ver = 1;
				}
			    }
			    else
			    {
				valid = FALSE;
			    }
			}
			break;
		    default:
			valid = FALSE;
		}
	    }
	}
	else
	{
	    valid = FALSE;
	}
	gzclose(fp);
    }


    if(valid==TRUE)
    {
	gint idx=0;
	while(!(eng_name[idx]=='\0'))
	{
		if(eng_name[idx]<='Z' && eng_name[idx]>='A')
		{
			eng_name[idx] = eng_name[idx] + 'a' - 'A';
		}
		idx++;
	}
	*ret_eng_name = g_strdup(eng_name);
	*ret_chi_name = g_strdup(chi_name);

    }
#endif 
    //return valid;
}//get_name()

#if 0
static char *realCname(char *c_name, char *e_name)
{
	char delims[] = ";";
	char *result = NULL;
	char *loc = strdup(setlocale(LC_MESSAGES, NULL));
	
	/*檢查有沒有包含冒號，若沒有應該是舊的中文名稱*/
	if( NULL == strchr(c_name, delims[0]) )
	{
#if 0
		return 
			(strlen(loc)>3&&loc[0]=='z'&&loc[1]=='h'&&loc[2]=='_') ?
				c_name :  /*若locale開頭=『zh_』則傳回中文名稱*/
				e_name;	/*否則傳回英文名稱*/
#else
		return (!strncmp(loc, "zh_",3)) ? (c_name) : (e_name) ;
#endif 			
	}
	
	char *loc_comp[] = {'\0', '\0'};
	char *cname;
	char *ptr;
	/*將包含『.』以後的字串予以清除*/
	if( NULL != (ptr=strchr(loc, '.')) )
	{
		ptr[0] = '\0';
	}
	loc_comp[0] = strdup(loc);
	if( NULL != (ptr=strchr(loc, '_')) )	/*locale包含『_』才進行比對*/
	{
		ptr[0] = '\0';	/*清除包括『_』之後的字元*/
		loc_comp[1] = strdup(loc);
	}

	int i, j, k;
	char *tmp = NULL;
	char split[] = ":";
	char *saveptr1, *saveptr2;
	/*check for zh_TW、zh*/
	for( k=0; k<2; k++)
	{
		cname = strdup(c_name);
		for( i=0, result = strtok_r( cname, delims, &saveptr1 ); result != NULL; i++, result = strtok_r( NULL, delims, &saveptr1 ) )
		{
			char *data[2];
			for( j=0, tmp = strtok_r( result, split, &saveptr2 ); tmp!=NULL; j++, tmp = strtok_r( NULL, split, &saveptr2 ) )
			{
				data[j] = tmp;
			}
			if( ('\0' != loc_comp[k]) && (0 == strcmp(data[1], loc_comp[k])) )
			{
				return data[0];
			}
		}
	}
	return e_name;
} //realCname()
#else
#if 0
#define BUFFER_LEN (255)

char *realCname(char *c_name, char *e_name)
{
	char delims[] = ";";
	char *result = NULL;
	char loc[BUFFER_LEN];
	strcpy(loc, setlocale(LC_MESSAGES, NULL));

	/*檢查有沒有包含冒號，若沒有應該是舊的中文名稱*/
	if( NULL == strchr(e_name, delims[0]) )
	{
		return 
			0==strncmp(loc, "zh_", 3) ?
				c_name :  /*若locale開頭=『zh_』則傳回中文名稱*/
				e_name;	/*否則傳回英文名稱*/
	}
	
	char loc_comp[][BUFFER_LEN] = {'\0', '\0',  '\0'};
	char ename[BUFFER_LEN];
	char *ptr;
	/*將包含『.』以後的字串予以清除*/
	if( NULL != (ptr=strchr(loc, '.')) )
	{
		ptr[0] = '\0';
	}
	strcpy(loc_comp[0], loc);
	if( NULL != (ptr=strchr(loc, '_')) )	/*locale包含『_』才進行比對*/
	{
		ptr[0] = '\0';	/*清除包括『_』之後的字元*/
		strcpy(loc_comp[1], loc);
	}
	strcpy(loc_comp[2], "en");

	int i, j, k;
	char *tmp = NULL;
	char split[] = ":";
	char *saveptr1, *saveptr2;
	/*check for zh_TW、zh*/
	for( k=0; k<3; k++)
	{
		strcpy(ename, e_name);
		for( i=0, result = strtok_r( ename, delims, &saveptr1 ); result != NULL; i++, result = strtok_r( NULL, delims, &saveptr1 ) )
		{
			char *data[2];
			for( j=0, tmp = strtok_r( result, split, &saveptr2 ); tmp!=NULL; j++, tmp = strtok_r( NULL, split, &saveptr2 ) )
			{
				data[j] = tmp;
			}
			if( 0 == strcmp(data[1], loc_comp[k]) )
			{
				return data[0];
			}
		}
	}
	return c_name;
} //realCname
#endif 
#endif 



