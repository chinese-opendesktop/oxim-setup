<?php
/*
*取出該輸入法對照檔的中文名稱
*/
function get_table_info($full_tbl_file)
{
	$a = array();
	$header_format = "a7prefix/Cversion/a12dummy";
	$header_size = 20;
	$fp = gzopen($full_tbl_file, "rb");
	$preHeader = unpack("@0/$header_format", gzread($fp, $header_size));
	foreach($preHeader as $k=>$v)
	{
		$preHeader[$k] = strtok($v, "\0");
	}
	if($preHeader['prefix']!="gencin")
	{
		return null;
	}

	$header_format = "In_locale/Ilocale_table_offset/In_setting/Isetting_table_offset/In_input_content/Ioffset_table_offset/In_char/Ichar_offset/Iinput_content_offset/Cn_max_keystroke/Ckeep_key_case/a256orig_name/a256cname/Cn_key_name/a1024keyname/Cn_selection_key/a128selection_keys/Cn_end_key/a128end_keys/Vchksum";
	$header_size = 38 + 256 + 256 + 1 + 8*128 + 1 + 128 + 1 + 128 + 4;
	$tmp = gzread($fp, $header_size);
	$header = unpack("@0/$header_format", $tmp);
	foreach($header as $k=>$v)
	{
		$header[$k] = strtok($v, "\0");
	}
// 	printf("%u\n", crc32($tmp));
	
	$aParts = pathinfo($full_tbl_file);
	if(!isset($aParts['filename']))
	{
		$aParts['filename'] = substr($aParts['basename'], 0, strrpos($aParts['basename'], '.'));
	}
	$a['EngName'] = $aParts['filename'];
// 	$a['ChiName']  = strtok(gzread($fp, 256), "\0");
	$a['ChiName']  = get_cname($header['cname'], $header['orig_name']);
	$a['isDefaultTable'] = $aParts['dirname']==_USER_TABLE_DIR_ ? false : true;
	$a['TabSettings'] = get_table_settings($a['EngName']);
	gzclose($fp);
	
	return $a;
}

/*
*
*/
function get_table_infos()
{
	static $files;
	if(!isset($files))
	{
		$files = array();
		foreach(array(_USER_TABLE_DIR_, _DEFAULT_TABLE_DIR_) as $table_dir)
		{
			foreach(scandir($table_dir) as $filename)
			{
				$file_parts = pathinfo($filename);
				if(isset($file_parts['extension']))
				{
					if(!($filename=='.' || $filename=='..') && $file_parts['extension']=='tab')
					{
						$aInfo = get_table_info("$table_dir/$filename");
						if(!is_null(count($aInfo)))
						{
							$files[] = $aInfo;
						}
					}
				}
			}
		}
		if(file_exists(_LIB_OXIM_DIR_ . "/chewing.so"))
		{
			$files[] = array('EngName'=>'chewing', 'ChiName'=>_('chewing'), 'isDefaultTable'=>true, 'TabSettings'=>get_table_settings('chewing'));
		}
		if(file_exists(_LIB_OXIM_DIR_ . "/unicode.so"))
		{
			$files[] = array('EngName'=>'unicode', 'ChiName'=>_('Unicode'), 'isDefaultTable'=>true, 'TabSettings'=>get_table_settings('unicode'));
		}
	}
	return $files;
}

