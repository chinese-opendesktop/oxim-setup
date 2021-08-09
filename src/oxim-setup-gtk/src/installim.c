#include "oxim_setup_gtk_global.h"
#include "installim.h"
#include "installim_gui_embassador.h"
#include "installim_core_embassador.h"
#include <locale.h>
static installim_dialog_data_t dialog_data;
static gboolean install_from_internet_now = FALSE;
static gboolean is_external_url = FALSE;
GtkDialog* dialog_me;
static GtkEntry* Filename_Entry;


gint signal_handler_event(GtkWidget *widget, GdkEventButton *event, gpointer func_data);
void install_notebook_switch_page_cb(GtkWidget* me);
void update_preview_cb (GtkFileChooser *file_chooser, gpointer data);
void fixed_toggled2 ( GtkCellRendererToggle *cell, gchar *path_str, gpointer data);
void toggle_cell_data_func(GtkTreeViewColumn* column, GtkCellRenderer* renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
void name_cell_data_func(GtkTreeViewColumn* column, GtkCellRenderer* renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
void description_cell_data_func(GtkTreeViewColumn* column, GtkCellRenderer* renderer, GtkTreeModel* model, GtkTreeIter* iter, gpointer data);
static gboolean connect_status_open_just=FALSE;
static gboolean ftp_is_connecting_on = FALSE;
void connect_button_enter_cb(GtkWidget* me);
void connect_button_leave_cb(GtkWidget* me);
void connect_button_pressed_cb(GtkWidget* me);
void installim_dialog_accept_button_pressed_cb(GtkWidget* me);
const gchar* im_downloadable(GtkTreeModel* model, GtkTreeIter* iter);

static gchar ftp_baseurl[256]="";

static GtkTreeStore* tree_store;
static GtkListStore* list_store;
static GtkTreeView *treeview;

void connect_button_clicked(GtkWidget* me, gpointer data);
void installim_treeview_build_mirrors_site(void);
void installim_treeview_build_cin_list(gint level);

static void connect_status(const gchar *fmt, ...);
static void connect_status(const gchar *fmt, ...)
{
	static GtkLabel* label;
	
	if(connect_status_open_just==TRUE)
	{	
//		label = GTK_LABEL(glade_xml_get_widget(dialog_data.header.xml,"connect_status"));
		label = GTK_LABEL( GTK_WIDGET( gtk_builder_get_object(dialog_data.header.builder, "connect_status") ) );
		connect_status_open_just=FALSE;
	}
	char s[2048] = ""; 
	va_list ap; 
	va_start(ap, fmt); 
	vsprintf(s, fmt, ap);
	va_end(ap); 
	if(label!=NULL)gtk_label_set_text(label,s);
}
gboolean mirrors_site_parse2(gint *pste, gchar token);
gboolean cin_list_parse(gint *pste, gchar token);
static void internal_sensitive_filter(void);
static void internal_copy_data(installim_dialog_data_t* from, installim_dialog_data_t* to);
static void internal_sensitive_filter(void)
{

} //internal_sensitive_filter()

static void internal_copy_data(installim_dialog_data_t* from, installim_dialog_data_t* to)
{
	to->header.is_dialog_press_accept = from->header.is_dialog_press_accept;
//	to->header.xml = from->header.xml;
	to->header.builder = from->header.builder;
	g_strlcpy(to->filename, from->filename, 1024);

} //internal_copy_data()

void installim_dialog_ctor(GtkWidget* me, gpointer data)
{
	printf("[Func %s() is invoked]\n",__func__);

	if(NULL==g_getenv("EXTERNAL_DOWNLOAD_URL"))
	{
	  is_external_url=FALSE;
	}
	else
	{
	  if( g_utf8_str_equal( g_getenv("EXTERNAL_DOWNLOAD_URL"),""))
	  {
	    is_external_url = FALSE;
	  }
	  else
	  {
	    is_external_url = TRUE;
	  }
	}

	connect_status_open_just=TRUE;
	ftp_is_connecting_on = FALSE;
	install_from_internet_now=FALSE;
	internal_copy_data((installim_dialog_data_t*)data, &(dialog_data));
	dialog_me = GTK_DIALOG(me);
//	GladeXML *xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;
	//TODO: GUIvar = glade_xml_get_widget(xml,"adsf");
//	Filename_Entry = GTK_ENTRY(glade_xml_get_widget(xml,"installim_dialog_filename_entry"));
	Filename_Entry = GTK_ENTRY( GTK_WIDGET( gtk_builder_get_object(builder, "installim_dialog_filename_entry") ) );
	//TODO: gtk_GUIvar_set_xxx(GUIvar, blabla)
	gtk_entry_set_text(Filename_Entry, dialog_data.filename);

	internal_sensitive_filter();
	dialog_data.header.is_dialog_press_accept = FALSE;

} //installim_dialog_ctor()



void installim_dialog_dtor(GtkObject* me, gpointer data)
{
	printf("AAAAAAAAAAAA[Func %s() is invoked]\n",__func__);
	//TODO: dialog_data.somefield <- GUIvar.field
	static const gchar* filename;
	filename = gtk_entry_get_text(Filename_Entry);
	g_strlcpy(dialog_data.filename, filename, -1);

	if(dialog_data.header.is_dialog_press_accept == TRUE)
		internal_copy_data( &(dialog_data),(installim_dialog_data_t*)data);
} //installim_dialog_dtor()

void installim_dialog_accept(GtkButton* accept_button)
{
	printf("[Func %s() is invoked]\n",__func__);
	dialog_data.header.is_dialog_press_accept = TRUE;
//	GladeXML* xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;
	gboolean connect_button_is_sensitive; //connect button is sensitive when the installim_dialog has in im choosen download mode.
//	g_object_get(G_OBJECT(glade_xml_get_widget(xml,"connect_button")), "sensitive",&connect_button_is_sensitive, NULL );
	g_object_get(G_OBJECT( GTK_WIDGET( gtk_builder_get_object(builder, "connect_button") ) ), "sensitive",&connect_button_is_sensitive, NULL );

	if(!connect_button_is_sensitive)
	{
		
		im_core_tab_pool_clear();
		
		//download all choiced xxx.cin.gz from ftp into /tmp/xxx.cin.gz. And then, translate all of these into /tmp/.oxim/tables/xxx.tab by oxim2tab cmd
		GtkTreeModel* model = GTK_TREE_MODEL(tree_store);
		GtkTreeIter parent_iter;
		GtkTreeIter iter;
		if(gtk_tree_model_get_iter_first(model,&parent_iter))
		{
		  do
		  {
			if(gtk_tree_model_iter_children(model, &iter, &parent_iter ))
			{
			  do
			  {
				const gchar* download_filename=NULL;
				download_filename =im_downloadable(model,&iter);
				if(download_filename != NULL)
				{
					static gchar download_url[256];
					static gchar download_filepath[256];
	
					g_sprintf(download_url,"%s/%s", ftp_baseurl, download_filename);
					g_sprintf(download_filepath, "%s%s", im_core_get_download_dir(), download_filename);
					g_printf("download ==== %s\n",download_url);
					
					if(im_core_ftp_download(download_url, download_filepath,10))
					{
	
						//TODO: translate .cin.gz into .tab in tmp dir
						static gchar im_name[100];
						g_utf8_str_assign(im_name, download_filename);
						gint len=0;
						while(im_name[len]!='\0')len++;
						im_name[len-7]='\0';
						im_core_tab_pool_add_im(im_name, download_filepath);
					}
				}
			  }while(gtk_tree_model_iter_next(model,&iter));
			}// if(gtk_tree_model_iter_children(model, &iter, &parent_iter ))
		  }while(gtk_tree_model_iter_next(model,&parent_iter));
		} //if(gtk_tree_model_get_iter_first(model,&parent_iter))
		if(1) //copy all of xxx.tab from /tmp/.oxim/tables into $HOME/.oxim/tables/ and then update oxim.conf according to files in ~/.oxim/tables/
		{
		
		} //if(1)
	}
	else
	{
//		GladeXML* xml = dialog_data.header.xml;
		GtkBuilder *builder = dialog_data.header.builder;
		GtkEntry* filename_entry;
//		filename_entry = GTK_ENTRY(glade_xml_get_widget(xml,"installim_dialog_filename_entry"));
		filename_entry = GTK_ENTRY( GTK_WIDGET( gtk_builder_get_object(builder, "installim_dialog_filename_entry") ) );
		if(gtk_entry_get_text(filename_entry)!=NULL)
		{
		  im_core_tab_pool_clear();
		  gchar* fp = g_strdup(gtk_entry_get_text(filename_entry));
		  if( g_file_test(fp, G_FILE_TEST_EXISTS) )
		  {
			gchar* im_name = g_path_get_basename(fp);
			
			if(im_name!=NULL)
			{
	 		  gint len=0;
			  while(im_name[len]!='.')len++;
			  im_name[len]='\0';

			  im_core_tab_pool_add_im(im_name, fp);
			  g_free(im_name);
			}

		  }
		  g_free(fp);
		}
		
		
	}
	gtk_widget_hide_all(GTK_WIDGET(dialog_me));
//	gtk_dialog_response(dialog_me,0);

} //installim_dialog_accept()

void installim_dialog_reject(GtkButton* reject_button)
{
	printf("[Func %s() is invoked]\n",__func__);
	gtk_widget_hide_all(GTK_WIDGET(dialog_me));
//	gtk_dialog_response(dialog_me,0);
} //installim_dialog_reject()

void installim_dialog_browser_button_clicked( GtkEntry* filename_entry,  GtkButton* button)
{


	GtkImage *preview; //plus
	preview = GTK_IMAGE(gtk_image_new ());//plus

	GtkWidget *dialog;
	GtkWidget *window;
	gchar *filename;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	

	dialog = gtk_file_chooser_dialog_new(_("Please choose"), GTK_WINDOW(window),
	GTK_FILE_CHOOSER_ACTION_OPEN,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
	NULL);

	//milochen add
	GtkFileFilter *filter = NULL;
	filter = gtk_file_filter_new();
	//gtk_file_filter_set_name(filter,"標準輸入法參考檔(*.cin *.cin.gz *.tab)");

	gtk_file_filter_set_name(filter,_("Standard Input Method Ref. File (*.cin *.cin.gz *.tab)"));
	gtk_file_filter_add_pattern(filter,"*.tab");
	gtk_file_filter_add_pattern(filter,"*.cin.gz");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog),filter);

	filter = gtk_file_filter_new();
	//gtk_file_filter_set_name(filter,"SCIM 輸入法參考檔(*.txt.in)");
	gtk_file_filter_set_name(filter,_("SCIM Input Method Ref. File(*.txt.in)"));
	gtk_file_filter_add_pattern(filter,"*.txt.in");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog),filter);


	gtk_file_chooser_set_preview_widget (GTK_FILE_CHOOSER(dialog), (GtkWidget*)preview); //plus


	g_signal_connect (dialog, "update-preview",
	G_CALLBACK (update_preview_cb), preview); //plus

	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if(result == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
		gtk_entry_set_text(filename_entry, filename);
	}


