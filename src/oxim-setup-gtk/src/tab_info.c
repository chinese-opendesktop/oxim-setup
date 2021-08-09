
#include "oxim_setup_gtk_global.h"
#include "tab_info.h"
#include <zlib.h>
/* General char type: mbs encoding
 *
 * Note: In Linux, if uch_t.s = "a1 a4", then uch_t.uch = 0xa4a1, i.e.,
 *       the order reversed. This might not be the general case for all
 *       plateforms.
 */
//Macro defined in oximtool.h


#define BUFFER_LEN (255)
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

static char *realCname(char *c_name, char *e_name);


















gboolean tab_info_get_name(gchar *filepath, gchar **ret_chi_name, gchar** ret_eng_name)
{
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
	int read_size=0;
	int hd_size=0;
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
    return valid;
}//get_name()



















static char *realCname(char *c_name, char *e_name)
{
	char delims[] = ";";
	char *result = NULL;
	char loc[BUFFER_LEN];
	//strcpy(loc, setlocale(LC_MESSAGES, NULL));
	strcpy(loc, g_getenv("LANG"));
	/*檢查有沒有包含冒號，若沒有應該是舊的中文名稱*/
	if( NULL == strchr(e_name, delims[0]) )
	{
		return 
			0==strncmp(loc, "zh", 2) ?
				c_name :  /*若locale開頭=『zh_』則傳回中文名稱*/
				e_name;	/*否則傳回英文名稱*/
	}
	
	char loc_comp[3][BUFFER_LEN];
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








