if ENABLE_SETUP_GAMBAS

EXTRA_DIST = $(PACKAGE)

if GB_READY

all:
	@(if test -x /usr/bin/gbc2; then \
	 echo "Building $(PACKAGE) component..."; \
         $(GAMBAS_path)/gbc2 -a -t ; \
         $(GAMBAS_path)/gba2 ; \
	else \
	 echo "Compiling $(PACKAGE) project..."; \
	fi)

endif

install-strip: install-exec-local
install-exec-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_GAMBAS_DIR)/.lang
	$(INSTALL_DATA) $(top_srcdir)/po/zh_TW.gmo $(DESTDIR)/$(OXIMSETUP_GAMBAS_DIR)/.lang/zh_TW.mo
	$(INSTALL_DATA) $(top_srcdir)/po/zh_TW.gmo .lang/zh_TW.mo
	$(INSTALL_DATA) $(top_srcdir)/po/zh_CN.gmo $(DESTDIR)/$(OXIMSETUP_GAMBAS_DIR)/.lang/zh_CN.mo
	$(INSTALL_DATA) $(top_srcdir)/po/zh_CN.gmo .lang/zh_CN.mo
	$(INSTALL_DATA) $(top_srcdir)/po/zh_HK.gmo $(DESTDIR)/$(OXIMSETUP_GAMBAS_DIR)/.lang/zh_HK.mo
	$(INSTALL_DATA) $(top_srcdir)/po/zh_HK.gmo .lang/zh_HK.mo
if GB_READY
	if test -x /usr/bin/gbc2; then \
		$(GAMBAS_path)/gbc2 -a -t -p -m && $(GAMBAS_path)/gba2 ; \
	fi
endif
	install oxim-setup-gambas.gambas $(DESTDIR)/$(OXIMSETUP_GAMBAS_DIR)/oxim-setup
endif
