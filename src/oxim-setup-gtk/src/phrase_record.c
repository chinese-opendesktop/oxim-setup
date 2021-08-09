
#include "oxim_setup_gtk_global.h"
#include "phrase_record.h"

static phrases_t* phrases_tmp=NULL;
static gint phrases_tmp_size = 0;
static gboolean phrase_parse(gint *pste, gchar token);
static const gchar symbol_key_table[] = "1234567890abcdefghijklmnopqrstuvwxyz`-=[];',./\\";



void phrase_reload( phrases_t* ret_phrases ,gint* ret_size)
{
	static phrases_t default_phrase_strlist = 
	{
	  {"1",""},{"2",""},{"3",""},{"4",""},{"5",""},{"6",""},{"7",""},{"8",""},{"9",""},{"0",""},
	  {"a","├"},{"b","股份有限公司"},{"c","┘"},{"d","┤"},{"e","┐"},{"f","『"},{"g","』"},{"h","「"},
	  {"i","、"},{"j","」"},{"k","§"},{"l","│"},{"m","─"},{"n","有限公司"},{"o","。"},{"p","﹖"},{"q","┌"},
	  {"r","□"},{"s","┼"},{"t","台北市"},{"u","±"},{"v","ˇ"},{"w","┬"},{"x","┴"},{"y","臺灣省"},{"z","└"},
	  {"`",""},{"-",""},{"=",""},{"[",""},{"]",""},{";","；"},{"'","："},{",","，"},{".","．"},{"/","？"},{"\\",""}
	};

	gint default_phrase_strlist_size = 47;
	//gchar* default_phrase_strlist_size = 47;
	gint idx=0;
	for(idx=0;idx<default_phrase_strlist_size;idx++)
	{
	  (*ret_phrases)[idx][0] = default_phrase_strlist[idx][0];
	  (*ret_phrases)[idx][1] = g_strdup(default_phrase_strlist[idx][1]);
	}
	*ret_size=47;
	
	gchar* fp = g_strdup_printf("%s/.oxim/tables/default.phr",g_get_userhome_dir());
	if(!g_file_test(fp, G_FILE_TEST_EXISTS))
	{
	  g_printf("(%s:%d)[%s()] %s is not exist", __FILE__, __LINE__, __func__,fp);
	  g_free(fp);
	  
	  fp=g_strdup_printf("%s/oxim/tables/default.phr", g_get_usrlib_dir());
	  if(!g_file_test(fp, G_FILE_TEST_EXISTS))
	  {	
	    g_printf("(%s:%d)[%s()] %s is not exist", __FILE__, __LINE__, __func__,fp);
	    g_free(fp);
	    return;
	  }
	}




	GIOChannel* read;
	gchar *content;
	gsize bytes;
	GError* error = NULL;
	read = g_io_channel_new_file(fp, "r", &error);
	g_free(fp);
	if(error!=NULL)
	{
	  g_printf("(%s:%d)[%s(filename=%s)] g_io_channel_new_file's error msg is[%s]\n",__FILE__, __LINE__, __func__,  fp ,error->message);
	  g_clear_error(&error);
	}
	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	g_io_channel_read_to_end(read, &content, &bytes, NULL);

#if 1
	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	g_io_channel_close(read);
	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	idx=0;
	gint pste=0;
	phrases_tmp = ret_phrases;   //set for parsor
	phrases_tmp_size = *ret_size;//set for parsor
	for(idx=0;idx<bytes;idx++)
	{
	  gchar token = content[idx];
	  if(!phrase_parse(&pste, token))
	  {
	    
	  }
	  else
	  {
	    
	  }
	}
	g_free(content);
#endif 

} //phrase_reload()