//g_strlcpy(dialog_data.filename, filename, -1);

//milochen plus





	gtk_widget_destroy(dialog);
} //installim_dialog_browser_button_clicked()



void update_preview_cb (GtkFileChooser *file_chooser, gpointer data)
{
  GtkWidget *preview;
  char *filename;
  GdkPixbuf *pixbuf;
  gboolean have_preview;

  preview = GTK_WIDGET (data);
  filename = gtk_file_chooser_get_preview_filename (file_chooser);

  pixbuf = gdk_pixbuf_new_from_file_at_size (filename, 256, 256, NULL);
  have_preview = (pixbuf != NULL);
  g_free (filename);

  gtk_image_set_from_pixbuf (GTK_IMAGE (preview), pixbuf);
  if (pixbuf)
    g_object_unref (pixbuf);

  gtk_file_chooser_set_preview_widget_active (file_chooser, have_preview);
}


gboolean mirrors_site_parse2(gint *pste, gchar token)
{
	//return FALSE if Halting, check pste to know whether pste (parse state) is succeed or fail
  static gchar safe_str[255];
  static gint safe_str_idx=0;
  static GtkTreeIter iter;
  #define _CLRS()do{ 		\
	safe_str[0]='\0';	\
	safe_str_idx=0;		\
  }while(0)


  #define _MOVE(tmp)do{ \
	g_utf8_str_assign((tmp), safe_str);\
	_CLRS();\
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


  #define _STORE_CHI_HOST_POS(arg_str) do{\
	g_printf("ChiHostPos=%s\t",(arg_str));\
	gtk_list_store_append(list_store, &iter);\
	gtk_list_store_set(list_store, &iter, 0,arg_str,-1);\
  }while(0)
  
  #define _STORE_HOST_NAME(arg_str) do{\
	g_printf("HostName=%s\n",(arg_str));\
	gtk_list_store_set(list_store, &iter, 1, arg_str,-1);\
  }while(0)

  switch (*pste)
  {
  case -1:
    //pste is fail...
  break;
  case 0:
    _CLRS();
    switch(token)
    {
    case ' ':
    case '\t':
    case '\n':
    break;  
    case '\"':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break;//case *pste==0

  case 1:
    switch(token)
    {
    case '\"':
	if(1)
	{
	  static gchar str[100];
	  _MOVE(str);
	  _STORE_CHI_HOST_POS(str);
	  _NEXT();
	}
    break;
    case '\n':
	_ERRO();
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;//case *pste==1
  case 2:
    switch(token)
    {
    case '=':
	_NEXT();
    break;
    case '\t':
    case ' ':
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break;//case *pste==2
  case 3:
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
    }//switch(token)
  break;//case *pste==3

  case 4:
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
	if(1)
	{
	  static gchar tmp[100];
	  _MOVE(tmp);
	  _STORE_HOST_NAME(tmp);
	  _NEXT();
	}
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;//case *pste==4
  case 5:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case '\n':
	_JUMP(0);
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break;//case *pste==5
  default:
    _ERRO();
  break;
  } //switch(*oste)



  #undef _CLRS
  #undef _MOVE
  #undef _ADDC
  #undef _NEXT
  #undef _JUMP
  #undef _ERRO
  #undef _STORE_CHI_HOST_POS
  #undef _STORE_HOST_NAME

  return TRUE;
} //mirrors_site_parse2()






gboolean cin_list_parse(gint *pste, gchar token)
{
	//return FALSE if Halting, check pste to know whether pste (parse state) is succeed or fail
  static gchar safe_str[255];
  static gint safe_str_idx=0;
  static GtkTreeIter iter;
  static GtkTreeIter parent_iter;

  #define _CLRS()do{ 		\
	safe_str[0]='\0';	\
	safe_str_idx=0;		\
  }while(0)


  #define _MOVE(tmp)do{ \
	g_utf8_str_assign((tmp), safe_str);\
	_CLRS();\
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

#if 0
  #define _STORE_LANG(arg_str) do{\
	g_printf("Lang=%s\n",(arg_str));\
	gtk_tree_store_append(tree_store, &parent_iter,NULL);\
	gtk_tree_store_set(tree_store, &parent_iter, 0,TRUE,1,TRUE, 3,(arg_str), -1);\
  }while(0)
  #define _STORE_1ST_COL(arg_str) do{\
	g_printf("1st Col=%s\t",(arg_str));\
	gtk_tree_store_append(tree_store, &iter , &parent_iter);\
	gboolean exist = im_core_im_has_exist((arg_str));\
	gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,!exist, 2,exist, 4,(arg_str), -1);\
  }while(0)
  
  #define _STORE_2ND_COL(arg_str) do{\
	g_printf("2nd Col=%s\t",(arg_str));\
	gtk_tree_store_set(tree_store, &iter, 5,(arg_str), -1);\
  }while(0)
