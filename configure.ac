#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# $Id: configure.ac,v 1.7 2010/03/29 00:25:42 wind Exp $

AC_PREREQ(2.59)
AC_INIT([oxim-setup], 1.5.5, [firefly@opendesktop.org.tw])
AM_INIT_AUTOMAKE($PACKAGE_NAME, $PACKAGE_VERSION)

GB_INIT_PROJECT(oxim-setup-gambas)

AC_PREFIX_DEFAULT([/usr])  # 預設安裝路徑
AC_CONFIG_SRCDIR([COPYING])
AC_CONFIG_HEADER([config.h])

# i18N
AM_GNU_GETTEXT([external])
PACKAGE_GETTEXT=gettext
VERSION_GETTEXT=1.2.0
AC_SUBST(PACKAGE_GETTEXT)
AC_SUBST(VERSION_GETTEXT)


# Checks for programs.
AC_DISABLE_STATIC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

# Checks for header files.
AC_PATH_X
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_MAJOR
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([fcntl.h float.h langinfo.h limits.h locale.h stdlib.h string.h sys/param.h sys/time.h sys/timeb.h unistd.h utime.h zlib.h libintl.h iconv.h])

# Checks for library
AC_CHECK_LIB(intl, gettext)
AC_CHECK_LIB(iconv, iconv)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_UID_T
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_ST_BLKSIZE
AC_STRUCT_ST_BLOCKS
AC_STRUCT_ST_RDEV

AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_ST_BLOCKS
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_HEADER_TIME
AC_STRUCT_TM

AC_CHECK_SIZEOF(char,      [ 1 ])
AC_CHECK_SIZEOF(short,     [ 2 ])
AC_CHECK_SIZEOF(int,       [ 4 ])
AC_CHECK_SIZEOF(long,      [ 4 ])
AC_CHECK_SIZEOF(long long, [ 8 ])
AC_CHECK_SIZEOF(int *,     [ 4 ])

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_CLOSEDIR_VOID
AC_REPLACE_FNMATCH
AC_FUNC_FORK
AC_FUNC_GETPGRP
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_UTIME_NULL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([alarm bzero endpwent fchdir getcwd gethostname getpass gettimeofday lchown memchr memmove memset mkdir nl_langinfo putenv rmdir select setlocale strcasecmp strchr strcspn strdup strerror strncasecmp strrchr strspn strstr strtol strtoul tzset utime gettext iconv])

#-----------------------------------------------------------------------
# Check for dlopen support
#-----------------------------------------------------------------------
AC_CHECK_FUNCS(dlopen, [ found=y ], [ found=n ])
if test $found = n; then
    AC_CHECK_LIB(dl, dlopen,
        [ found=y; DL_LIB=-ldl; AC_DEFINE(HAVE_DLOPEN) ], [ found=n ])
fi

if test $found = n; then
    AC_CHECK_FUNCS(shl_load, [ found=y ], [ found=n ])
fi
if test $found = n; then
    for f in dl dld; do
        AC_CHECK_LIB($f, shl_load,
            [ found=y; DL_LIB="-l$f"
              AC_DEFINE(HAVE_SHL_LOAD) ], [ found=n ])
        test $found = y && break
    done
fi
AC_SUBST(DL_LIB)

#-----------------------------------------------------------------------
# Check for oxim's lib
#-----------------------------------------------------------------------
AC_CHECK_LIB(oxim, oxim_version, [ found=y ], [ AC_MSG_ERROR([require liboxim missing]) ])

#-----------------------------------------------------------------------
# Check for XPM support
#-----------------------------------------------------------------------
PKG_CHECK_MODULES(XPM, xpm >= 2.0.0, use_xpm="yes", use_xpm="no")
if test "$use_xpm" = "no" ; then
    AC_CHECK_HEADERS([X11/xpm.h], [use_xpm="yes"], [use_xpm="no"])
    if test "$use_xpm" = "yes" ; then
	XPM_CFLAGS=""
	AC_SUBST(XPM_CFLAGS)
	XPM_LIBS="-lX11 -lXpm"
	AC_SUBST(XPM_LIBS)
    else
	AC_MSG_ERROR([required XPM header file missing])
    fi
fi

