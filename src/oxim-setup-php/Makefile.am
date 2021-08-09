if ENABLE_SETUP_PHP

oxim_setup_php = oxim-setup-php

install-strip:install-data-local
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_PHP_DIR) 
	cp -a src/* $(DESTDIR)/$(OXIMSETUP_PHP_DIR)
	rm -f $(DESTDIR)/$(OXIMSETUP_PHP_DIR)/oxim-setup.glade.in
	install $(DESTDIR)/$(OXIMSETUP_PHP_DIR)/oxim-setup.php $(DESTDIR)/$(OXIMSETUP_PHP_DIR)/oxim-setup
	sed -i 's|@PHP_BASE_DIR@|"$(OXIMSETUP_PHP_DIR)"|' $(DESTDIR)/$(OXIMSETUP_PHP_DIR)/oxim-setup

endif