#else

  #define _STORE_LANG(arg_str) do{\
	g_printf("Lang=%s\n",(arg_str));\
	gtk_tree_store_append(tree_store, &parent_iter,NULL);\
	gint idx=0; while(!(arg_str[idx]=='\0'||arg_str[idx]==','))idx++;\
	gtk_tree_store_set(tree_store, &parent_iter, 0,TRUE,1,TRUE, -1);\
	if(arg_str[idx]=='\0')\
	{\
	  gtk_tree_store_set(tree_store, &parent_iter,  3,(arg_str), -1);\
	  gtk_tree_store_set(tree_store, &parent_iter,  4,(arg_str), -1);\
	}\
	else\
	{\
	  arg_str[idx]='\0';\
	  gtk_tree_store_set(tree_store, &parent_iter,  3,(&arg_str[0]), -1);\
	  gtk_tree_store_set(tree_store, &parent_iter,  4,(&arg_str[idx+1]), -1);\
	  arg_str[idx]=',';\
	}\
  }while(0)

  #define _STORE_LANG_ENG(arg_str) do{\
	g_printf("LangEng=%s\n",(arg_str));\
	/*gtk_tree_store_append(tree_store, &parent_iter,NULL);*/\
	gtk_tree_store_set(tree_store, &parent_iter,  4,(arg_str), -1);\
  }while(0)

  //_STORE_1ST_COL is present the filename of cin.gz
  #define _STORE_1ST_COL(arg_str) do{\
	g_printf("1st Col=%s\t",(arg_str));\
	gtk_tree_store_append(tree_store, &iter , &parent_iter);\
	gboolean exist = im_core_im_has_exist((arg_str));\
	gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,!exist, 2,exist, 5,(arg_str), -1);\
  }while(0)
  

  //_STORE_2ND_COL is present the data of chinese input method name
  #define _STORE_2ND_COL(arg_str) do{\
	g_printf("2nd Col=%s\t",(arg_str));\
	gint idx=0; while(!(arg_str[idx]=='\0' || arg_str[idx]==';'))idx++; \
	gtk_tree_store_set(tree_store, &iter, 6,(arg_str), -1);\
	gtk_tree_store_set(tree_store, &iter, 8,(arg_str), -1);\
  }while(0)

  //_STORE_3RD_COL is present the data of chinese description 
  #define _STORE_3RD_COL(arg_str) do{\
	g_printf("3rd Col=%s\n",(arg_str));\
	gint idx=0; while(!(arg_str[idx]=='\0' || arg_str[idx]==';'))idx++; \
	if(arg_str[idx]=='\0')\
	{\
	  gtk_tree_store_set(tree_store, &iter, 7,(arg_str), -1);\
	  gtk_tree_store_set(tree_store, &iter, 9,(arg_str), -1);\
	}\
	else\
	{\
	  arg_str[idx]='\0';\
	  gtk_tree_store_set(tree_store, &iter, 7,&(arg_str[0]), -1);\
	  gtk_tree_store_set(tree_store, &iter, 9,&(arg_str[idx+1]), -1);\
	  arg_str[idx]=';';\
	}\
  }while(0)

  //_STORE_4TH_COL is present the data of english input method name
  #define _STORE_4TH_COL(arg_str) do{\
	g_printf("4th Col=%s\n",(arg_str));\
	gtk_tree_store_set(tree_store, &iter, 8,(arg_str), -1);\
  }while(0)
  
  //_STORE_5TH_COL is present the data of english description
  #define _STORE_5TH_COL(arg_str) do{\
	g_printf("5th Col=%s\n",(arg_str));\
	gtk_tree_store_set(tree_store, &iter, 9,(arg_str), -1);\
  }while(0)
