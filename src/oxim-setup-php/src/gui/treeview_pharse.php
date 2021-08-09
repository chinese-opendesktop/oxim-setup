<?php
function setup_phrse_treeview()
{
	global $wMain;
	
	$treeview = $wMain->get_widget("TreePhrse");
		
	$renderer0 = new GtkCellRendererText();
	$renderer0->set_property("editable",false);
	$treeviewcolumn0 = new GtkTreeViewColumn("", $renderer0, "text", 0);
	$renderer1 = new GtkCellRendererText();
	$renderer1->set_property("editable",true);
	$renderer1->connect("edited","callback_TreePhrse_edited");
	$treeviewcolumn1 = new GtkTreeViewColumn("Alt + Shift", $renderer1, "text", 1);
	
	$liststore = new GtkListStore(64, 64);
	foreach(get_default_pharse_content() as $k=>$v)
	{
		$liststore->append(array($k, $v));
	}
	$treeview->set_model($liststore);
	
	$treeview->append_column($treeviewcolumn0);
	$treeview->append_column($treeviewcolumn1);
}

function callback_TreePhrse_edited($cellrenderertext, $path, $new_text)
{
	global $wMain;
	
	$treeview = $wMain->get_widget("TreePhrse");
	$model = $treeview->get_model();
	$iter = $model->get_iter($path);
	$model->set($iter, 1, $new_text);
}
?>