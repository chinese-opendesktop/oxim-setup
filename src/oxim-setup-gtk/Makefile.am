if ENABLE_SETUP_GTK

bin_PROGRAMS = oxim-setup-gtk

INCLUDES = -Iinclude/ \
	   $(GTK2_CFLAGS) $(GLADE_CFLAGS) $(CURL_CFLAGS) \
	   -g -c -DINSTALLATION_LEVEL

LIBS += $(GTK2_LIBS) $(GLADE_LIBS) $(CURL_LIBS) -lz

oxim_setup_gtk_SOURCES = src/main.c \
		     src/chewing.c \
		     src/gencin.c \
		     src/globalsetting.c \
		     src/installim.c \
                     src/oxim_setting_and_config.c \
		     src/g_oxim_conf.c \
		     src/g_mirrors_site.c \
		     src/utils.c \
                     src/im_default_value.c \
                     src/default_input_methods.c \
                     src/phrase_record.c \
                     src/tab_info.c

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_GTK_DIR) $(DESTDIR)/$(OXIMSETUP_GTK_DIR)
	$(INSTALL_PROGRAM) $(DESTDIR)/$(bindir)/$(bin_PROGRAMS) $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/oxim-setup
	rm -f $(DESTDIR)/$(bindir)/$(bin_PROGRAMS)
	$(INSTALL_DATA) gui/oxim-setup-glade.xml $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) config/gtkrc $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) gui/icon_textview_icon1.png $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) gui/icon_textview_icon2.png $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) gui/icon_textview_icon3.png $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) gui/icon_textview_icon4.png $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) gui/icon_textview_icon5.png $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/
	$(INSTALL_DATA) gui/icon_textview_icon6.png $(DESTDIR)/$(OXIMSETUP_GTK_DIR)/

CLEANFILES = src/*.o

endif
