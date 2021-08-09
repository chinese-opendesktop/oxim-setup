#ifndef _IM_DEFAULT_VALUE_H
#define _IM_DEFAULT_VALUE_H



gboolean im_default_value_load(const gchar* im_name);
gboolean im_default_value_get_value(const gchar* attr, gchar** ret_value);
gboolean im_default_value_get_next_attr(gchar** ret_attr);
gboolean im_default_value_get_first_attr(gchar** ret_attr);

#endif//_IM_DEFAULT_VALUE_H
