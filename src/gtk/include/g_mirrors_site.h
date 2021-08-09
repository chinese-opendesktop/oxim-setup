
#ifndef _G_MIRRORS_SITE_H 
#define _G_MIRRORS_SITE_H

gboolean g_mirrors_site_set( const gchar* hostname, const gchar* attribute, const gchar* value);
gboolean g_mirrors_site_get( const gchar* hostname, const gchar* attribute, gchar** ret_value);

gboolean g_mirrors_site_first_hostname(gchar** ret_hostname);
gboolean g_mirrors_site_next_hostname(gchar** ret_hostname);

gboolean g_mirrors_site_update(void);
gboolean g_mirrors_site_reload(void);

#endif //_G_MIRRORS_SITE_H 
