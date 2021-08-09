<?php
//設定某輸入法為『預設』
function callback_DefaultButton_clicked($button)
{
	global $aTableInfos, $aSettings;
	
	$path = get_tree_path();
	$aSettings['DefauleInputMethod'] = $aTableInfos[$path]['EngName'];
	reload_tables_treeview();
}
?>