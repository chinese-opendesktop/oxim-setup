<?php
//重整列表
function reload_tables_treeview()
{
	global $wMain;
	$path = get_tree_path();
	
	remove_tables_treeview();
	setup_tables_treeview();
	$wMain->get_widget("TreeTables")->set_cursor(
		$path>-1 ? $path : 0
	);
}

//將列表內容清空
function remove_tables_treeview()
{
	global $wMain;
	$treeview = $wMain->get_widget("TreeTables");
	
	$treeview->set_model(null);
	foreach($treeview->get_columns() as $column)
	{
		$treeview->remove_column($column);
	}
}

function setup_tables_treeview()
{
	global $wMain;
	global $aTableInfos, $aSettings;
	
	$treeview = $wMain->get_widget("TreeTables");
		
	$renderer = new GtkCellRendererToggle();
	$renderer->set_property("activatable", true);
	$renderer->connect("toggled", "callback_TreeTables_toggled");
	$treeviewcolumn = new GtkTreeViewColumn( _("circular"), $renderer, "active", 0);
	$treeview->append_column($treeviewcolumn);
	
	$treeviewcolumn = new GtkTreeViewColumn( _("Input Method") );
	$renderer1 = new GtkCellRendererPixbuf();
	$renderer2 = new GtkCellRendererText();
	$treeviewcolumn->pack_start($renderer1, true);
	$treeviewcolumn->pack_start($renderer2, false);
	$treeviewcolumn->set_attributes($renderer1, 'pixbuf', 1);
	$treeviewcolumn->set_attributes($renderer2, 'text', 2);
	$treeview->append_column($treeviewcolumn);
	
	$renderer = new GtkCellRendererText();
	$treeviewcolumn = new GtkTreeViewColumn( _("Hotkey"), $renderer, "text", 3);
	$treeview->append_column($treeviewcolumn);
	
	$renderer = new GtkCellRendererText();
	$treeviewcolumn = new GtkTreeViewColumn("==", $renderer, "text", 4);
	$treeview->append_column($treeviewcolumn);

	
	$liststore = new GtkListStore(GObject::TYPE_BOOLEAN, GObject::TYPE_OBJECT, GObject::TYPE_STRING, GObject::TYPE_STRING, GObject::TYPE_STRING);
	foreach($aTableInfos as $aTableInfo)
	{
		$oGdkPixBuf = null;
		if($aSettings['DefauleInputMethod']==$aTableInfo['EngName'])
		{
			$oGdkPixBuf = GdkPixbuf::new_from_file(_IMAGES_DIR_."/cd01.png");	//打勾
		}
		$sName = !empty($aTableInfo['TabSettings']['AliasName']) ? $aTableInfo['TabSettings']['AliasName'] : $aTableInfo['ChiName'];	//顯示的名稱
		$sDefaultTable = $aTableInfo['isDefaultTable'] ? _("<built-in>") : "";	//內建
		$sSetKey = isset($aTableInfo['TabSettings']['SetKey']) ? "Ctrl+Alt+".$aTableInfo['TabSettings']['SetKey'] : _("None");	//快速鍵
		$bCircular = strtolower($aTableInfo['TabSettings']['Circular'])=='yes' ? true : false;	//轉換
		
		$liststore->append(array($bCircular, $oGdkPixBuf, $sName, $sSetKey, $sDefaultTable));
	}
	$treeview->set_model($liststore);
	$treeview->connect("cursor-changed", "callback_TreeView_cursor_changed");
}

//『轉換』被點選
function callback_TreeTables_toggled($cellrenderertoggle, $path)
{
	global $wMain;
	global $aTableInfos;
	
	$treeview = $wMain->get_widget("TreeTables");
	$model = $treeview->get_model();
	$iter = $model->get_iter($path);
	$model->set($iter, 0, !$cellrenderertoggle->get_active());
	$aTableInfos[$path]['TabSettings']['Circular'] = !$cellrenderertoggle->get_active() ? 'Yes' : 'No';
}

function callback_TreeView_cursor_changed($treeview)
{
	global $wMain;
	global $aTableInfos, $aSettings;
	
	$path = get_tree_path();
	
	//屬性按鈕
	$wMain->get_widget("PropertyButton")->set_sensitive(
		$aTableInfos[$path]['EngName']=='unicode' ?
			false : true
	);
	
	//預設按鈕
	$wMain->get_widget("DefaultButton")->set_sensitive(
		$aSettings['DefauleInputMethod']==$aTableInfos[$path]['EngName'] ?
			false : true
	);

	//通用設定按鈕
	$wMain->get_widget("CommonSettingButton")->set_sensitive(true);
	
	//移除輸入法按鈕
	$wMain->get_widget("RemoveTabButton")->set_sensitive(
		$aTableInfos[$path]['isDefaultTable'] ?
			false : true
	);
}
?>
