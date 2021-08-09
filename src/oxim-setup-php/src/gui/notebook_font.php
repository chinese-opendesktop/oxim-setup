<?php
function setup_font_tab()
{
	global $wMain;
	global $aSettings;
	
	$fontbutton = $wMain->get_widget("FontButton");
	$fontbutton->set_font_name($aSettings['DefaultFontName']." ".$aSettings['DefaultFontSize']);
// 	$fontbutton->set_show_size($aSettings['DefaultFontSize']);

	$wMain->get_widget("PreeditFont")->set_value($aSettings['PreeditFontSize']);
	$wMain->get_widget("SelectFont")->set_value($aSettings['SelectFontSize']);
	$wMain->get_widget("StatusFont")->set_value($aSettings['StatusFontSize']);
	$wMain->get_widget("MenuFont")->set_value($aSettings['MenuFontSize']);
	$wMain->get_widget("SymbolFont")->set_value($aSettings['SymbolFontSize']);
	$wMain->get_widget("XcinFont")->set_value($aSettings['XcinFontSize']);
}
?>