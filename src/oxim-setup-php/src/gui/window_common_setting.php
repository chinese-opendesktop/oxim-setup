<?php
//從combobox元件取得[123456789]的陣列
function CommonSettingWindow_get_key_map()
{
	global $wCommonSetting;
	$aKeyMap = array();
	
	$oModel = $wCommonSetting->get_widget("combobox1")->get_model();
	$oIter = $oModel->get_iter_first();
	$i = 0;
	while(!is_null($oIter))
	{
		$aKeyMap[$oModel->get_value($oIter, 0)] = $i++;
		$oIter = $oModel->iter_next($oIter);
	}
	return $aKeyMap;
}

//開啟通用設定視窗
function callback_CommonSettingWindow_clicked($button)
{
	global $wMain, $wCommonSetting;
	global $aTableInfos, $aSettings;

	$path = get_tree_path();
	$aTableInfo = $aTableInfos[$path];
	$aTabSettings = $aTableInfo['TabSettings'];
	
	//名稱
	$wCommonSetting->get_widget("NameLabel")->set_text($aTableInfo['ChiName']);
	
	//別名
	$wCommonSetting->get_widget("AliasEntry")->set_text(
		isset($aTabSettings['AliasName']) ? 
			$aTabSettings['AliasName'] : ""
	);
	
	//按鍵組合
	if(!isset($aTabSettings['SetKey']))
	{
		$wCommonSetting->get_widget("checkbutton1")->set_active(false);
		$wCommonSetting->get_widget("combobox1")->set_active(0);
		$wCommonSetting->get_widget("combobox1")->set_sensitive(false);
	}
	else
	{
		$aKeyMap = CommonSettingWindow_get_key_map();
		$wCommonSetting->get_widget("checkbutton1")->set_active(true);
		$wCommonSetting->get_widget("combobox1")->set_active($aKeyMap[$aTabSettings['SetKey']]);
		$wCommonSetting->get_widget("combobox1")->set_sensitive(true);
	}

	$wCommonSetting->get_widget("CommonSettingWindow")->set_visible(true);
}

//『確定』
function callback_CommonSettingWindow_OkButton_clicked($button)
{
	global $wCommonSetting, $wMsgDialog;
	global $aTableInfos;
	
	$bFound = false;
	$aKeyMap = array_flip(CommonSettingWindow_get_key_map());
	$path = get_tree_path();
	foreach($aTableInfos as $i=>$aTableInfo)
	{
		if(isset($aTableInfo['TabSettings']['SetKey']))
		{
			if( $path!=$i &&
			    ($aTableInfo['TabSettings']['SetKey']==$aKeyMap[$wCommonSetting->get_widget("combobox1")->get_active()]) &&
			    ($wCommonSetting->get_widget("checkbutton1")->get_active()) )
			{
				$bFound = true;
			}
		}
	}
	if($bFound)
	{
		$wMsgDialog->get_widget("label")->set_text( _("The key you choose had used by other Input-Method!\n")._("Re-Select another key, please.") );
		$wMsgDialog->get_widget("MsgDialog")->set_visible(true);
		return;
	}
	
	$path = get_tree_path();
	$aTabSettings = $aTableInfos[$path]['TabSettings'];
	
	//設定『別名』
	$aTableInfos[$path]['TabSettings']['AliasName'] = $wCommonSetting->get_widget("AliasEntry")->get_text();
	//設定按鍵組合
	if($wCommonSetting->get_widget("checkbutton1")->get_active())
	{
		$aTableInfos[$path]['TabSettings']['SetKey'] = $aKeyMap[$wCommonSetting->get_widget("combobox1")->get_active()];
	}
	
	$wCommonSetting->get_widget("CommonSettingWindow")->set_visible(false);
	reload_tables_treeview();
}

//『取消』
function callback_CommonSettingWindow_CancelButton_clicked($button)
{
	global $wCommonSetting;
	$wCommonSetting->get_widget("CommonSettingWindow")->set_visible(false);
}

//『使用按鍵組合』打勾
function callback_CommonSettingWindow_checkbutton1_clicked($checkbutton)
{
	global $wCommonSetting;
	$wCommonSetting->get_widget("combobox1")->set_sensitive($checkbutton->get_active());
}
?>
