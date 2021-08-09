#include "oxim_setup_gtk_global.h"
#include "im_default_value.h"
//The include file may be stronger in the future... since it could fit more and more habbit of IM  for other user.
static gchar name[200];
static GHashTable* h=NULL;
static GList *keys=NULL;
static GList *kptr = NULL;

static void uniliu_default(void);
static void cnsphone_default(void);
static void cnscj_default(void);
static void chewing_default(void);
static void unicode_default(void);


gboolean im_default_value_load(const gchar* im_name)
{

	g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
	if(im_name == NULL) return FALSE;
	g_utf8_str_assign(name, im_name);
	if(h!=NULL)
	{
		g_hash_table_destroy(h);
		h=NULL;
	}
	if(keys!=NULL)
	{
		g_list_free(keys);
		keys=NULL;
	}

	h = g_hash_table_new_full(g_str_hash,g_str_equal, g_free, g_free);

	if(g_utf8_str_equal(im_name, "uniliu")) //Uni蝦米
	{
		g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
		uniliu_default();
	}
	else if(g_utf8_str_equal(im_name, "cnsphone")) //中標注音
	{
		g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
		cnsphone_default();
	}
	else if(g_utf8_str_equal(im_name, "cnscj")) //中標倉頡
	{
		g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
		cnscj_default();
	}
	else if(g_utf8_str_equal(im_name, "chewing")) //新酷音
	{
		g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
		chewing_default();
	}
	else if(g_utf8_str_equal(im_name, "unicode")) //萬國碼
	{
		g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
		unicode_default();
	}
	else //其它一般輸入法
	{
		g_printf("(%s:%d)[%s(im_name=%s)]\n", __FILE__, __LINE__, __func__, im_name);
		g_hash_table_insert(h,g_strdup("AutoCompose"),g_strdup("Yes"));
		g_hash_table_insert(h,g_strdup("AutoUpChar"),g_strdup("Yes"));
		g_hash_table_insert(h,g_strdup("AutoFullUp"),g_strdup("No"));
		g_hash_table_insert(h,g_strdup("SpaceAutoUp"),g_strdup("No"));
		g_hash_table_insert(h,g_strdup("SelectKeyShift"),g_strdup("No"));
		g_hash_table_insert(h,g_strdup("SpaceIgnore"),g_strdup("Yes"));
		g_hash_table_insert(h,g_strdup("SpaceReset"),g_strdup("Yes"));
		g_hash_table_insert(h,g_strdup("WildEnable"),g_strdup("Yes"));
		g_hash_table_insert(h,g_strdup("EndKey"),g_strdup("No"));
		g_hash_table_insert(h,g_strdup("DisableSelectList"),g_strdup("None"));
	}
	keys = g_hash_table_mget_keys(h);
	//g_list_sort(keys, g_str_compare_func); 
	keys = g_list_sort(keys, g_str_compare_func);
	kptr=g_list_first(keys);
	//kptr = keys;
	return TRUE;
} // im_default_value_load()

gboolean im_default_value_get_value(const gchar* attr, gchar** ret_value)
{
	if(h==NULL)
	{
		g_printf("(%s:%d)[%s()] h==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}
	if(keys==NULL)
	{
		g_printf("(%s:%d)[%s()] keys==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}
	if(kptr==NULL)
	{
		g_printf("(%s:%d)[%s()] kptr==NULL\n", __FILE__, __LINE__, __func__);
		return FALSE;
	}
	gchar* text = NULL;
	text=g_hash_table_lookup(h,attr);
	if(text ==NULL)
	{
		g_printf("(%s:%d)[%s()] kptr==NULL\n", __FILE__, __LINE__, __func__);
		return FALSE;
	}

	*ret_value = g_strdup(text);
	return TRUE;
} //im_default_value_get_value()

gboolean im_default_value_get_next_attr(gchar** ret_attr)
{
	if(h==NULL)
	{
		g_printf("(%s:%d)[%s()] h==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}
	if(keys==NULL)
	{
		g_printf("(%s:%d)[%s()] keys==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}
	if(kptr==NULL)
	{
		g_printf("(%s:%d)[%s()] kptr==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}
	kptr = g_list_next(kptr);
	if(kptr==NULL)return FALSE;
	*ret_attr = g_strdup((gchar*)kptr->data);
	return TRUE;
} //im_default_value_get_next_attr()

gboolean im_default_value_get_first_attr(gchar** ret_attr)
{
	if(h==NULL)
	{
		g_printf("(%s:%d)[%s()] h==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}
	if(keys==NULL)
	{
		g_printf("(%s:%d)[%s()] keys==NULL\n", __FILE__, __LINE__, __func__); 
		return FALSE;
	}

	kptr = g_list_first(keys);
	if(kptr==NULL) return FALSE;
	*ret_attr = g_strdup((gchar*)kptr->data);
	return TRUE;
} //im_default_value_get_value_first_attr()



static void uniliu_default(void)
{
	g_hash_table_insert(h,g_strdup("AutoCompose"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("AutoUpChar"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("AutoFullUp"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("SpaceAutoUp"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("SelectKeyShift"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SpaceIgnore"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("SpaceReset"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("WildEnable"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("EndKey"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("DisableSelectList"),g_strdup("None"));
} //uniliu_default()

static void cnsphone_default(void)
{	
	g_hash_table_insert(h,g_strdup("AutoCompose"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("AutoUpChar"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("AutoFullUp"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SpaceAutoUp"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SelectKeyShift"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SpaceIgnore"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SpaceReset"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("WildEnable"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("EndKey"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("DisableSelectList"),g_strdup("None"));

} //cnsphone_default()


static void cnscj_default(void)
{
	g_hash_table_insert(h,g_strdup("AutoCompose"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("AutoUpChar"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("AutoFullUp"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("SpaceAutoUp"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SelectKeyShift"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("SpaceIgnore"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("SpaceReset"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("WildEnable"),g_strdup("Yes"));
	g_hash_table_insert(h,g_strdup("EndKey"),g_strdup("No"));
	g_hash_table_insert(h,g_strdup("DisableSelectList"),g_strdup("None"));

} //cnscj_default()


static void chewing_default(void)
{
	g_hash_table_insert(h,g_strdup("KeyMap"),g_strdup("0"));
	g_hash_table_insert(h,g_strdup("SelectionKeys"),g_strdup("0"));
	g_hash_table_insert(h,g_strdup("CapsLockMode"),g_strdup("0"));
} //chewing_default()



static void unicode_default(void)
{

} //unicode_default()


