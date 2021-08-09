#ifndef _DEFAULT_INPUT_METHODS_H
#define _DEFAULT_INPUT_METHODS_H
const gchar* default_input_methods_get_first_im(void);
const gchar* default_input_methods_get_next_im(void);
gboolean default_input_methods_is_im_exist(const gchar* im);
const gchar* default_input_methods_get_chiname(const gchar* im);
const gchar* default_input_methods_get_engname(const gchar* chiname);
#endif//_DEFAULT_INPUT_METHODS_H



