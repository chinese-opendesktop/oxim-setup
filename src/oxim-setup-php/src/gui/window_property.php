<?php
//按下『屬性』按鈕
function callback_PropertyWindow_clicked($button)
{
	global $wProperty, $wChewingProperty;
	global $aTableInfos;
	
	$path = get_tree_path();
	$aTabSettings = $aTableInfos[$path]['TabSettings'];
	if($aTableInfos[$path]['EngName']=='chewing')
	{
		ChewingPropertyWindow_open();	//開啟新酷音屬性視窗
	}
	else
	{
		//輸入法名稱
		$wProperty->get_widget("label18")->set_text(
			!empty($aTabSettings['AliasName']) ?
				$aTabSettings['AliasName'] : $aTableInfos[$path]['ChiName']
		);

		_setSettingValues($aTabSettings);
		
		$wProperty->get_widget("PropertyWindow")->set_visible(true);	//開啟屬性視窗
	}
}

//to set value
function callback_PropertyWindow_WriteSettings($button)
{
	global $wProperty;
	global $aTableInfos;
	
	$path = get_tree_path();
	foreach(
		array(
			'AutoCompose',
			'AutoUpChar',
			'AutoFullUp',
			'SpaceAutoUp',
			'SelectKeyShift',
			'SpaceReset',
			'WildEnable',
			'EndKey'
		)
		as $field
	)
	{
		$aTableInfos[$path]['TabSettings'][$field] = $wProperty->get_widget($field)->get_active() ? 'Yes' : 'No';
	}
	
	$aTableInfos[$path]['TabSettings']['DisableSelectList'] = 
		trim($wProperty->get_widget('DisableSelectList')->get_text())=="" ? 
			'None' : $wProperty->get_widget('DisableSelectList')->get_text();
			
	$aTableInfos[$path]['TabSettings']['SpaceIgnore'] = $wProperty->get_widget('SpaceIgnore0')->get_active() ? 'Yes' : 'No';
	
	$wProperty->get_widget("PropertyWindow")->set_visible(false);
}

//設成預設值
function callback_PropertyWindow_setDefault($button)
{
	_setSettingValues(
		array(
			'AutoCompose'=>'Yes',
			'AutoUpChar'=>'Yes',
			'AutoFullUp'=>'No',
			'SpaceAutoUp'=>'No',
			'SelectKeyShift'=>'No',
			'SpaceIgnore'=>'No',
			'SpaceReset'=>'Yes',
			'WildEnable'=>'Yes',
			'EndKey'=>'Yes',
			'DisableSelectList'=>'None'
		)
	);
}

//切換設定狀態值
function _setSettingValues($aTabSettings)
{
	global $wProperty;
	
	//自動組字設定、萬用組字功能、空白鍵自動清除、空白鍵自動出字、選字鍵後移一位、按結束鍵出字
	foreach(array('AutoCompose','WildEnable','SpaceReset','SpaceAutoUp','SelectKeyShift','EndKey') as $key)
	{
		$wProperty->get_widget($key)->set_active(
			strtolower($aTabSettings[$key])=="yes" ?
				true : false
		);
	}

	//自動出字模式
	$bSwitch = strtolower($aTabSettings['AutoUpChar'])=="yes" ? true : false;
	$wProperty->get_widget('AutoUpChar')->set_active($bSwitch);
	$wProperty->get_widget('SpaceAutoUp')->set_sensitive($bSwitch);
	$wProperty->get_widget('SelectKeyShift')->set_sensitive($bSwitch);
	
	//滿字根自動出字
	$bSwitch = strtolower($aTabSettings['AutoFullUp'])=="yes" ? true : false;
	$wProperty->get_widget('SpaceIgnore0')->set_sensitive($bSwitch);
	$wProperty->get_widget('SpaceIgnore1')->set_sensitive($bSwitch);
	if(strtolower($aTabSettings['SpaceIgnore'])=="yes")
	{
		$wProperty->get_widget('SpaceIgnore0')->set_active($bSwitch);
	}
	else
	{
		$wProperty->get_widget('SpaceIgnore1')->set_active($bSwitch);
	}
	
	//特殊字根
	if($aTabSettings["DisableSelectList"]!="None")
	{
		$wProperty->get_widget('DisableSelectList')->set_text($aTabSettings['DisableSelectList']);
	}
	else
	{
		$wProperty->get_widget('DisableSelectList')->set_text("");
	}

}

//自動出字模式切換時
function callback_PropertyWindow_AutoUpChar_toggled($togglebutton)
{
	global $wProperty;
	$bSwitch = $togglebutton->get_active();
	$wProperty->get_widget('SpaceAutoUp')->set_sensitive($bSwitch);
	$wProperty->get_widget('SelectKeyShift')->set_sensitive($bSwitch);
}

//滿字根出字模式切換時
function callback_PropertyWindow_AutoFullUp_toggled($togglebutton)
{
	global $wProperty;
	$bSwitch = $togglebutton->get_active();
	$wProperty->get_widget('SpaceIgnore0')->set_sensitive($bSwitch);
	$wProperty->get_widget('SpaceIgnore1')->set_sensitive($bSwitch);
}

//『取消』
function callback_PropertyWindow_CancelButton_clicked($button)
{
	global $wProperty;
	$wProperty->get_widget("PropertyWindow")->set_visible(false);
}
?>