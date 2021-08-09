if ENABLE_SETUP_QT4

bin_PROGRAMS = oxim-setup-qt4

INCLUDES = -I$(top_srcdir)/src/include

oxim_setup_qt4_SOURCES = oxim-setup.pro \
		    oxim-setup.ui \
		    oxim-setup.h \
		    oxim-setup.cpp \
		    ui_oxim-setup.h \
		    attribute.ui \
		    attribute.h \
		    attribute.cpp \
		    ui_attribute.h \
		    chewingsetting.ui \
		    chewingsetting.h \
		    chewingsetting.cpp \
		    ui_chewingsetting.h \
		    commonsetting.ui \
		    commonsetting.h \
		    commonsetting.cpp \
		    ui_commonsetting.h \
		    install.ui \
		    install.h \
		    install.cpp \
		    ui_install.h \
		    main.cpp

oxim-setup-qt4: oxim-setup-qt4.pro
	/usr/bin/qmake-qt4 oxim-setup-qt4.pro -o Makefile.qt "QMAKE_CLEAN+=.moc/* .obj/*"
	QTDIR=$(QTDIR) make -f Makefile.qt

#$(QTDIR)/bin/qmake-qt4 oxim-setup-qt3.pro -o Makefile.qt "QMAKE_CLEAN+=.moc/* .obj/*"
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_QT4_DIR)
	$(INSTALL_PROGRAM) $(bin_PROGRAMS) $(DESTDIR)/$(OXIMSETUP_QT4_DIR)/oxim-setup
	rm -f $(DESTDIR)/$(bindir)/$(bin_PROGRAMS)

CLEANFILES = Makefile.qt .ui/* .moc/* .obj/*

endif
