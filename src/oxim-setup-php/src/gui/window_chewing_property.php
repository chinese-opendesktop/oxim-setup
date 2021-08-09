<?php
//開啟『新酷音輸入法屬性』視窗
function ChewingPropertyWindow_open()
{
	global $wChewingProperty;
	global $aTableInfos;
	$path = get_tree_path();
	$aTabSettings = $aTableInfos[$path]['TabSettings'];

	//鍵盤對應
	$wChewingProperty->get_widget("KeyMap".$aTabSettings['KeyMap'])->set_active(true);
	//選字鍵
	$wChewingProperty->get_widget("SelectionKeys".$aTabSettings['SelectionKeys'])->set_active(true);
	//CapsLock輸出
	$wChewingProperty->get_widget("CapsLockMode".$aTabSettings['CapsLockMode'])->set_active(true);

	$wChewingProperty->get_widget("ChewingPropertyWindow")->set_visible(true);
}

//按下『確定』之後
function callback_ChewingPropertyWindow_accept($button)
{
	global $wChewingProperty;
	global $aTableInfos;
	$path = get_tree_path();

	foreach(array('KeyMap','SelectionKeys','CapsLockMode') as $key)
	{
		foreach($wChewingProperty->get_widget($key."0")->get_group() as $v)
		{
			if($v->get_active())
			{
				$aTableInfos[$path]['TabSettings'][$key] = str_replace($key, "", $v->get_name());
			}
		}
	}
	$wChewingProperty->get_widget("ChewingPropertyWindow")->set_visible(false);
}

//『取消』
function callback_ChewingPropertyWindow_CancelButton_clicked($button)
{
	global $wChewingProperty;
	$wChewingProperty->get_widget("ChewingPropertyWindow")->set_visible(false);
}

?>