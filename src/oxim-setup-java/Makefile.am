if ENABLE_SETUP_JAVA

oxim_setup_java = oxim-setup-java

install-strip:install-data-local
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_JAVA_DIR) 
	cp -a src/* $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)
	rm -f $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/*.java
	rm -f $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/*.form
	rm -f $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/*.mf
	rm -f $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/*.png
	install $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/oxim-setup $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/oxim-setup.jar
	rm -f $(DESTDIR)/$(OXIMSETUP_JAVA_DIR)/oxim-setup
	

endif
