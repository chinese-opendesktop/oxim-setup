#!/usr/bin/env php
<?php
error_reporting(0);

setlocale(LC_ALL, null);
textdomain("oxim-setup");
$basedir = dirname(__FILE__);
include_once("$basedir/init.php");

if(true)
{
	$needle = __FILE__;
// 	$needle = basename($needle);
// 	$sRst = shell_exec("ps x|grep -e \"php $needle\"");
 	$sRst = shell_exec("ps x|grep -e \"$needle\"");
	if(substr_count($sRst, "php $needle")>1)
	{
		exit;
	}
}
if(false)
{
$tmplockfile = sys_get_temp_dir()."/oximsetupphp";
if(file_exists($tmplockfile) && posix_getpgid(intval(file_get_contents($tmplockfile))) )
{
	echo "still running(".posix_getpgid(intval(file_get_contents($tmplockfile))).")";
	exit;
}
else
{
	$fp = fopen($tmplockfile, "w");
	fwrite($fp, posix_getpid());
	fclose($fp);
}
}

global $wMain, $wCommonSetting, $wMsgDialog, $wChewingProperty, $wProperty, $wInstallTab, $wProgress;
global $aTableInfos, $aSettings;
global $sRemoteCinUrl;

//主視窗
$wMain = new GladeXML("$basedir/oxim-setup.glade");
$wMain->signal_autoconnect();
$a = new GtkImage();
$a->set_from_pixbuf(GdkPixBuf::new_from_file("$basedir/images/cd01.png"));
$wMain->get_widget("DefaultButton")->set_image($a);
$wMain->get_widget("label28")->modify_font(new PangoFontDescription(14));
//通用輸入法設定視窗
$wCommonSetting = new GladeXML("$basedir/oxim-setup.glade", "CommonSettingWindow");
$wCommonSetting->signal_autoconnect();
//訊息視窗
$wMsgDialog = new GladeXML("$basedir/oxim-setup.glade", "MsgDialog");
$wMsgDialog->signal_autoconnect();
//新酷音屬性視窗
$wChewingProperty = new GladeXML("$basedir/oxim-setup.glade", "ChewingPropertyWindow");
$wChewingProperty->signal_autoconnect();
//屬性視窗
$wProperty = new GladeXML("$basedir/oxim-setup.glade", "PropertyWindow");
$wProperty->signal_autoconnect();
//安裝輸入法視窗
$wInstallTab = new GladeXML("$basedir/oxim-setup.glade", "InstallTabWindow");
$wInstallTab->signal_autoconnect();
//進度條視窗
$wProgress = new GladeXML("$basedir/oxim-setup.glade", "ProgressWindow");
$wProgress->signal_autoconnect();


//$wMain->get_widget("label25")->set_text(str_replace(array("</font>","<font color=\"#5555ff\">"), "", $wMain->get_widget("label25")->get_text()));
$aTableInfos = get_table_infos();	//輸入法參考檔列表
$aSettings = get_settings();	//輸入法設定值 oxim.conf

setup_font_tab();
setup_phrse_treeview();
setup_tables_treeview();
//Start the main loop
Gtk::main();

if(false)
    unlink($tmplockfile);
?>