#endif 

  #define _IS_FIRST_LETTER(e) (		\
	   (((e)>='a') && ((e)<='z'))	\
	|| (((e)>='A') && ((e)<='Z'))	\
	|| (((e)>='0') && ((e)<='9'))	\
	|| ((e)=='_')			\
	|| ((e)=='.')			\
	|| ((e)=='-')			\
  )
  
  #define _IS_LETTERS(e) (		\
	   (((e)>='a') && ((e)<='z'))	\
	|| (((e)>='A') && ((e)<='Z'))	\
	|| (((e)>='0') && ((e)<='9'))	\
	|| ((e)=='_')			\
	|| ((e)=='.')			\
	|| ((e)=='-')			\
  )
 
  switch(*pste)
  {
  case -1:
  break;//case *pste==-1
  case 0:
    switch(token)
    {
    case ' ':
    case '\t':
    case '\n':
    break;
    case 'L':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break;//case *pste==0

  case 1:
    if(1)
    {
    static const gchar Lang[]="Language\0";
    static gint Lang_idx=1;
    static gboolean need_init=TRUE;
    switch(token)
    {
    case '\t':
    case ' ':
	Lang_idx=1;
	need_init=TRUE;	
	if(Lang[Lang_idx]=='\0')
		_NEXT();
	else
	{
	//	_ERRO();
	}
    break;
    case '=':
	Lang_idx=1;
	need_init=TRUE;	
	_JUMP(3);
    break;
    default:
	if(Lang[Lang_idx] != '\0' && Lang[Lang_idx]==token)
	{
	  Lang_idx++;
	}
	else
	{
	  Lang_idx=1;
	  need_init=TRUE;	
	  _ERRO();
	}
    break;
    }//switch(token)
    }//if(1)
  break;//case *pste==1

  case 2:
    switch(token)
    {
    case '\t':
    case ' ':
    break;
    case '=':
	_NEXT();
    break;
    default:
	_ERRO();
    break;    
    } //switch(token)
  break;//case *pste==2

  case 3:
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
  break;//case *pste==3

  case 4:
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
      if(1)
      {
	static gchar s[100];
	_MOVE(s);
	_STORE_LANG(s);
	_NEXT();
      }//if(1)
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;//case *pste==4

  case 5:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case '\n':
	_NEXT();
    break;
    case ',':
	_JUMP(21);
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break;//case *pste==5

  case 6:
    switch(token)
    {
    case '\n':
    case '\t':
    case ' ':
    break;
    default:
        if(_IS_FIRST_LETTER(token))
	{
	  _ADDC(token);
	  _NEXT();
	}
	else
	{
	  _ERRO();
	}
    break;
    }//switch(token)
  break;//case *pste==6

  case 7:
    switch(token)
    {
    case '\t':
    case ' ':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	if(g_utf8_str_equal(s,"Language"))
	{
	  _JUMP(2);
	}
	else
	{
	   _STORE_1ST_COL(s);
	   _NEXT();
	}
      }//if(1)
    break;
    case '=':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	if(g_utf8_str_equal(s,"Language"))
	{
	  _JUMP(3);
	}
	else
	{
	  _ERRO();
	}
      }//if(1)
    break;
    case ',':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	_STORE_1ST_COL(s);
	_JUMP(9);
      }
    break;
    default:
	if(_IS_LETTERS(token))
	{
	  _ADDC(token);
	}
	else
	{
	  //_ERRO();
	}
    break;
    }//switch(token)
  break;//case *pste==7

  case 8:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case ',':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    }//switch(token)
  break;//case *pste==8

  case 9:
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
    }//switch(token)
  break;//case *pste==9

  case 10:
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	_STORE_2ND_COL(s);
	_NEXT();
      }
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;//case *pste==10
  case 11:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case ',':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    } //switch(token)
  break;//case *pste==11

  case 12:
    switch(token)
    {
    case '\t':
    case ' ':
    break;
    case '\"':
	_NEXT();
    break;
    case '\n':
	_ERRO();
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;//case *pste==12

  case 13:
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	_STORE_3RD_COL(s);
	_NEXT();
      }
    break;
    default:
	_ADDC(token);
    break;
    } //switch(token);
  break;//case *pste==13

  case 14:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case ',':
	_NEXT();
    break;
    case '\n':
	_JUMP(7);
    break;
    default:
	_ERRO();
    break;
    } //switch(token)
  break;
  case 15:
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
    }// switch(token)
  break; 

  case 16:
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	_STORE_4TH_COL(s);
	_NEXT();
      }
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;

  case 17:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case ',':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    } //switch(token)
  break;

  case 18:
    switch(token)
    {
    case '\t':
    case ' ':
    break;
    case '\"':
	_NEXT();
    break;
#if 0
    case '\n':
	_ERRO();
    break;
    default:
	_ADDC(token);
    break;
#else
    default:
	_ERRO();
    break;
#endif 
    }//switch(token)
  break; 

  case 19: 
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
      if(1)
      {
	static gchar s[256];
	_MOVE(s);
	_STORE_5TH_COL(s);
	_NEXT();
      }
    break;
    default:
	_ADDC(token);
    break;
    } //switch(token);
  break;

  case 20:
    switch(token)
    {
    case ' ':
    case '\t':
    break;
    case '\n':
	_JUMP(7);
    break;
    case ',':
	_NEXT();
    break;
    default:
	_ERRO();
    break;
    } //switch(token)
  break;//case *pste==14


  case 21:
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
  break;//case *pste==3

  case 22:
    switch(token)
    {
    case '\n':
	_ERRO();
    break;
    case '\"':
      if(1)
      {
	static gchar s[100];
	_MOVE(s);
	_STORE_LANG_ENG(s);
	//_NEXT();
	_JUMP(5);
      }//if(1)
    break;
    default:
	_ADDC(token);
    break;
    }//switch(token)
  break;//case *pste==4


  default:
    _ERRO();
  break;

  } //switch(*pste)

  #undef _CLRS
  #undef _MOVE
  #undef _ADDC
  #undef _NEXT
  #undef _JUMP
  #undef _ERRO
  #undef _STORE_1ST_COL
  #undef _STORE_2ND_COL
  #undef _STORE_3RD_COL
  #undef _STORE_4TH_COL
  #undef _STORE_5TH_COL
  #undef _STORE_LANG_ENG
  #undef _STORE_LANG
  #undef _IS_FIRST_LETTER
  #undef _IS_LETTERS

  return TRUE;
} //cin_list_parse()


gboolean im_gui_progress_open(void)
{
	g_printf("(%s:%d)[%s() invoked]\n", __FILE__, __LINE__, __func__);
	return TRUE;
}//im_gui_progress_open()

gboolean im_gui_progress_set_value(gint value)
{
	g_printf("(%s:%d)[%s(value=%d) invoked]\n", __FILE__, __LINE__, __func__,value);
	return TRUE;
}//im_gui_progress_set_value()

gboolean im_gui_progress_close(void)
{
	g_printf("(%s:%d)[%s() invoked]\n", __FILE__, __LINE__, __func__);
	return TRUE;
}//im_gui_progress_close()


void connect_button_clicked(GtkWidget* me, gpointer data)
{
//	GladeXML *xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;
	GtkTreeSelection* selection = gtk_tree_view_get_selection(treeview);
	GtkTreeModel* model;
	GtkTreeIter iter;


	if(FALSE == gtk_tree_selection_get_selected( selection, &model, &iter))
	{
		printf("get_tree_selection_get_select() return FALSE\n");
		 return;
	}
	printf("get_tree_selection_get_select() return TRUE\n");
	gchar* text;
	static gchar url[255];

	gtk_tree_model_get(model, &iter, 1, &text, -1);
	g_utf8_str_assign(url,text);
	g_free(text);

	g_utf8_str_assign(ftp_baseurl,url); //ftp_baseurl is a global variable that will be used when download im file.

	g_utf8_str_append(url,"/cin.list");

	static gchar pf[100];
	g_sprintf(pf, "%s/.oxim/tables/%s/cin.list", g_get_usertmp_dir(), g_get_user_name());
	//if( !im_core_ftp_download( url, "./cin2.list",20))
	if( !im_core_ftp_download( url, pf,10))
	{	
		g_printf("\n\n ftp_download ERROR!!");
//		GtkWindow* parent_window = GTK_WINDOW(glade_xml_get_widget(xml,"installim_dialog"));
		GtkWindow* parent_window = GTK_WINDOW(GTK_WIDGET( gtk_builder_get_object(builder, "installim_dialog") ));
		GtkMessageDialog* message_dialog = GTK_MESSAGE_DIALOG(gtk_message_dialog_new(
			parent_window, //parent window
			GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,//GtkDialogFlags
			GTK_MESSAGE_ERROR,//GtkMessageType
			GTK_BUTTONS_CLOSE,//GtkButtonsType
			"(%s:%d)[%s()]\n Ftp download Error!", __FILE__, __LINE__, __func__
		));
		gtk_dialog_run(GTK_DIALOG(message_dialog));
		gtk_widget_destroy(GTK_WIDGET(message_dialog));
		//connect_status("");
		return;
	}

	g_printf("\n\n ftp_download SUCCEED!!");
//	GtkWidget* connect_btn = glade_xml_get_widget(xml, "connect_button");
	GtkWidget* connect_btn = GTK_WIDGET( gtk_builder_get_object(builder, "connect_button") );
//	connect_status("It's connecting on the station  [ %s ]", ftp_baseurl);
	gtk_widget_set_sensitive(connect_btn, FALSE);
	installim_treeview_build_cin_list(0);
} //connect_button_clicked()

