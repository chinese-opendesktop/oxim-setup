function GlobalSettings()
{
    var tags = configs.tags;
    var labelName = $(tags.lblIMName);
    var inputAlias = $(tags.inputAlias);
    var checkbtn = $(tags.chkHotkey);
    var selectbtn = $(tags.selHotkey);

    this.setData = function(id)
    {
	if ( id==undefined )
	    return false;

	var imp = imlist.get( id );

	checkbtn.click(function(){
	    var obj = $(this).parent().find("select");
	    if (this.checked)
		obj.removeAttr("disabled");
	    else
		obj.attr("disabled", "disabled");
	});

	if ( imp.hotkey=="" )
	{
	    checkbtn.removeAttr("checked");
	    selectbtn.attr("disabled", "disabled");
	}
	else
	{
	    checkbtn.attr("checked", "checked");
	    selectbtn.removeAttr("disabled");
	    selectbtn.attr("value", imp.hotkey);
	}

	labelName.html( imp.inpname );	// set im name
	inputAlias.attr("value", imp.aliasname);	// set alias name

	return true;
    }

    this.save = function(idx)
    {
	var node_id = "#node-"+idx;
	var oNode = $(node_id).children();
	var imp = imlist.get(idx);

	// 設定別名
	var alias = inputAlias.attr("value");
	if (str_trim(alias)!='')
	{
	    oNode.eq(1).html(alias);
	    oxim_set_IMAliasName(idx, alias);
	}
	else
	{
	    oNode.eq(1).html(imp.inpname);
	    oxim_set_IMAliasName(idx, '\0');
	}

	// 是否設定快速鍵
	if ( checkbtn.attr("checked") != true )
	{
	    oxim_set_IMKey(idx, -1);
	    oNode.eq(2).html("無");
	}
	else
	{
	    var key = selectbtn.attr("value");

	    if (oxim_set_IMKey(idx, key))
	    {
		oNode.eq(2).html("Ctrl+Alt+" + key);
	    }
	    else
	    {
		/*QMessageBox::information( this, _("Duplicate key"),
		_("The key you choose had used by other Input-Method!\n") +
		_("Re-Select another key, please.") );*/
	    }
	}
    }

}