#-----------------------------------------------------------------------
# Check for libglade support
#-----------------------------------------------------------------------
PKG_CHECK_MODULES(GLADE, libglade-2.0 >= 2.0, use_libglade="yes", use_libglade="no")
if test "$use_libglade" = "yes" ; then
	GLADE_CFLAGS=`$PKG_CONFIG --cflags libglade-2.0 gtk+-2.0 gmodule-2.0 glib-2.0 libxml-2.0 gobject-2.0` 
	GLADE_LIBS=`$PKG_CONFIG --libs libglade-2.0 gtk+-2.0 gmodule-2.0 glib-2.0 libxml-2.0 gobject-2.0`
	AC_SUBST(GLADE_CFLAGS)
	AC_SUBST(GLADE_LIBS)
else
	AC_MSG_ERROR([required libglade missing])
fi

#-----------------------------------------------------------------------
# Check for curl support
#-----------------------------------------------------------------------
PKG_CHECK_MODULES(CURL, libcurl >= 7.15, use_libcurl="yes", use_libcurl="no")
if test "$use_libcurl" = "no" ; then
        AC_CHECK_HEADERS([curl/curl.h], [use_libcurl="yes"], [use_libcurl="no"])
        if test "$use_libcurl" = "yes" ; then
		CURL_CFLAGS=`$PKG_CONFIG --cflags libcurl` 
		CURL_LIBS=`$PKG_CONFIG --libs libcurl`
		AC_SUBST(CURL_CFLAGS)
		AC_SUBST(CURL_LIBS)
	else
		AC_MSG_ERROR([required libcurl missing])
	fi
fi

#-----------------------------------------------------------------------
# Check for Xft support
#-----------------------------------------------------------------------
PKG_CHECK_MODULES(XFT, xft >= 2.0, use_xft="yes", use_xft="no")
if test "$use_xft" = "no" ; then
    AC_MSG_ERROR([oxim need libxft, but not found or version too old.])
fi

#-----------------------------------------------------------------------
#  Check for Gtk2 Library ***
#-----------------------------------------------------------------------
AC_ARG_ENABLE([gtk-immodule],
    AS_HELP_STRING(
        [--enable-gtk-immodule],
        [Enable build gtk2 input method extension (default=auto)]),
        [],
        [enable_gtk_immodule="yes"])

if test "$enable_gtk_immodule" = "yes" ; then
    PKG_CHECK_MODULES(GTK2, gtk+-2.0 >= 2.2.0, use_gtk2="yes", use_gtk2="no")
    if test "$use_gtk2" = "no" ; then
	AC_MSG_WARN([Gtk2 version must be > 2.2.0!])
	enable_gtk_immodule="no"
    fi
    GTK_IM_MODULE_DIR=`$PKG_CONFIG gtk+-2.0 --variable=libdir`/gtk-2.0/immodules
    AC_SUBST(GTK_IM_MODULE_DIR)
fi
AM_CONDITIONAL(ENABLE_GTK_IMMODULE, [ test "$enable_gtk_immodule" = "yes" ])

#-----------------------------------------------------------------------
#  Check for QT3 Library ***
#-----------------------------------------------------------------------
PKG_CHECK_MODULES(QT3, qt-mt >= 3.1, use_qt3="yes", use_qt3="no")
if test "$use_qt3" = "no" ; then
    AC_MSG_WARN([Can not find QT3 development packages.])
fi

#-----------------------------------------------------------------------
#  Check for QT4 Library ***
#-----------------------------------------------------------------------
PKG_CHECK_MODULES(QT4, qt-mt >= 3.1, use_qt4="yes", use_qt4="no")
if test "$use_qt4" = "no" ; then
    AC_MSG_WARN([Can not find QT4 development packages.])
fi
#-----------------------------------------------------------------------
# Check for OXZilla support
#-----------------------------------------------------------------------
#PKG_CHECK_MODULES(OXZILLA, oxzilla >= 0.1.1, use_oxzilla="yes", use_oxzilla="no")
#if test "$use_oxzilla" = "no" ; then
   # AC_MSG_ERROR([oxim-setup-oxzilla need oxzilla, but not found or version too old.])
#fi

#-----------------------------------------------------------------------
# GUI Setup tool (USE QT Library)
#-----------------------------------------------------------------------
AC_ARG_ENABLE([qt-immodule],
    AS_HELP_STRING(
        [--enable-qt-immodule],
        [Enable build QT input method extension (default=auto)]),
        [],
        [enable_qt_immodule="yes"])

AC_ARG_WITH([qt-dir],
    AS_HELP_STRING(
    	[--with-qt-dir=PATH],
	[set the install root of QT libraries (default=$QTDIR)]),
	[test x$withval != x && qt_dir="$withval"],
	[qt_dir="$QTDIR"])

