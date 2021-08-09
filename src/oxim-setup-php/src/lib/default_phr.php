<?php
/*
*片語檔相關函式
*/
function get_default_pharse_content()
{
	$aContent = array();
	if(file_exists(_PHARSE_FILE_))
	{
		$fp = fopen(_PHARSE_FILE_, "r");
	}
	else
	{
		$fp = fopen(_DEFAULT_TABLE_DIR_ . "/default.phr", "r");
	}
	while(!feof($fp))
	{
		$char = $parse = "";
		list($char, $parse) = explode(" ", fgets($fp));
		if($char!='')
		{
			$aContent[$char] = str_replace(array("\"","\r","\n"), "", $parse);
		}
	}
	fclose($fp);
	
	return $aContent;
}
?>