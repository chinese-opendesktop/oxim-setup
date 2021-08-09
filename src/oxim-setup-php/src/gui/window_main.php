<?php
//將設定資料存回檔案
function commit_data($button)
{
	global $wMain;
	global $aTableInfos, $aSettings;
	
	//片語
	$fp = fopen(_PHARSE_FILE_, "w");
	$model = $wMain->get_widget("TreePhrse")->get_model();
	$iter = $model->get_iter_first();
	do
	{
		fwrite($fp, sprintf("%s \"%s\"", $model->get_value($iter, 0), trim($model->get_value($iter, 1)) ));
		$iter = $model->iter_next($iter);
		fwrite($fp, "\n");
	}
	while(!is_null($iter));
	fclose($fp);
	
	//字型、大小、顏色
	$fp = fopen(_USER_OXIM_CONFIG_FILE_, "w");
	list($aSettings['DefaultFontName'], $aSettings['DefaultFontSize']) = split(" ", $wMain->get_widget("FontButton")->get_font_name(), 2);
	$aSettings['PreeditFontSize'] = $wMain->get_widget("PreeditFont")->get_value();
	$aSettings['SelectFontSize'] = $wMain->get_widget("SelectFont")->get_value();
	$aSettings['StatusFontSize'] = $wMain->get_widget("StatusFont")->get_value();
	$aSettings['MenuFontSize'] = $wMain->get_widget("MenuFont")->get_value();
	$aSettings['SymbolFontSize'] = $wMain->get_widget("SymbolFont")->get_value();
	$aSettings['XcinFontSize'] = $wMain->get_widget("XcinFont")->get_value();
	fwrite($fp, "<SystemSetting>\n");
	foreach($aSettings as $k=>$v)
	{
		fwrite($fp, "\t$k = \"$v\"\n");
	}
	fwrite($fp, "</SystemSetting>\n");
	
	fwrite($fp, "\n");
	
	//輸入法設定
	$i = 1;
	foreach($aTableInfos as $aTableInfo)
	{
		fwrite($fp, sprintf("#\n# %s\n#\n", $aTableInfo['ChiName']));
		fwrite($fp, sprintf("<InputMethod \"%s\">\n", $aTableInfo['EngName']));
		
		$aTabSettings = $aTableInfo['TabSettings'];
		{
			foreach($aTabSettings as $k=>$v)
			{
				fwrite($fp, "\t$k = \"$v\"\n");
			}
		}
		fwrite($fp, "</InputMethod>\n");
		if(count($aTableInfos)>$i)
		{
			fwrite($fp, "\n");
		}
		$i++;
	}
	fclose($fp);
	oxim_reload();
	
	Gtk::main_quit();
}

?>