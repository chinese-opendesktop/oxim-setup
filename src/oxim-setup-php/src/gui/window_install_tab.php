<?php
//按下『確定』，下載並轉換輸入法對照檔
function callback_InstallTabWindow_action($button)
{
	global $wProgress;
	global $wInstallTab;
	global $sRemoteCinUrl;
	global $aTableInfos, $aSettings;
	
	$aCinLists = get_cin_lists();
	
	//處理local cin
	$CinFile = $wInstallTab->get_widget("filechooserbutton1")->get_filename(true);
	if(!empty($CinFile))
	{
		if(preg_match("/.*\.tab/", $CinFile)>0)
		{
			$CinFileName = basename($CinFile, ".tab");
			copy($CinFile, _USER_TABLE_DIR_ . "/" . $CinFileName . ".tab");
		}
		else
		{
			$CinFileName = basename(
						preg_replace(
							array("/(.*)\.txt\.in/", "/(.*)\.cin\.gz/", "/(.*)\.cin/"),
							"$1",
							$CinFile
						));
			exec(
				sprintf("oxim2tab -o %s %s", 
					_USER_TABLE_DIR_ . "/" . $CinFileName . ".tab",
					$CinFile
				)
			);
		}
		$aInfo = get_table_info(_USER_TABLE_DIR_ . "/" . $CinFileName . ".tab");
		if(!is_null($aInfo))
		{
			insert_new_table_vars($aInfo['EngName'], $aInfo['ChiName']);
		}
	}
	
	//處理ftp
	$model = $wInstallTab->get_widget("InstallFromWebTree")->get_model();
	$iter_parent = $model->get_iter_first();
	
	$wProgress->get_widget("ProgressWindow")->set_visible(true);
	while(!is_null($iter_parent))	//第一層：語言分類
	{
		$iter_child = $model->iter_children($iter_parent);
		while(!is_null($iter_child))	//第二層：對照檔列表
		{
			$wProgress->get_widget("progressbar1")->set_fraction(0.1);
			while (Gtk::events_pending()) {Gtk::main_iteration();}
			
			$clicked = $model->get_value($iter_child, 0);
			$aPath = $model->get_path($iter_child);
			if($clicked)
			{
				if(!$aCinLists[$aPath[0]]['info'][$aPath[1]]['local'])
				{
					$wProgress->get_widget("progressbar1")->set_fraction(0.4);
					$wProgress->get_widget("progressbar1")->set_text(_("Downloading...") . $aCinLists[$aPath[0]]['info'][$aPath[1]]['name']);
					while (Gtk::events_pending()) {Gtk::main_iteration();}
					
					$destCinSrcFile = _USER_TABLE_DIR_ . "/" . $aCinLists[$aPath[0]]['info'][$aPath[1]]['file'];
					if(!
						ftp_copy(
							$sRemoteCinUrl . "/" . $aCinLists[$aPath[0]]['info'][$aPath[1]]['file'], 
							$destCinSrcFile,
							FTP_BINARY
						)
					)
					{
						$wProgress->get_widget("ProgressWindow")->set_visible(false);
						restore_error_handler();
						return;
					}
					
					$wProgress->get_widget("progressbar1")->set_fraction(0.8);
					while (Gtk::events_pending()) {Gtk::main_iteration();}
					
					exec(
						sprintf("oxim2tab -o %s %s", 
							_USER_TABLE_DIR_ . "/" . basename($destCinSrcFile, ".cin.gz") . ".tab",
							$destCinSrcFile
						)
					);
					$aInfo = get_table_info(_USER_TABLE_DIR_ . "/" . basename($destCinSrcFile, ".cin.gz") . ".tab");
					insert_new_table_vars($aInfo['EngName'], $aInfo['ChiName']);
					unlink($destCinSrcFile);					
				}
			}
			
			$iter_child = $model->iter_next($iter_child);
		}
		
		$iter_parent = $model->iter_next($iter_parent);
	}
	restore_error_handler();
	$wProgress->get_widget("ProgressWindow")->set_visible(false);
	
	oxim_reload();
	
	$wInstallTab->get_widget("InstallTabWindow")->set_visible(false);
	reload_tables_treeview();
}

