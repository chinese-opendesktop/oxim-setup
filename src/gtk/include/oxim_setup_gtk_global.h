#ifndef OXIMSETUP_GLOBAL
#define OXIMSETUP_GLOBAL


#if defined(DEVELOPMENT_LEVEL)
#	define GTKRC_FILEPATH ("../config/gtkrc")
#	define GLADE_FILEPATH ("../gui/oxim-setup-glade.xml")
#	define TEXTVIEW_ICON1_FILEPATH ("../gui/icon_textview_icon1.png")
#	define TEXTVIEW_ICON2_FILEPATH ("../gui/icon_textview_icon2.png")
#	define TEXTVIEW_ICON3_FILEPATH ("../gui/icon_textview_icon3.png")
#	define TEXTVIEW_ICON4_FILEPATH ("../gui/icon_textview_icon4.png")
#	define TEXTVIEW_ICON5_FILEPATH ("../gui/icon_textview_icon5.png")
#	define TEXTVIEW_ICON6_FILEPATH ("../gui/icon_textview_icon6.png")
#	define V_PIXBUF_FILEPATH ("../gui/Vpixbuf.png")
#	define N_PIXBUF_FILEPATH ("../gui/Npixbuf.png")
#elif defined(INSTALLATION_LEVEL)
#	define GTKRC_FILEPATH (g_get_gtkrc_fp())
#	define GLADE_FILEPATH (g_get_glade_fp())
#  if __WORDSIZE == 64
#       define TEXTVIEW_ICON1_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/icon_textview_icon1.png")
#       define TEXTVIEW_ICON2_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/icon_textview_icon2.png")
#       define TEXTVIEW_ICON3_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/icon_textview_icon3.png")
#       define TEXTVIEW_ICON4_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/icon_textview_icon4.png")
#       define TEXTVIEW_ICON5_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/icon_textview_icon5.png")
#       define TEXTVIEW_ICON6_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/icon_textview_icon6.png")
#       define V_PIXBUF_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/Vpixbuf.png")
#       define N_PIXBUF_FILEPATH ("/usr/lib64/oxim-setup/oxim-setup-gtk/Npixbuf.png")
#  else
#	define TEXTVIEW_ICON1_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/icon_textview_icon1.png")
#	define TEXTVIEW_ICON2_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/icon_textview_icon2.png")
#	define TEXTVIEW_ICON3_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/icon_textview_icon3.png")
#	define TEXTVIEW_ICON4_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/icon_textview_icon4.png")
#	define TEXTVIEW_ICON5_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/icon_textview_icon5.png")
#	define TEXTVIEW_ICON6_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/icon_textview_icon6.png")
#	define V_PIXBUF_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/Vpixbuf.png")
#	define N_PIXBUF_FILEPATH ("/usr/lib/oxim-setup/oxim-setup-gtk/Npixbuf.png")
#  endif
#else
#	error no-define DEVELOPMENT_LEVEL OR INSTALLATION_LEVEL
#endif //DEVELOPE_LEVEL

#include <bits/wordsize.h>
#include <gtk/gtk.h>
//#include <glade/glade.h>
#include <gmodule.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gi18n.h>

#if ((GTK_MAJOR_VERSION == 2) && (GTK_MINOR_VERSION <= 4))
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define g_stat stat
#else
#include <glib/gstdio.h>
#endif

#include <zlib.h>
#include <libxml/nanoftp.h>
#include <glib-object.h>
//#include <gobject/gobject.h>
//#include <libgnomeprint/gnome-font.h>
#include "utils.h"
#define GETTEXT_PACKAGE ("oxim-setup")

//#define g_utf8_str_assign(str,assign) g_utf8_strncpy( (str), (assign),-1)

//#define g_utf8_str_append(str,append) g_utf8_strncpy( &((str)[g_utf8_strlen((str),-1)]),(append),-1)
//#define g_utf8_str_append(str,append) g_utf8_strncpy( (g_strstr_len((str),-1,"")), (append),-1)
//#define g_utf8_str_append(str,append) g_utf8_strncpy( &((str)[g_strlen((str),-1)]),(append),-1)
//#define g_utf8_str_equal(str1,str2) ((g_strncasecmp((str1),(str2),-1)==0)?(TRUE):(FALSE))

typedef struct
{
	gboolean is_dialog_press_accept; //if 1 -> accept, if 0 -> reject
//	GladeXML *xml;
	GtkBuilder *builder;
} dialog_data_header_t;

#endif //OXIMSETUP_GLOBAL