#if 0
static gint is_parent_idx=0;
static gint is_sensitive_idx=1;
static gint is_toggle_actived_idx=2;
static gint language_idx=3;
static gint im_file_idx=4;
static gint im_name_idx=5;
static gint description_idx=6;
#else
static gint is_parent_idx=0;
static gint is_sensitive_idx=1;
static gint is_toggle_actived_idx=2;
static gint language_idx=3;
static gint im_file_idx=5;
static gint im_name_idx=6;
static gint description_idx=7;

#endif 

static void set_cin_list_model_idx(void)
{
 
 // gchar *loc = (gchar*)g_strdup(setlocale(LC_MESSAGES,NULL));
  //gchar *loc = (gchar*)g_strdup(setlocale(LC_MESSAGES,NULL));
  gchar *loc = (gchar*)g_strdup(g_getenv("LANG"));
  g_printf("\nloc = %s\n",loc);

  g_printf("\nloc = %s\n",loc);
  g_printf("\nloc = %s\n",loc);
  g_printf("\nloc = %s\n",loc);
  g_printf("\nloc = %s\n",loc);
  if(!strncmp("zh",loc,2))
  {
    is_parent_idx=0;
    is_sensitive_idx=1;
    is_toggle_actived_idx=2;
    language_idx=3;
    im_file_idx=5;
    im_name_idx=6;
    description_idx=7;
  }
  else
  {
    is_parent_idx=0;
    is_sensitive_idx=1;
    is_toggle_actived_idx=2;
    language_idx=4;
    im_file_idx=5;
    im_name_idx=8;
    description_idx=9;
  }

  g_free(loc);
};


void fixed_toggled2 ( GtkCellRendererToggle *cell, gchar *path_str, gpointer data)
{
  g_printf("[Func %s() is invoked]\n",__func__);
  gboolean is_sensitive;
  gboolean is_parent;
	GtkTreeModel *model = (GtkTreeModel *)data;
	GtkTreeIter iter;
	GtkTreePath *path = gtk_tree_path_new_from_string(path_str);
	gboolean fixed;	
	gtk_tree_model_get_iter( model,&iter,path);	
	gtk_tree_path_free (path);

	gtk_tree_model_get(model, &iter,is_parent_idx, &is_parent,  is_sensitive_idx, &is_sensitive, is_toggle_actived_idx, &fixed, -1);
	if(!is_parent)
	{
		if(is_sensitive)
		{
			fixed ^= 1 ;
			gtk_tree_store_set (GTK_TREE_STORE(model), &iter, is_toggle_actived_idx,fixed, -1);
		}
	}
	else
	{
		//TODO: expand all im in the same language 
		gtk_tree_view_collapse_all(treeview);
		
	}

}//fixed_toggled ()



