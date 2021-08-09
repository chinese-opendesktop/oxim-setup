if ENABLE_SETUP_QT3

bin_PROGRAMS = oxim-setup-qt3

INCLUDES = -I$(top_srcdir)/src/include

oxim_setup_qt3_SOURCES = oxim-setup.pro \
		    oxim-setup.ui \
		    oxim-setup.ui.h \
		    globolsetting.ui \
		    globolsetting.ui.h
		    gencin.ui \
		    gencin.ui.h \
		    chewing.h \
		    installim.h \
		    installim.ui.h \
		    Sunpinyin.ui \
		    Sunpinyin.ui.h \
		    main.cpp 

oxim-setup-qt3: oxim-setup-qt3.pro
	$(QTDIR)/bin/qmake oxim-setup-qt3.pro -o Makefile.qt "QMAKE_CLEAN+=.moc/* .obj/*"
	QTDIR=$(QTDIR) make -f Makefile.qt

#$(QTDIR)/bin/qmake-qt4 oxim-setup-qt3.pro -o Makefile.qt "QMAKE_CLEAN+=.moc/* .obj/*"
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/$(OXIMSETUP_QT3_DIR)
	$(INSTALL_PROGRAM) $(bin_PROGRAMS) $(DESTDIR)/$(OXIMSETUP_QT3_DIR)/oxim-setup
	rm -f $(DESTDIR)/$(bindir)/$(bin_PROGRAMS)

CLEANFILES = Makefile.qt .ui/* .moc/* .obj/*

endif
