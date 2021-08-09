#ifndef _INSTALLIM_CORE_EMBASSADOR_H
#define _INSTALLIM_CORE_EMBASSADOR_H
#include "oxim_setup_gtk_global.h"
//core have the responsibility to to implement  installim_core_embassador.h
//all of callback functions in installim_core_embassador.h will be call by installim program.
gboolean im_core_ftp_download(const gchar *url, const gchar *filepath, gint timeout_second);
gboolean im_core_im_has_exist(const gchar *filename_cin_gz);
const gchar* im_core_get_download_dir(void);
void im_core_tab_pool_add_im(const gchar *im_name, const gchar* filepath_cin_gz); //im_name is the xxx's part of xxx.tab, filepath denote xxx.cin.gz
void im_core_tab_pool_clear(void);
#endif  //_INSTALLIM_CORE_EMBASSADOR_H