void toggle_cell_data_func(GtkTreeViewColumn* column, GtkCellRenderer* renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{	
	gboolean is_parent;
	gboolean is_sensitive;
	gboolean is_toggle_actived;
	gtk_tree_model_get(model, iter, is_parent_idx, &is_parent, is_sensitive_idx, &is_sensitive, is_toggle_actived_idx, &is_toggle_actived,-1);
	if(is_parent)
	{
		g_object_set(renderer, "visible", FALSE,NULL);
	}
	else
	{
		g_object_set(renderer,"visible",TRUE,NULL);
		//g_object_set(renderer,"active",is_toggle_actived);
		g_object_set(renderer,"sensitive",is_sensitive,NULL);
	}

}// toggle_cell_data_func()



void name_cell_data_func(GtkTreeViewColumn* column, GtkCellRenderer* renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
	gboolean is_parent;
	gboolean is_sensitive;
	gboolean is_toggle_actived;
	gtk_tree_model_get(model, iter, is_parent_idx, &is_parent, is_sensitive_idx, &is_sensitive, is_toggle_actived_idx, &is_toggle_actived,-1);
	if(is_parent)
	{
		gchar* text;
		gtk_tree_model_get(model,iter,language_idx,&text,-1);
		g_object_set(renderer, "text", text, NULL);
		g_object_set(renderer, "sensitive", TRUE,NULL);
		g_free(text);
	}
	else
	{
		gchar* text;
		gtk_tree_model_get(model,iter, im_name_idx, &text,-1);
		g_object_set(renderer, "text", text, NULL);
		g_free(text);
		g_object_set(renderer, "sensitive",is_sensitive, NULL);
		
	}

}// name_cell_data_func()


void description_cell_data_func(GtkTreeViewColumn* column, GtkCellRenderer* renderer, GtkTreeModel* model, GtkTreeIter* iter, gpointer data)
{
	gboolean is_parent;
	gboolean is_sensitive;
	gboolean is_toggle_actived;
	gtk_tree_model_get(model, iter, is_parent_idx, &is_parent, is_sensitive_idx, &is_sensitive, is_toggle_actived_idx, &is_toggle_actived,-1);
	
	if(is_parent)
	{
		g_object_set(renderer, "text","",NULL);
	}
	else
	{
		gchar* text;
		gtk_tree_model_get(model,iter,description_idx,&text,-1);
		//g_printf("\n\n description text = \"%s\"\n\n",text);
		g_object_set(renderer, "text",text,NULL);

		//g_object_set(renderer, "text","GOOD",NULL);
		g_free(text);
		g_object_set(renderer, "sensitive",is_sensitive, NULL);
	
	}

}// description_cell_data_func()


const gchar* im_downloadable(GtkTreeModel* model, GtkTreeIter* iter)
{
	gboolean is_parent;
	gboolean is_sensitive;
	gboolean is_toggle_actived;
	static gchar filename_cin_gz[100];
	gchar* text;
	
	gtk_tree_model_get(model,iter, is_parent_idx, &is_parent, is_sensitive_idx, &is_sensitive, is_toggle_actived_idx, &is_toggle_actived, -1);
	if(is_parent) return NULL;
	if(!is_sensitive) return NULL;
	if(!is_toggle_actived) return NULL;
	gtk_tree_model_get(model,iter, im_file_idx,&text,-1);
	g_utf8_str_assign(filename_cin_gz, text);
	g_free(text);
	g_printf("(%s:%d)[%s()] return %s\n", __FILE__, __LINE__, __func__, filename_cin_gz);
	return filename_cin_gz;
	
}// im_downloadable()


void installim_treeview_build_mirrors_site(void)
{
//	GladeXML *xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;
//	treeview = GTK_TREE_VIEW(glade_xml_get_widget(xml, "installim_treeview"));
	treeview = GTK_TREE_VIEW( GTK_WIDGET( gtk_builder_get_object(builder, "installim_treeview") ) );


  g_signal_connect(G_OBJECT(treeview),
                     "button_press_event",
                     G_CALLBACK(signal_handler_event),
                     NULL);

  /* and/or */

  g_signal_connect(G_OBJECT(treeview),
                     "button_release_event",
                     G_CALLBACK(signal_handler_event),
                     NULL);

  /* something else */


	GtkTreeModel* model;
	GtkTreeViewColumn* column;
	GtkCellRenderer* renderer;
	
	column = gtk_tree_view_column_new();		
	gtk_tree_view_column_set_title(column, _("Select a site to download"));
	renderer= gtk_cell_renderer_text_new();	
	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	//gtk_tree_view_column_set_cell_data_func(column, renderer, some_cell_data_func, NULL, NULL);
	gtk_tree_view_column_set_attributes(column, renderer, "text",0,NULL);
	gtk_tree_view_append_column(treeview,column);
	//gtk_tree_view_append_column( treeview, gtk_tree_view_column_new_with_attributes("Host Position", gtk_cell_renderer_text_new(), "text", 0, NULL));
	

	list_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	model = GTK_TREE_MODEL(list_store);
	//GtkTreeIter iter;
	gtk_tree_view_set_model(treeview, model);
	GIOChannel *read;
	gchar *content;
	GError *error = NULL;
	gsize bytes;

	gint idx=0;
	gint pste=0;	
		
	//read = g_io_channel_new_file("./mirrors.site", "r", &error);
	static gchar fp[100]="\0";
	//g_sprintf(fp,"/%s/.oxim/mirrors.site",g_get_user_name());
	g_sprintf(fp,"%s/.oxim/mirrors.site",g_get_userhome_dir());
	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	read = g_io_channel_new_file(fp, "r", &error);
	if(error!=NULL)
	{
		//g_print(error->message);
		g_printf("(%s:%d)[%s(filename=%s)] g_io_channel_new_file's error msg is[%s]\n",__FILE__, __LINE__, __func__,  fp ,error->message);
		g_clear_error(&error);
	}

	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	g_io_channel_read_to_end(read, &content, &bytes, NULL);
	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	g_io_channel_close(read);
	g_printf("(%s:%d)[%s(filename=%s)] \n",__FILE__, __LINE__, __func__,  fp );
	g_printf("token parse...mirrors_site_parse2\n");
	idx=0;
	pste=0;
	for(idx=0;idx<bytes;idx++)
	{
		gchar token = content[idx];
		if(!mirrors_site_parse2(&pste, token))
		{
		}
		else
		{
		}
	}
	g_free(content);
} // installim_treeview_build_mirrors_site()



void installim_treeview_build_cin_list(gint level)
{

	GtkTreeViewColumn* column;
	GtkCellRenderer* renderer;
	GtkTreeModel* model;
	//GtkTreeIter parent_iter;
	//GtkTreeIter iter;
#if 0
	tree_store = gtk_tree_store_new(7, 
		G_TYPE_BOOLEAN, //is_parent	
		G_TYPE_BOOLEAN, //is_sensitive
		G_TYPE_BOOLEAN, //is_toggle_actived
		G_TYPE_STRING,	//is_parent ? language 
		G_TYPE_STRING,  //!is_parent ? im_file
		G_TYPE_STRING,  //!is_parent ? im_name
		G_TYPE_STRING	//!is_parent ? im_description
	);
#else
	tree_store = gtk_tree_store_new(10, 
		G_TYPE_BOOLEAN, //is_parent	
		G_TYPE_BOOLEAN, //is_sensitive
		G_TYPE_BOOLEAN, //is_toggle_actived
		G_TYPE_STRING,	//is_parent ? language 
		G_TYPE_STRING,	//is_parent ? language (english)

		G_TYPE_STRING,  //!is_parent ? im_file
		G_TYPE_STRING,  //!is_parent ? im_name
		G_TYPE_STRING,	//!is_parent ? im_description

		G_TYPE_STRING,  //!is_parent ? im_name (english)
		G_TYPE_STRING	//!is_parent ? im_description (english)
	
	);

#endif 
	model = GTK_TREE_MODEL(tree_store);



	//remove orginal treeview column setting, which is show for mirrors.site
	if(level==0)
	{
	  column = gtk_tree_view_get_column(treeview,0);
	  gtk_tree_view_remove_column(treeview, column);
	}
	else if(level==1)
	{
//	  GladeXML *xml = dialog_data.header.xml;
	  GtkBuilder *builder = dialog_data.header.builder;
//	  treeview = GTK_TREE_VIEW(glade_xml_get_widget(xml, "installim_treeview"));
	  treeview = GTK_TREE_VIEW( GTK_WIDGET( gtk_builder_get_object(builder, "installim_treeview") ) );
	}

	//add a new treeview column setting, which is show for cin.list
	column = gtk_tree_view_column_new();		
	gtk_tree_view_append_column(treeview, column);
	gtk_tree_view_column_set_title(column, _("Language&Input Method Name"));
	renderer = gtk_cell_renderer_toggle_new();
	gtk_tree_view_column_pack_start(column,renderer,TRUE);

	g_signal_connect(renderer, "toggled", G_CALLBACK(fixed_toggled2), model);
	gtk_tree_view_column_set_attributes(column, renderer, "active", 2, NULL);
	gtk_tree_view_column_set_cell_data_func(column, renderer, toggle_cell_data_func,NULL,NULL);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(column,renderer,TRUE);
	gtk_tree_view_column_set_cell_data_func(column, renderer, name_cell_data_func,NULL,NULL);

	column = gtk_tree_view_column_new();	
	gtk_tree_view_column_set_title(column, _("Description"));
	gtk_tree_view_append_column(treeview, column);
	renderer = gtk_cell_renderer_text_new();	
	gtk_tree_view_column_pack_start(column,renderer,TRUE);

	gtk_tree_view_column_set_cell_data_func(column, renderer, description_cell_data_func, NULL, NULL);
	
	set_cin_list_model_idx();
#if 0
    #if 0
	gtk_tree_store_append(tree_store, &parent_iter, NULL);
	gtk_tree_store_set(tree_store, &parent_iter, 0,TRUE,1,TRUE, 3,"Language 1", -1);
	gtk_tree_store_append(tree_store, &iter , &parent_iter);
	gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,FALSE, 2,TRUE, 4,"xxx.cin.gz", 5,"InputMethod 1",6,"Description 1" ,-1);
	gtk_tree_store_append(tree_store, &iter , &parent_iter);
	gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,TRUE, 2,TRUE, 4,"xxx.cin.gz", 5,"InputMethod 1",6,"Description 1" ,-1);
    #else
	gtk_tree_store_append(tree_store, &parent_iter, NULL);
	gtk_tree_store_set(tree_store, &parent_iter, 0,TRUE,1,TRUE, 3,"語言1",4,"Language 1", -1);
	gtk_tree_store_append(tree_store, &iter , &parent_iter);
	//gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,FALSE, 2,TRUE, 5,"xxx.cin.gz", 6,"InputMethod 1",7,"Description 1" ,-1);
	gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,FALSE, 2,TRUE, 5,"xxx1.cin.gz", 6,"輸入法 1",7,"說明 1",8,"InputMethod 1",9,"Description 1" ,-1);
	gtk_tree_store_append(tree_store, &iter , &parent_iter);
	gtk_tree_store_set(tree_store, &iter, 0,FALSE, 1,TRUE, 2,TRUE, 5,"xxx2.cin.gz", 6,"輸入法 2",7,"描述 2",8,"InputMethod 2",9,"Description 2" ,-1);

    #endif 
