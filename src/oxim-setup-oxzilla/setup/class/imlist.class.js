// var imlist = new IMList();

function IMList()
{
    var imgDefault = "<img border=0 src='imgs/cd01.png'>";
    var imlist = oxim_imlist();
    this.length = imlist.length;

    this.setDefault = function(node_id, tree_id)
    {
	$(tree_id).find("tbody").children().remove();

	for (var i in imlist)
	{
	    var tags = configs.tags;
	    var im = imlist[i];
	    var oIm = $(node_id).clone();

	    oIm.click( function (){ 
		var flag = false;
		var node_id = $(this).data("node_id");
		var im = new IMList().get(node_id);

		// check for Default button
		if ( configs.getData("default_node_id")!=undefined )
		{
		    if ( configs.setData("default_node_id")==node_id )
			flag = true;
		}
		else
		{
		    flag = im.is_default;
		}
		if ( flag )
		    $(tags.btnDefault).attr("disabled", "disabled");
		else
		    $(tags.btnDefault).removeAttr("disabled");

		// check for remove im button
		if ( ! new IMList().deleteIM_precheck(node_id) )
		    $(tags.btnRemoveIM).attr("disabled", "disabled");
		else
		    $(tags.btnRemoveIM).removeAttr("disabled");
		    
		// check for Property button
		if ( im.modname.match(/gen-inp/i) ||
		    im.modname.match(/gen-inp-v1/i) ||
		    im.modname.match(/Sunpinyin/i) ||
		    im.modname.match(/chewing/i) )
		{
		    $(tags.btnProperty).removeAttr("disabled");
		}
		else
		{
		    $(tags.btnProperty).attr("disabled", "disabled");
		}

		$(tags.btnGlobal).removeAttr("disabled");
		// show/hide selected bar when click(select) on im
		for( var k=0; k<imlist.length; k++)
		{
		    $("#node-"+k).removeClass("im_selected");
		}
		$(this).addClass("im_selected");

		configs.setNodeId(node_id);

	    });

	    oIm.data("node_id", i );
	    oIm.attr("id", oIm.attr("id")+i);
	    oIm.find("td").eq(0).find("input").attr("checked", im.circular ? "checked" : "")
		.data("node_id", i )
		.click(function(){
		    var node_id = $(this).data("node_id");
		    oxim_set_IMCircular(node_id, this.checked );
		});
	    oIm.find("td").eq(1).html( sprintf("%s%s", im.is_default ? imgDefault : "" , im.name) );
	    oIm.find("td").eq(2).html(im.hotkey=="" ? "無" : "Ctrl+Alt+"+im.hotkey);
	    oIm.find("td").eq(3).html(im.builtin ? "<內建>" : "");
	    oIm.appendTo( $(tree_id).find("tbody") );
	}
    }

    this.get = function (index)
    {
	return imlist[index];
    }

    this.setIMDefault = function (node_prefix, index)
    {
	for (var i in imlist)
	{
	    $(node_prefix+i).find("td").eq(1).html( sprintf("%s%s", i==index ? imgDefault : "" , imlist[i].name) );
	    if ( i==index )
	    {
		configs.setData("default_node_id", i);
	    }
	}
	oxim_set_config("DefauleInputMethod", this.get(index).objname);
    }

    this.deleteIM_precheck = function (index)
    {
	if (index == undefined)
	    return false;
	var imp = imlist[index];

	// 不在使用者目錄下的不能殺
	if (imp.builtin)
	    return false;
	// 不是 tab 檔，不能殺
	if ( ! imp.modname.match(/gen-inp/i) && ! imp.modname.match(/gen-inp-v1/i) )
	{
	    return false;
	}
	//alert("ok");
	return true;
    }

    this.deleteIM = function (node_id, tree_id, index)
    {
	var imp = imlist[index];

	file_unlink( sprintf("%s/tables/%s.tab", oxim_user_dir(), imp.objname ) );
	// 重新寫入 config 檔案
	oxim_make_config();
	this.reloadIM();
	this.setDefault(node_id, tree_id);
    }
    
    this.reloadIM = function ()
    {
	imlist = oxim_imlist(true);
    }
}