static gboolean phrase_parse(gint *pste, gchar token)
{
	
  static gchar safe_str[255];
  static gint safe_str_idx=0;
  static gchar head_str[255]="\0\0\0";
  #define _CLRS()do{ 		\
	safe_str[0]='\0';	\
	safe_str_idx=0;		\
	head_str[0]='\0';	\
  }while(0)


  #define _ERRO() do{\
	g_printf("(%s:%d)[%s(*pste=%d,token=%c)] Error \n", __FILE__, __LINE__, __func__, *pste, token);\
	*pste=-1;\
	return FALSE;\
  }while(0)

  #define _ADDC(e) do{			\
	safe_str[safe_str_idx++]=(e);	\
	safe_str[safe_str_idx]='\0';	\
	if(safe_str_idx>250)		\
	{				\
		_CLRS();		\
		_ERRO();		\
	}				\
  }while(0)

  #define _NEXT()do{\
	(*pste)=(*pste)+1;\
  }while(0)

  #define _JUMP(s)do{\
	*pste = (s);\
  }while(0)

  #define _ADDHEAD(e) do{\
	head_str[0]=(e); \
	head_str[1]='\0';\
  }while(0)

  #define _APPEND_RECORD() do{\
	g_printf("Phrase Add Record (\"%s:%s\")\n", head_str, safe_str);\
	gint idx=0;							\
	for(idx=0;idx<phrases_tmp_size;idx++)				\
	{								\
	  if(g_utf8_str_equal(head_str,((*phrases_tmp)[idx][0])))	\
	  {								\
	    g_free((*phrases_tmp)[idx][1]);				\
	    (*phrases_tmp)[idx][1]=g_strdup(safe_str);			\
	  }								\
	}								\
  }while(0)

  switch(*pste)
  {
  case -1:

  break;
  case 0:
    switch(token)
    {
    case ' ':
    case '\t':
    case '\n':
    break;
    default:
      if(1)
      {
	gint idx=0;
	while(!( (symbol_key_table[idx]=='\0')||(symbol_key_table[idx]==token) ))idx++;
	if(symbol_key_table[idx]=='\0')
	{
		_ERRO();
	}
	else
	{
		_ADDHEAD(symbol_key_table[idx]);
		_NEXT();
	}
      }
    break;
    }//switch(token)
  break; //case 0
  case 1:
    switch(token)
    {
    case ' ':
    case '\t':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break; //case 1
  case 2:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case '\"':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    } //switch(token)
  break; //case 2
  case 3:
    switch(token)
    {
    case '\n':
	_ERRO();	
    break;
    case '\"':
	//TODO: add one record of data s.t. 
	_APPEND_RECORD();
	_CLRS();
	_NEXT();
    break;
    default:
	_ADDC(token);
    break;
    } //switch(token)
  break; //case 3
  case 4:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case '\n':
	_JUMP(0);
    break;

    default:
	//_ERRO();
	//Don't _ERRO , since somebody will key-in double-quaotion
    break;
    } //switch(token)
  break; //case 4
  } //switch (*pste)
 
#undef _CLRS
#undef _ERRO
#undef _ADDC
#undef _NEXT
#undef _JUMP
#undef _APPEND_RECORD
#undef _ADDHEAD
  return TRUE;
} //phrase_parse()


void phrase_update( phrases_t phrases, gint size)
{
  //symbol_key_table[] = "1234567890abcdefghijklmnopqrstuvwxyz`-=[];',./\\";
  static gchar str[65536]="";
  str[0]='\0';
  gint idx=0;
  gint key_idx=0;
  for(key_idx=0; key_idx< (sizeof(symbol_key_table)/sizeof(gchar))-1; key_idx++)
  {
    static gchar key[] ="\0\0";
    key[0]=symbol_key_table[key_idx];

    if(g_utf8_str_equal(phrases[idx][0], key) && idx < size)
    {
	gchar* appendstr = g_strdup_printf("%s \"%s\"\n", phrases[idx][0], phrases[idx][1]);
	g_utf8_str_append(str, appendstr);
	g_free(appendstr);
	idx++;
    }
    else
    {
	gchar* appendstr = g_strdup_printf("%s \"\"\n", key);
	g_utf8_str_append(str, appendstr);
	g_free(appendstr);
    }
  } //for(key_idx=0; key_idx< (sizeof(symbol_key_table)/sizeof(gchar)); key_idx++)
  g_printf("show out printing ...\n%s\n...ending show out\n",str);

  GIOChannel *write;
  GError *error = NULL;
  gsize bytes;
  gchar* fp = g_strdup_printf("%s/.oxim/tables/default.phr",g_get_userhome_dir());
  write=g_io_channel_new_file(fp, "w", &error);
  if(error != NULL)
  {
    g_printf("(%s:%d)[%s(filename=%s)] g_io_channel_new_file's error msg is[%s]\n",__FILE__, __LINE__, __func__,  fp ,error->message);
    g_clear_error(&error);
  }
  g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
  g_io_channel_write_chars(write, str, -1, &bytes, NULL);
  g_io_channel_close(write);

  str[0]='\0';
} //phrase_update()