#else

	GIOChannel *read;
	gchar *content;
	GError *error = NULL;
	gsize bytes;

	gint idx=0;
	gint pste=0;	
	static gchar pf[100];
	//if( !im_core_ftp_download( url, "./cin2.list",20))
	g_sprintf(pf, "%s/.oxim/tables/%s/cin.list",g_get_usertmp_dir(), g_get_user_name());
	//read = g_io_channel_new_file("./cin2.list", "r", &error);
	read = g_io_channel_new_file(pf, "r", &error);
	if(error!=NULL)
	{
		g_print(error->message);
		g_clear_error(&error);
		return;
	}


	g_io_channel_read_to_end(read, &content, &bytes, NULL);
	g_io_channel_close(read);
	g_printf("token parse...cin.list\n");
	idx=0;
	pste=0;
	for(idx=0;idx<bytes;idx++)
	{
	  gchar token = content[idx];
	  if(!cin_list_parse(&pste, token))
	  {
	  }
	  else
	  {
	  }
	}
	if(0) //TODO: how about that when parse error
	{
	  if(is_zhtw())
	    connect_status("選擇完輸入法後，請按下按鈕 '%s' 安裝輸入法\n", _("OK")); 
	  else
	    connect_status("Press button '%s' to install the input method you choice", _("OK")); 

	  //connect_status("Press button '%s' to install the input method you choice", _("OK"));
	  ftp_is_connecting_on = TRUE;
	}
	g_free(content);



#endif //if 0 




	gtk_tree_view_set_model(treeview, model);
	
} //installim_treeview_build_cin_list()


void install_notebook_switch_page_cb(GtkWidget* me)
{
//  GladeXML *xml = dialog_data.header.xml;
  GtkBuilder *builder = dialog_data.header.builder;

//  gint page_num = gtk_notebook_get_current_page(GTK_NOTEBOOK(glade_xml_get_widget(xml,"install_notebook")));
  gint page_num = gtk_notebook_get_current_page(GTK_NOTEBOOK(GTK_WIDGET( gtk_builder_get_object(builder, "install_notebook") )));
  if(page_num==1) return;  
  if(is_external_url)
  {
//     gtk_widget_set_sensitive(glade_xml_get_widget(xml,"connect_button"), FALSE);
	gtk_widget_set_sensitive( GTK_WIDGET( gtk_builder_get_object(builder, "connect_button") ), FALSE);
  }

  if(install_from_internet_now == FALSE)
  {	
//	GladeXML *xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;

	if(!is_external_url)
	{ 
#if 0
	  //connect_status("Please choice ftp to install input method");
	  if(is_zhtw())
	    connect_status("請選擇列表中的ftp站台來安裝輸入法");
	  else
	    connect_status("Please choice ftp to install input method");
#endif
	  installim_treeview_build_mirrors_site();
	}
	else
	{
	  //connect_status("");
	  gchar url[200];
	  g_sprintf(url,g_getenv("EXTERNAL_DOWNLOAD_URL"));
	  g_utf8_str_assign(ftp_baseurl,url); //ftp_baseurl is a global variable that will be used when download im file.
	  g_utf8_str_append(url,"/cin.list");
	  static gchar pf[100];
	  connect_status("Try to connect:[%s]", ftp_baseurl);
	  g_sprintf(pf, "%s/.oxim/tables/%s/cin.list", g_get_usertmp_dir(), g_get_user_name());
	  if( !im_core_ftp_download( url, pf,10))
	  {	
		g_printf("\n\n ftp_download ERROR!!");
//		GtkWindow* parent_window = GTK_WINDOW(glade_xml_get_widget(xml,"installim_dialog"));
		GtkWindow* parent_window = GTK_WINDOW(GTK_WIDGET( gtk_builder_get_object(builder, "installim_dialog") ));
#if 1
		GtkMessageDialog* message_dialog = GTK_MESSAGE_DIALOG(gtk_message_dialog_new(
			parent_window, //parent window
			GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,//GtkDialogFlags
			GTK_MESSAGE_ERROR,//GtkMessageType
			GTK_BUTTONS_CLOSE,//GtkButtonsType
			"(%s:%d)[%s()]\n Ftp download Error!", __FILE__, __LINE__, __func__
		));
		gtk_dialog_run(GTK_DIALOG(message_dialog));
		gtk_widget_destroy(GTK_WIDGET(message_dialog));
#endif 
		if(is_zhtw())
		  connect_status("站台[%s]\n連線失敗", ftp_baseurl);
		else
		  connect_status("Connect failed:[%s]", ftp_baseurl);
		return;
	  }

	  g_printf("\n\n ftp_download SUCCEED!!");		

//	  GtkWidget* connect_btn = glade_xml_get_widget(xml, "connect_button");
	  GtkWidget* connect_btn = GTK_WIDGET( gtk_builder_get_object(builder, "connect_button") );
	  gtk_widget_set_sensitive(connect_btn, FALSE); 
	  if(is_zhtw())
	    connect_status("與站台[%s]連線中...", ftp_baseurl);
	  else	  
	    connect_status("Connecting to station:[%s]", ftp_baseurl);
	  installim_treeview_build_cin_list(1);
	} //else of (!is_external_url)


    install_from_internet_now = TRUE;
  }
}//install_notebook_switch_page_cb()