function get_table_settings($EngName)
{
	$aTabSettings = array();
	if(!($EngName=='chewing' || $EngName=='unicode'))
	{
		$aTabSettings = array(
			'Circular' => 'Yes',
			'AutoCompose' => "Yes",
			'AutoUpChar' => "Yes",
			'AutoFullUp' => "No",
			'SpaceAutoUp' => "No",
			'SelectKeyShift' => "No",
			'SpaceIgnore' => "Yes",
			'SpaceReset' => "Yes",
			'WildEnable' => "Yes",
			'EndKey' => "No",
			'DisableSelectList' => "None"
		);
	}
	
	if(file_exists(_DEFAULT_OXIM_CONFIG_FILE_))
	{
		$sContent = file_get_contents(_DEFAULT_OXIM_CONFIG_FILE_);
		if(preg_match("/<InputMethod \"$EngName\">([^\/]*)<\/InputMethod>/ms", $sContent, $matches))
		{
			$sSubContent = $matches[1];
			if(preg_match_all("/(\w*)\s+=\s+(\"{0,1}.*\"{0,1})/", $sSubContent, $sub_matches))
			{
				for($i=0; $i<count($sub_matches[0]); $i++)
				{
					$aTabSettings[$sub_matches[1][$i]] = str_replace("\"", "", $sub_matches[2][$i]);
				}
			}
		}
	}
	
	if(file_exists(_USER_OXIM_CONFIG_FILE_))
	{
		$sContent = file_get_contents(_USER_OXIM_CONFIG_FILE_);
		if(preg_match("/<InputMethod \"$EngName\">([^\/]*)<\/InputMethod>/ms", $sContent, $matches))
		{
			$sSubContent = $matches[1];
			if(preg_match_all("/(\w*)\s+=\s+(\"{0,1}.*\"{0,1})/", $sSubContent, $sub_matches))
			{
				for($i=0; $i<count($sub_matches[0]); $i++)
				{
					$aTabSettings[$sub_matches[1][$i]] = str_replace("\"", "", $sub_matches[2][$i]);
				}
				if(!in_array("AliasName", $sub_matches[1]))
				{
					$aTabSettings["AliasName"] = "";
				}
			}
		}
	}
	return $aTabSettings;
}

function insert_new_table_vars($eng_name, $chi_name)
{
	global $aTableInfos;
	
	$aTableInfos[] = array(
		'EngName'=>$eng_name,
		'ChiName'=>$chi_name,
		'isDefaultTable'=>false,
		'TabSettings'=>array(
			'Circular' => 'Yes',
			'AutoCompose' => "Yes",
			'AutoUpChar' => "Yes",
			'AutoFullUp' => "No",
			'SpaceAutoUp' => "No",
			'SelectKeyShift' => "No",
			'SpaceIgnore' => "Yes",
			'SpaceReset' => "Yes",
			'WildEnable' => "Yes",
			'EndKey' => "No",
			'DisableSelectList' => "None"
		)
	);
}

function remove_from_table_vars($eng_name)
{
	global $aTableInfos;
	
	foreach($aTableInfos as $key=>$aTableInfo)
	{
		if($eng_name==$aTableInfo['EngName'])
		{
			unset($aTableInfos[$key]);
		}
	}
	$aTableInfos = array_slice($aTableInfos, 0);
}

function get_cname($cname, $ename)
{
	$loc = _LOCALE_;
	if(FALSE === strstr($ename, ":"))
	{
		return ("zh_" == substr($loc, 0, 3)) ? $cname : $ename;
	}
	$new_loc = "";
	for($i=0; $i<strlen($loc); $i++)
	{
		if(substr($loc, $i ,1)==".")
		{
			break;
		}
		$new_loc .= substr($loc, $i ,1);
	}
	//輸入法:zh_TW;輸入法:zh_CN
	foreach(explode(";", $ename) as $v)
	{
		//輸入法:zh_TW
		list($name, $locale) = explode(":", $v);
		if($new_loc==$locale)
		{
			return $name;
		}
	}
	$loc = $new_loc;
	$new_loc = "";
	for($i=0; $i<strlen($loc); $i++)
	{
		if(substr($loc, $i ,1)=="_")
		{
			break;
		}
		$new_loc .= substr($loc, $i ,1);
	}
	//輸入法:zh_TW;輸入法:zh_CN
	foreach(explode(";", $ename) as $v)
	{
		//輸入法:zh_TW
		list($name, $locale) = explode(":", $v);
		if($new_loc==$locale)
		{
			return $name;
		}
	}
	foreach(explode(";", $ename) as $v)
	{
		//輸入法:zh_TW
		list($name, $locale) = explode(":", $v);
		if(substr($locale, 0, 2)=="en")
		{
			return $name;
		}
	}
	return $ename;
}
?>
