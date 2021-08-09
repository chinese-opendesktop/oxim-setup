AUTOMAKE_OPTIONS = gnu

input_d_dir = /etc/X11/xinit/xinput.d
xsession_d_dir = /etc/X11/Xsession.d
epc_autostart_dir = $(datadir)/autostart

SUBDIRS = \
	  po \
	  src/utils \
      	  src/oxim-setup-gtk \
	  src/oxim-setup-qt3 \
	  src/oxim-setup-qt4 \
	  src/oxim-setup-php \
	  src/oxim-setup-gambas \
	  src/oxim-setup-pygtk \
	  src/oxim-setup-oxzilla \
	  src/oxim-setup-java
	  

install-exec-local:
	$(mkinstalldirs) $(DESTDIR)/$(datadir)/applications
	$(INSTALL_DATA) oxim-setup.desktop $(DESTDIR)/$(datadir)/applications/oxim-setup.desktop
	$(mkinstalldirs) $(DESTDIR)/$(datadir)/pixmaps
	$(INSTALL_DATA) oxim-setup.png $(DESTDIR)/$(datadir)/pixmaps/oxim-setup.png
	$(mkinstalldirs) $(DESTDIR)/$(mandir)/man1
	$(INSTALL_DATA) oxim-setup.1 $(DESTDIR)/$(mandir)/man1/oxim-setup.1

#uninstall-local:
#	rm -f $(DESTDIR)/$(input_d_dir)/oxim
#if ENABLE_SETUP_TOOL
#	rm -f $(DESTDIR)/$(datadir)/applications/oxim-setup.desktop
#	rm -f $(DESTDIR)/$(datadir)/pixmaps/oxim-setup.png
#endif