void connect_button_enter_cb(GtkWidget* me)
{
	//GladeXML *xml = dialog_data.header.xml;
	GtkTreeSelection* selection = gtk_tree_view_get_selection(treeview);
	GtkTreeModel* model;
	GtkTreeIter iter;


	if(FALSE == gtk_tree_selection_get_selected( selection, &model, &iter))
	{
		 return;
	}
	gchar* text;
	static gchar url[255];
	gtk_tree_model_get(model, &iter, 1, &text, -1);
	g_utf8_str_assign(url,text);
	g_free(text);
	g_utf8_str_assign(ftp_baseurl,url);
//	if(is_zhtw())
//	  connect_status("按下此鈕後，可連線至站台\n  [ %s ]", ftp_baseurl);
//	else
//	  connect_status("Click to connect  [ %s ]", ftp_baseurl);
} //connect_button_enter_cb()
void connect_button_leave_cb(GtkWidget* me)
{
return;
	//connect_status("");
	if(!ftp_is_connecting_on) 
	  if(is_zhtw())
	    connect_status("請選擇列表中的ftp站台來安裝輸入法");
	  else
	    connect_status("Please choice ftp to install input method");
	else
	  if(is_zhtw())
	    connect_status("選擇完輸入法後，請按下按鈕 '%s' 安裝輸入法\n", _("OK")); 
	  else
	    connect_status("Press button '%s' to install the input method you choice", _("OK")); 
} //connect_button_leave_cb()

void connect_button_pressed_cb(GtkWidget* me)
{

//	if(is_zhtw())
//	  connect_status("正嘗試連接站台\n[%s]", ftp_baseurl);
//	else
//	  connect_status("It's tring to connect [ %s ]", ftp_baseurl);
} //connect_button_pressed_cb()



void installim_dialog_accept_button_pressed_cb(GtkWidget* me)
{
	//connect_status("It's to download and install the input method(s)  from [ %s ]" ,ftp_baseurl);
	if(is_zhtw())
	  connect_status("正從站台 [%s ] \n下載及安裝輸入法" ,ftp_baseurl);
	else
	  connect_status("It's to download and install the input method(s)  from [ %s ]" ,ftp_baseurl);
} //installim_dialog_accept_button_pressed_cb()


void installim_dialog_accept_button_enter_cb(GtkWidget* me)
{
	if(ftp_is_connecting_on)
	{
	  if(is_zhtw())	
	    connect_status("按下此鈕後，方可下載\n站台[%s]輸入法" ,ftp_baseurl);
	  else
	    connect_status("Click to download input method(s)  from [ %s ]" ,ftp_baseurl);
	}


} //installim_dialog_accept_button_pressed_cb()

void installim_dialog_accept_button_leave_cb(GtkWidget* me)
{
return;
	if(ftp_is_connecting_on )
	{
	  if(is_zhtw())
	    connect_status("選擇完輸入法後，請按下按鈕 '%s' 安裝輸入法\n", _("OK")); 
	  else
	    connect_status("Press button '%s' to install the input method you choice", _("OK")); 

	  //connect_status("Press button '%s' to install the input method you choice", _("OK"));

	}
} //installim_dialog_accept_button_pressed_cb()


gint signal_handler_event(GtkWidget *widget, GdkEventButton *event, gpointer func_data)
{
 // g_printf("AAA\n");
  if (GTK_IS_TREE_VIEW(widget) &&
       (event->type==GDK_2BUTTON_PRESS ||
        event->type==GDK_3BUTTON_PRESS) ) {
    //g_printf("I feel %s clicked with button %d\n", event->type==GDK_2BUTTON_PRESS ? "double" : "triple", event->button);
  }
#if 1
  if(!ftp_is_connecting_on && (event->type==GDK_2BUTTON_PRESS || event->type==GDK_3BUTTON_PRESS)) //TODO: condition
  { //TODO:logical condition is not enough when treeview is empty
    if(1)
    {
	//GladeXML *xml = dialog_data.header.xml;
	GtkTreeSelection* selection = gtk_tree_view_get_selection(treeview);
	GtkTreeModel* model;
	GtkTreeIter iter;


	if(FALSE == gtk_tree_selection_get_selected( selection, &model, &iter))
	{
		g_printf("get_tree_selection_get_select() return FALSE\n");
		 return FALSE;
	}
	g_printf("get_tree_selection_get_select() return TRUE\n");
	gchar* text;
	static gchar url[255];

	gtk_tree_model_get(model, &iter, 1, &text, -1);
	g_utf8_str_assign(url,text);
	g_free(text);

	g_utf8_str_assign(ftp_baseurl,url); //ftp_baseurl is a global variable that will be used when download im file.
    }
//	GladeXML *xml = dialog_data.header.xml;
	GtkBuilder *builder = dialog_data.header.builder;
//	g_signal_emit_by_name((gpointer)(glade_xml_get_widget(xml,"connect_button")), "pressed");
	g_signal_emit_by_name((gpointer)(GTK_WIDGET( gtk_builder_get_object(builder, "connect_button") )), "pressed");
//	g_signal_emit_by_name((gpointer)(glade_xml_get_widget(xml,"connect_button")), "clicked");
	g_signal_emit_by_name((gpointer)(GTK_WIDGET( gtk_builder_get_object(builder, "connect_button") )), "clicked");
	//connect_button_clicked(NULL,NULL);
  }
  else if(ftp_is_connecting_on && (event->type==GDK_2BUTTON_PRESS || event->type==GDK_3BUTTON_PRESS) )
  {
    GtkTreeSelection* selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel* model;
    GtkTreeIter iter;
    if(FALSE == gtk_tree_selection_get_selected( selection, &model, &iter))
    {
	g_printf("get_tree_selection_get_select() return FALSE\n");
    }
    else
    {
	gboolean is_lang=FALSE;
	gtk_tree_model_get(model, &iter, 0,&is_lang,-1);
	if(is_lang)
	{	
	 
	  gboolean open_all = TRUE;
	  GtkTreePath* treepath;
	  gchar *string;
	  string = gtk_tree_model_get_string_from_iter(model,&iter);
	  treepath = gtk_tree_path_new_from_string(string);
	  g_free(string);	 
	  gboolean bv = gtk_tree_view_row_expanded(treeview, treepath);
	  gtk_tree_view_collapse_all (treeview);

	  if(!bv)
	    gtk_tree_view_expand_row(treeview, treepath, open_all);
	    
	  gtk_tree_path_free(treepath);
	}
    }

  } 
 #if 0

  else if(ftp_is_connecting_on && (event->type==GDK_BUTTON_PRESS))
  {
    GtkTreeSelection* selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel* model;
    GtkTreeIter iter;

    if(FALSE == gtk_tree_selection_get_selected( selection, &model, &iter))
    {
	g_printf("get_tree_selection_get_select() return FALSE\n");
    }
    else
    {
	gboolean is_lang=FALSE;
	gtk_tree_model_get(model, &iter, 0,&is_lang,-1);
	if(is_lang)
	{	
	 // gtk_tree_view_collapse_all (treeview);
	  gboolean open_all = TRUE;
	  GtkTreePath* treepath;
	  gchar *string;
	  string = gtk_tree_model_get_string_from_iter(model,&iter);
	  treepath = gtk_tree_path_new_from_string(string);
	  g_free(string);
	  if(gtk_tree_view_row_expanded(treeview, treepath))
	  {
	    //gtk_tree_view_collapse_row(treeview, treepath);
	  }
	  else
	  {
	    gtk_tree_view_expand_row(treeview, treepath, open_all);
	  }	
	  gtk_tree_path_free(treepath);
	}
    }
  } 
 #endif
#endif 
  

  return FALSE;
}