function callback_InstallTabWindow_switchtab($ntbk, $pointer, $pageNum)
{
	global $wInstallTab, $wProgress;
	if($pageNum==0)
	{
		return;
	}

	if(defined("_EXTERNAL_DOWNLOAD_URL_"))
	{
		callback_InstallTabWindow_connect(null);
	}
	else
	{
		//處理mirrors.site
		//檔案不存在 或 經過一天沒更新 就重新下載mirrors.site
		if(!file_exists(_USER_MIRRORS_SITE_FILE_) || abs(time() - filemtime(_USER_MIRRORS_SITE_FILE_))>86400)
		{
			$wProgress->get_widget("ProgressWindow")->set_visible(true);
// 			$wProgress->get_widget("progressbar1")->set_text(_("Downloading...") . "Mirror site list.");
			$wProgress->get_widget("progressbar1")->set_fraction(0.1);
			while (Gtk::events_pending()) {Gtk::main_iteration();}
			copy(_WWW_MIRRORS_SITE_FILE_, _USER_MIRRORS_SITE_FILE_);
			$wProgress->get_widget("progressbar1")->set_fraction(1.0);
			$wProgress->get_widget("ProgressWindow")->set_visible(false);
			clearstatcache();
		}
		
		if(is_null($wInstallTab->get_widget("InstallFromWebTree")->get_model()))
		{
			setup_InstallFromWeb_treelist();
		}
	}
	
	return;
}

//開啟視窗 - 安裝輸入法
function callback_InstallTabWindow_open($button)
{
	global $wInstallTab;
	
	if($wInstallTab->get_widget("notebook2")->get_current_page()==1)
	{
		callback_InstallTabWindow_switchtab(null, null, 1);
	}
	$x = new GtkFileFilter();
        $x->add_pattern("*.cin");
        $x->add_pattern("*.cin.gz");
        $x->add_pattern("*.tab");
        $x->add_pattern("*.txt.in");
	$wInstallTab->get_widget("filechooserbutton1")->set_filter($x);
	
	$wInstallTab->get_widget("InstallTabWindow")->set_visible(true);
}

//開啟視窗 - 移除輸入法
function callback_InstallTabWindow_remove($button)
{
	global $wMain;
	global $aTableInfos;
	
	$dialog = new GtkMessageDialog(
		null,//parent
		0,
		Gtk::MESSAGE_QUESTION,
		Gtk::BUTTONS_YES_NO,
		 _("Remove Input Method")
	);
	$dialog->set_markup(_("It'll remove the input method you choose from your computer,\n")._("and cannot use it again, are you sure to do?"));
	$answer = $dialog->run();
	$dialog->destroy();
 
	if ($answer == Gtk::RESPONSE_YES)
	{
		$path = get_tree_path();
		unlink(_USER_TABLE_DIR_ . "/". $aTableInfos[$path]['EngName'] . ".tab");
		oxim_reload();
		remove_from_table_vars($aTableInfos[$path]['EngName']);
		reload_tables_treeview();
	}
}

//將列表內容清空
function remove_InstallFromWeb_treeview()
{
	global $wInstallTab;
	$treeview = $wInstallTab->get_widget("InstallFromWebTree");
	
	$treeview->set_model(null);
	foreach($treeview->get_columns() as $column)
	{
		$treeview->remove_column($column);
	}
}

//讀取mirrors.site列表並將列表內容更新至tree中
function setup_InstallFromWeb_treelist()
{
	global $wInstallTab;
	
	$treeview = $wInstallTab->get_widget("InstallFromWebTree");
		
	$renderer = new GtkCellRendererText();
	$treeviewcolumn = new GtkTreeViewColumn(_("Select a site to download"), $renderer, "text", 0);
	
	$liststore = new GtkListStore(GObject::TYPE_STRING);
	foreach(get_mirror_sites() as $aMirrorSite)
	{
		$liststore->append(array($aMirrorSite['title']));
	}
	$treeview->set_model($liststore);
	$treeview->connect("cursor-changed", "callback_InstallFromWebTree_list_cursor_changed");
	
	$treeview->append_column($treeviewcolumn);
}

//讀取cin.list列表並將列表內容更新至tree中
function setup_InstallFromWeb_treeview()
{
	global $wInstallTab;
	
	$treeview = $wInstallTab->get_widget("InstallFromWebTree");
	
	$treeviewcolumn = new GtkTreeViewColumn( _("Language&Input Method Name") );
	$renderer1 = new GtkCellRendererToggle();
	$renderer1->connect("toggled", "callback_InstallFromWebTree_view_toggled");
	$renderer2 = new GtkCellRendererText();
	$treeviewcolumn->pack_start($renderer1, true);
	$treeviewcolumn->pack_start($renderer2, false);
	$treeviewcolumn->set_attributes($renderer1, 'active', 0);
	$treeviewcolumn->set_attributes($renderer2, 'text', 1);
	$treeviewcolumn->set_cell_data_func($renderer1, 'load_treeview_toggle', 0);
	$treeviewcolumn->set_cell_data_func($renderer2, 'load_treeview_text', 1);
	$treeview->append_column($treeviewcolumn);
	
	$renderer = new GtkCellRendererText();
	$treeviewcolumn = new GtkTreeViewColumn(_("Description"), $renderer, "text", 2);
	$treeviewcolumn->set_cell_data_func($renderer, 'load_treeview_text', 2);	
	$treeview->append_column($treeviewcolumn);
	
	$store = new GtkTreeStore(GObject::TYPE_BOOLEAN, GObject::TYPE_STRING, GObject::TYPE_STRING);
	foreach(get_cin_lists() as $aCinList)
	{
		$node = $store->append(null, array(true, $aCinList['language'], ""));
		foreach($aCinList['info'] as $aInfo)
		{
			$bChecked = $aInfo['local'] ? true : false;
			$store->append($node, array($bChecked, $aInfo['name'], $aInfo['description']));
		}
	}
	$treeview->set_model($store);
	
}