AC_ARG_WITH([qt-imdir],
    AS_HELP_STRING(
    	[--with-qt-imdir=PATH],
	[set the QT3 input methods directory]),
	[test x$withval != x && qt_imdir="$withval"],
	[qt_imdir="$QTDIR/plugins/inputmethods"])

AC_ARG_ENABLE([setup-qt3],
    AS_HELP_STRING(
        [--enable-setup-qt3],
        [Enable build GUI setup tool QT3(default=yes)]),
        [],
        [enable_setup_qt3="yes"])

AC_ARG_ENABLE([setup-qt4],
    AS_HELP_STRING(
        [--enable-setup-qt4],
        [Enable build GUI setup tool QT4(default=yes)]),
        [],
        [enable_setup_qt4="yes"])

AC_ARG_ENABLE([setup-php],
    AS_HELP_STRING(
        [--enable-setup-php],
        [Enable build GUI setup tool PHP-GTK 2(default=yes)]),
        [],
        [enable_setup_php="yes"])
AM_CONDITIONAL(ENABLE_SETUP_PHP, [ test "$enable_setup_php" = "yes" ])

AC_ARG_ENABLE([setup-java],
    AS_HELP_STRING(
        [--enable-setup-java],
        [Enable build GUI setup tool JAVA-GTK 2(default=yes)]),
        [],
        [enable_setup_java="yes"])
AM_CONDITIONAL(ENABLE_SETUP_JAVA, [ test "$enable_setup_java" = "yes" ])

AC_ARG_ENABLE([setup-oxzilla],
    AS_HELP_STRING(
        [--enable-setup-oxzilla],
        [Enable build GUI setup tool OXZILLA-GTK 2(default=yes)]),
        [],
        [enable_setup_oxzilla="yes"])
AM_CONDITIONAL(ENABLE_SETUP_OXZILLA, [ test "$enable_setup_oxzilla" = "yes" ])

AC_ARG_ENABLE([setup-gtk],
    AS_HELP_STRING(
        [--enable-setup-gtk],
        [Enable build GUI setup tool GTK 2(default=yes)]),
        [],
        [enable_setup_gtk="yes"])
AM_CONDITIONAL(ENABLE_SETUP_GTK, [ test "$enable_setup_gtk" = "yes" ])

AC_ARG_ENABLE([setup-gambas],
    AS_HELP_STRING(
        [--enable-setup-gambas],
        [Enable build GUI setup tool Gambas(default=yes)]),
        [],
        [enable_setup_gambas="yes"])
AM_CONDITIONAL(ENABLE_SETUP_GAMBAS, [ test "$enable_setup_gambas" = "yes" ])

AC_ARG_ENABLE([setup-pygtk],
    AS_HELP_STRING(
        [--enable-setup-pygtk],
        [Enable build GUI setup tool PyGTK(default=yes)]),
        [],
        [enable_setup_pygtk="yes"])

AM_CONDITIONAL(ENABLE_SETUP_PYGTK, [ test "$enable_setup_pygtk" = "yes" ])

AC_ARG_ENABLE([setup-oxzilla],
    AS_HELP_STRING(
        [--enable-setup-oxzilla],
        [Enable build GUI setup tool OXZILLA-GTK 2(default=yes)]),
        [],
        [enable_setup_oxzilla="yes"])
AM_CONDITIONAL(ENABLE_SETUP_OXZILLA, [ test "$enable_setup_oxzilla" = "yes" ])

