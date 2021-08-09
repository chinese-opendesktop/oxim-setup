if ENABLE_SETUP_PYGTK

install-strip:install-data-local
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_PYGTK_DIR) 
	cp -a src/* $(DESTDIR)/$(OXIMSETUP_PYGTK_DIR)
	install $(DESTDIR)/$(OXIMSETUP_PYGTK_DIR)/oxim-setup-pygtk $(DESTDIR)/$(OXIMSETUP_PYGTK_DIR)/oxim-setup
	rm $(DESTDIR)/$(OXIMSETUP_PYGTK_DIR)/oxim-setup-pygtk
endif
