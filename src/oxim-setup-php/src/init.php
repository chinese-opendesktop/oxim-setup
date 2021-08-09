<?php
/*
*前導程式
*/

if (!extension_loaded('php-gtk')) {
    if(!dl("php_gtk2.so"))
	exit(1);
}
if (!extension_loaded('zlib')) {
    echo "The zlib module is not available!\r\n";
    exit(1);
}

define("_LOCALE_", setlocale(LC_ALL, null));
define("_OXIM_RELOAD_PROGRAM_", "oxim-agent -r");
define("_LIB_OXIM_DIR_", "/usr/lib/oxim/modules");
define("_BASE_DIR_", $basedir);
define("_IMAGES_DIR_", $basedir."/images");
define("_HOME_DIR_", getenv("HOME"));
define("_PHARSE_DIR_", _HOME_DIR_."/.oxim/tables");
define("_PHARSE_FILE_", _PHARSE_DIR_."/default.phr");
define("_USER_TABLE_DIR_", _HOME_DIR_."/.oxim/tables");
define("_DEFAULT_TABLE_DIR_", "/usr/lib/oxim/tables");
define("_DEFAULT_OXIM_CONFIG_FILE_", "/etc/oxim/oxim.conf");
define("_USER_OXIM_CONFIG_FILE_", _HOME_DIR_."/.oxim/oxim.conf");
define("_OXIM_MIRROR_SITE_URL_", "http://opendesktop.org.tw");
define("_CIN_LIST_FILE_NAME_", "cin.list");
define("_USER_CIN_LIST_FILE_", _HOME_DIR_."/.oxim/"._CIN_LIST_FILE_NAME_);
define("_USER_MIRRORS_SITE_FILE_", _HOME_DIR_."/.oxim/mirrors.site");
define("_WWW_MIRRORS_SITE_FILE_", _OXIM_MIRROR_SITE_URL_."/mirrors.site");
if(getenv("EXTERNAL_DOWNLOAD_URL")!='')
	define("_EXTERNAL_DOWNLOAD_URL_", getenv("EXTERNAL_DOWNLOAD_URL"));

include_once("$basedir/lib/libs.php");
include_once("$basedir/lib/default_phr.php");
include_once("$basedir/lib/tab_reader.php");
include_once("$basedir/lib/net_cin_table.php");
include_once("$basedir/gui/notebook_font.php");
include_once("$basedir/gui/treeview_pharse.php");
include_once("$basedir/gui/treeview_tables.php");
include_once("$basedir/gui/notebook_tables.php");
include_once("$basedir/gui/window_common_setting.php");
include_once("$basedir/gui/msg_dialog.php");
include_once("$basedir/gui/window_main.php");
include_once("$basedir/gui/window_chewing_property.php");
include_once("$basedir/gui/window_property.php");
include_once("$basedir/gui/window_install_tab.php");
?>