if test "$enable_setup_qt3" = "yes" || test "$enable_qt_immodule" = "yes" ; then
    have_qmake="no"
    have_uic="no"
    have_moc="no"
    have_qinputcontextplugin="no"

    AC_MSG_CHECKING([for qmake])
    if test -f ${qt_dir}/bin/qmake ; then
	AC_MSG_RESULT(${qt_dir}/bin/qmake)
	have_qmake="yes"
    else
	AC_MSG_RESULT([not found!])
    fi

    AC_MSG_CHECKING([for uic])
    if test -f ${qt_dir}/bin/uic ; then
	AC_MSG_RESULT(${qt_dir}/bin/uic)
	have_uic="yes"
    else
	AC_MSG_RESULT([not found!])
    fi

    AC_MSG_CHECKING([for moc])
    if test -f ${qt_dir}/bin/moc ; then
	AC_MSG_RESULT(${qt_dir}/bin/moc)
	have_moc="yes"
    else
	AC_MSG_RESULT([not found!])
    fi

    if test "$enable_qt_immodule" = "yes"
    then
	AC_MSG_CHECKING([for qinputcontextplugin.h])
	if test -f ${qt_dir}/include/qinputcontextplugin.h ; then
	    AC_MSG_RESULT(${qt_dir}/include/qinputcontextplugin.h)
	    have_qinputcontextplugin="yes"
	    QT_IM_MODULE_DIR="${qt_imdir}"
	    AC_SUBST(QT_IM_MODULE_DIR)
	else
	    AC_MSG_RESULT([not found!])
	    enable_qt_immodule="no"
	fi
    fi

    if test $have_qmake = "no" || test $have_uic = "no" || test $have_moc = "no"
    then
	AC_MSG_ERROR([Can't find QT build tools! Plese set with-qt-dir="Your QT install root PATH"])
    fi

    QTDIR="$qt_dir"
    AC_SUBST(QTDIR)
fi
AM_CONDITIONAL(ENABLE_QT_IMMODULE, [ test "$enable_qt_immodule" = "yes" ])
AM_CONDITIONAL(ENABLE_SETUP_QT3, [ test "$enable_setup_qt3" = "yes" ])
AM_CONDITIONAL(ENABLE_SETUP_QT4, [ test "$enable_setup_qt4" = "yes" ])

#-----------------------------------------------------------------------
# 
#-----------------------------------------------------------------------
#OXZILLA_JSPLUGIN_DIR=`$PKG_CONFIG --variable=jsplugindir oxzilla`
#AC_SUBST(OXZILLA_JSPLUGIN_DIR)
OXIMSETUP_DEFAULT_DIR=${libdir}/oxim-setup
AC_SUBST(OXIMSETUP_DEFAULT_DIR)
OXIMSETUP_QT3_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-qt3
AC_SUBST(OXIMSETUP_QT3_DIR)
OXIMSETUP_QT4_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-qt4
AC_SUBST(OXIMSETUP_QT4_DIR)
OXIMSETUP_PHP_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-php
AC_SUBST(OXIMSETUP_PHP_DIR)
OXIMSETUP_JAVA_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-java
AC_SUBST(OXIMSETUP_JAVA_DIR)
OXIMSETUP_GAMBAS_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-gambas
AC_SUBST(OXIMSETUP_GAMBAS_DIR)
OXIMSETUP_GTK_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-gtk
AC_SUBST(OXIMSETUP_GTK_DIR)
OXIMSETUP_PYGTK_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-pygtk
AC_SUBST(OXIMSETUP_PYGTK_DIR)
OXIMSETUP_OXZILLA_DIR=${OXIMSETUP_DEFAULT_DIR}/oxim-setup-oxzilla
AC_SUBST(OXIMSETUP_OXZILLA_DIR)

#OXIMSETUP_GTK_DATA_DIR=${datadir}/oxim-setup-gtk
#AC_SUBST(OXIMSETUP_GTK_DATA_DIR)

#-----------------------------------------------------------------------
# 
#-----------------------------------------------------------------------
AC_OUTPUT(Makefile \
	  src/utils/Makefile \
	  src/oxim-setup-gtk/Makefile \
	  src/oxim-setup-qt3/Makefile \
	  src/oxim-setup-qt4/Makefile \
	  src/oxim-setup-php/Makefile \
	  src/oxim-setup-java/Makefile \
	  src/oxim-setup-gambas/Makefile \
	  src/oxim-setup-pygtk/Makefile \
	  src/oxim-setup-oxzilla/Makefile \
	  po/Makefile.in \
	  src/utils/oxim-setup \
	  src/oxim-setup-php/src/oxim-setup.glade \
	  src/oxim-setup-gtk/gui/oxim-setup-glade.xml	  
	 )

AC_MSG_RESULT([
Build options:
  Version		$VERSION
  Install prefix	$prefix

Optional:
  Setup PHP-GTK	program	$enable_setup_php
  Setup QT3	program	$enable_setup_qt3
  Setup GTK	program	$enable_setup_gtk
  Setup Gambas	program $enable_setup_gambas
  Setup PyGTK	program $enable_setup_pygtk
  Setup QT4	program	$enable_setup_qt4
  Setup JAVA	program	$enable_setup_java
  Setup OXZILLA	program	$enable_setup_oxzilla
])
