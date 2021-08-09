<?php
//取得網路上的mirrors.site列表
function get_mirror_sites()
{
	$aMirrorSites = array();
	$sContent = file_get_contents(_USER_MIRRORS_SITE_FILE_);
	if(preg_match_all("/\"(.*)\" *= *\"(.*)\"/", $sContent, $matches))
	{
		for($i=0; $i<count($matches[0]); $i++)
		{
			$aMirrorSites[$i]['title'] = $matches[1][$i];
			$aMirrorSites[$i]['url'] = $matches[2][$i];
		}
	}
	return $aMirrorSites;
}

//取得網路上的cin.list輸入法列表
function get_cin_lists()
{
	$bShowChn = (substr(_LOCALE_, 0, 2)=="zh") ? true : false;
	$aCinLists = array();
	$sContent = file_get_contents(_USER_CIN_LIST_FILE_);
	if(preg_match_all("/Language *= *\"([^=]*\")/sm", $sContent, $matches))
	{
		foreach($matches[1] as $sSubContent)
		{
			$aCinList = array();
			//test_pattern:中文(繁體)xxx
			if(preg_match("/(.*),(.*)\"/", $sSubContent, $sub_matches))
			{
				if($bShowChn)
				{
					$aCinList['language'] = $sub_matches[1];
				}
				else
				{
					$aCinList['language'] = $sub_matches[2];
				}
			}
			//test_pattern:3corner.cin.gz,"3Corner(三角編號)","胡立人﹑張源渭﹑黃克東發明的三角編號輸入法;Three Corner Code"
			if(preg_match_all("/(.*),\"(.*)\",\"(.*);(.*)\"/", $sSubContent, $sub_matches))
			{
				for($i=0; $i<count($sub_matches[0]); $i++)
				{
					$aCinList['info'][$i]['file'] = $sub_matches[1][$i];
					$aCinList['info'][$i]['name'] = $sub_matches[2][$i];
					if($bShowChn)
					{
						$aCinList['info'][$i]['description'] = $sub_matches[3][$i];
					}
					else
					{
						$aCinList['info'][$i]['description'] = $sub_matches[4][$i];
					}
					$aCinList['info'][$i]['local'] = is_remote_cin_in_local($aCinList['info'][$i]['file']);
				}
			}
			$aCinLists[] = $aCinList;
		}
	}
	return $aCinLists;
}

//檢查cin檔有沒有下載過
function is_remote_cin_in_local($cin_filename)
{
	global $aTableInfos;
	
	foreach($aTableInfos as $aTableInfo)
	{
		if($aTableInfo['EngName']==basename($cin_filename, ".cin.gz"))
		{
			return true;
		}
	}
}
?>