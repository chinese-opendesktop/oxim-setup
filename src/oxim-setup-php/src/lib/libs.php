<?php
function get_settings()
{
	$aSettings = array();
	
	if(file_exists(_DEFAULT_OXIM_CONFIG_FILE_))
	{
		$sContent = file_get_contents(_DEFAULT_OXIM_CONFIG_FILE_);
		if(preg_match("/<SystemSetting>(.*)<\/SystemSetting>/ms", $sContent, $matches))
		{
			$sSubContent = $matches[1];
			if(preg_match_all("/(\w*)\s+=\s+(\".*\")/", $sSubContent, $sub_matches))
			{
				for($i=0; $i<count($sub_matches[0]); $i++)
				{
					$aSettings[$sub_matches[1][$i]] = str_replace("\"", "", $sub_matches[2][$i]);
				}
			}
		}
	}
	
	if(file_exists(_USER_OXIM_CONFIG_FILE_))
	{
		$sContent = file_get_contents(_USER_OXIM_CONFIG_FILE_);
		if(preg_match("/<SystemSetting>(.*)<\/SystemSetting>/ms", $sContent, $matches))
		{
			$sSubContent = $matches[1];
			if(preg_match_all("/(\w*)\s+=\s+(\".*\")/", $sSubContent, $sub_matches))
			{
				for($i=0; $i<count($sub_matches[0]); $i++)
				{
					$aSettings[$sub_matches[1][$i]] = str_replace("\"", "", $sub_matches[2][$i]);
				}
			}
		}
	}
	return $aSettings;
}

//取得Tree之目前選取的索引值
function get_tree_path()
{
	global $wMain;
	
	$a = $wMain->get_widget("TreeTables")->get_cursor();
	return isset($a[0][0]) ? $a[0][0] : -1;
}

//FTP 拷貝檔案到local端
function ftp_copy($source_url, $dest_url, $mode = FTP_ASCII)
{
	$aSource = parse_url($source_url);
	$sSourcePath = dirname($aSource['path']);
	$sSourceFile = basename($aSource['path']);
	$bSuccess = true;
	
	$bSuccess = $conn = ftp_connect($aSource['host']);
	if($conn)
	{
		$bSuccess = ftp_login($conn, "ftp", "ftp");
		if ($bSuccess)
		{
			$bSuccess = ftp_chdir($conn, $sSourcePath);
			$fp = fopen($dest_url, "w");
			$bSuccess = ftp_fget($conn, $fp, $sSourceFile, $mode);
			ftp_close($conn);
		}
	}
	else
	{
		trigger_error( _("Error occur when connect to network, check network please!"), E_USER_ERROR);
	}
	return $bSuccess;
}

function oxim_reload()
{
	exec(_OXIM_RELOAD_PROGRAM_);
}

function ftpErrorHandler($errno, $errstr, $errfile, $errline)
{
	$dialog = new GtkMessageDialog(
		null,//parent
		0,
		Gtk::MESSAGE_WARNING,
		Gtk::BUTTONS_CLOSE,
		"Warning!"
	);
	$dialog->set_markup( _("FTP Error:\n") . $errstr);
	$answer = $dialog->run();
	$dialog->destroy();
}

if ( !function_exists('sys_get_temp_dir'))
{
  function sys_get_temp_dir()
  {
    if (!empty($_ENV['TMP'])) { return realpath($_ENV['TMP']); }
    if (!empty($_ENV['TMPDIR'])) { return realpath( $_ENV['TMPDIR']); }
    if (!empty($_ENV['TEMP'])) { return realpath( $_ENV['TEMP']); }
    $tempfile=tempnam(uniqid(rand(),TRUE),'');
    if (file_exists($tempfile)) 
    {
	unlink($tempfile);
	return realpath(dirname($tempfile));
    }
  }
}
?>