function load_treeview_toggle($cell_layout, $cellrenderer, $tree_model, $iter)
{
	$aPath = $tree_model->get_path($iter);
	$cellrenderer->set_property("visible", 
		count($aPath)==1?
			false : true
	);
	load_treeview_text($cell_layout, $cellrenderer, $tree_model, $iter);
}

function load_treeview_text($cell_layout, $cellrenderer, $tree_model, $iter)
{
	$aPath = $tree_model->get_path($iter);
	
	if(count($aPath)==2 && get_class($cellrenderer)=="GtkCellRendererToggle")
	{
		$aCinLists = get_cin_lists();
		$cellrenderer->set_property("sensitive", 
			$aCinLists[$aPath[0]]['info'][$aPath[1]]['local'] ?
				false : true
		);
		$cellrenderer->set_property("activatable", 
			$aCinLists[$aPath[0]]['info'][$aPath[1]]['local'] ?
				false : true
		);
	}
}

//『連線』按鈕被按下
function callback_InstallTabWindow_connect($button)
{
	global $wInstallTab;
	global $sRemoteCinUrl;
	
	if(defined("_EXTERNAL_DOWNLOAD_URL_"))
	{
		$sRemoteCinUrl = _EXTERNAL_DOWNLOAD_URL_;	//紀錄目前點選的遠端ftp 位置
		set_error_handler("ftpErrorHandler");
		if(!ftp_copy($sRemoteCinUrl . "/" . _CIN_LIST_FILE_NAME_, _USER_CIN_LIST_FILE_))
		{
			restore_error_handler();
			return;
		}
		restore_error_handler();
	}
	else
	{
		$aMirrorSites = get_mirror_sites();
		$path = get_InstallFromWebTree_path();
		if($path>-1)
		{
			$sRemoteCinUrl = $aMirrorSites[$path]['url'];	//紀錄目前點選的遠端ftp 位置
			set_error_handler("ftpErrorHandler");
			if(!ftp_copy($sRemoteCinUrl . "/" . _CIN_LIST_FILE_NAME_, _USER_CIN_LIST_FILE_))
			{
				restore_error_handler();
				return;
			}
			restore_error_handler();
		}
	}
	remove_InstallFromWeb_treeview();
	setup_InstallFromWeb_treeview();
	$wInstallTab->get_widget("button12")->set_sensitive(false);
}

//游標被改變
function callback_InstallFromWebTree_list_cursor_changed($treeview)
{
	global $wInstallTab;
	
	$path = get_InstallFromWebTree_path();
	if(count($wInstallTab->get_widget("InstallFromWebTree")->get_columns())==1)
	{
		//連線按鈕
		$wInstallTab->get_widget("button12")->set_sensitive(
			$path>-1 ? true : false
		);
	}
	else
	{
		$wInstallTab->get_widget("button12")->set_sensitive(false);
	}
	
}

//『取消』
function callback_InstallTabWindow_CancelButton_clicked($button)
{
	global $wInstallTab;
	remove_InstallFromWeb_treeview();
	$wInstallTab->get_widget("InstallTabWindow")->set_visible(false);
}

//取得Tree之目前選取的索引值
function get_InstallFromWebTree_path()
{
	global $wInstallTab;
	
	$a = $wInstallTab->get_widget("InstallFromWebTree")->get_cursor();
	return isset($a[0][0]) ? $a[0][0] : -1;
}

//打勾被點選
function callback_InstallFromWebTree_view_toggled($cellrenderertoggle, $path)
{
	global $wInstallTab;
	
	$treeview = $wInstallTab->get_widget("InstallFromWebTree");
	$model = $treeview->get_model();
	$iter = $model->get_iter($path);
	$model->set($iter, 0, !$cellrenderertoggle->get_active());
// 	$aTableInfos[$path]['TabSettings']['Circular'] = !$cellrenderertoggle->get_active() ? 'Yes' : 'No';
}
?>
