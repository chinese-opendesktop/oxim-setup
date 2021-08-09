function InstallIM()
{
    var USER_TABLE_DIR = getenv("HOME") + "/.oxim/tables";
    var OXIM_MIRROR_SITE_URL = "http://opendesktop.org.tw";
    var CIN_LIST_FILE_NAME = "cin.list";
    var USER_CIN_LIST_FILE = getenv("HOME") + "/.oxim/" + CIN_LIST_FILE_NAME;
    var USER_MIRRORS_SITE_FILE = getenv("HOME") + "/.oxim/mirrors.site";
    var WWW_MIRRORS_SITE_FILE = OXIM_MIRROR_SITE_URL + "/mirrors.site";

    var tables_dir = oxim_user_dir() + "/tables";
    var modules_dir = oxim_user_dir() + "/modules";
    var isReload = false;

    function toggleBackground(thisobj)
    {
	var objs = $(thisobj).parent().find("tr");
	var total = objs.length;
	
	for( var i=0; i<total; i++)
	{
	    objs.eq(i).removeClass("im_selected");
	}
	$(thisobj).addClass("im_selected");
    }
    
    this.localInstall =  function(filename)
    {
	filename = str_trim(filename);
	if (filename.length)
	{
	    // 檢查檔案是否存在
	    if (file_exists(filename))
	    {
		var fi = file_pathinfo(filename);
		var path = fi.dirname; // 原始檔路徑
		//path = "/usr/lib/oxim/modules";
		var name = fi.basename; // 原始檔檔名
		var basename = fi.filename; // 不含副檔名的檔名
		var extname = fi.extension; // 副檔名
// 		alert(sprintf("%s\n", extname));
		// 檢查檔案的擴充名稱(*.cin、*.tab、*.so)
		if (extname == "cin" || extname == "gz" || extname == "in")
		{
		    var tabname = basename+".tab";
		    var cmd = "oxim2tab" ;
		    cmd += " -o " ;
		    cmd += tables_dir + "/" + tabname;
		    cmd += " " ;
		    cmd += filename;
		    
		    if ( exec_sync(cmd) )
		    {
			// alert(oxim_CheckTable("/root/.oxim/tables/cnscj.tab"));
			if( oxim_CheckTable(filename) )
			{
			    isReload = true;
			    alert(("Convert success\n"));
			}
			else
			{
			    alert(("1.Convert failure\n"));
			}
		    }
		    else
		    {
			alert(("2.Convert failure\n"));
		    }
		}
		else if (extname == "tab")
		{
		    // 檢查 tab 檔是否合法
		    if (oxim_CheckTable(filename) )
		    {
			var source = filename;
			var target = tables_dir + "/" + basename+".tab";
			if ( file_copy(source, target) )
			{
			    isReload = true;
			    alert(("Install success\n"));
			}
			else
			{
			    alert(("Install failure\n"));
			}
		    }
		    else
		    {
			alert(("This kind of tab file can not be support!\n"));
		    }
		}
		else
		    alert(("OXIM don't support this file\n"));
	    }
	}
	if (isReload)
	{
	    // 重新寫入 config 檔案
	    oxim_make_config();
	    // 重新讀取
    // 	IMListInit();
	}

    }
 
    this.networkInstall = function(tree_id)
    {
	var site = configs.getData('current_site');
	
	if ( site == undefined )
	    return;
	
	var objs = $(tree_id).find("input[type=checkbox]");
	var total = objs.length;
	for( var i=0; i<total; i++)
	{
	    if ( objs.get(i).checked )
	    {
		var tab_name = objs.eq(i).val();
		var table = site + "/" + tab_name;
		var destCinSrcFile = USER_TABLE_DIR + "/" + tab_name;
		
		wget(table, destCinSrcFile);
		exec_sync(
			sprintf("oxim2tab -o %s %s", 
				USER_TABLE_DIR + "/" + tab_name.replace(/\.cin\.gz$/, "") + ".tab",
				destCinSrcFile
			)
		);
		file_unlink(destCinSrcFile);
		
	    }
	}
	imlist.reloadIM();
	imlist.setDefault("#node-", "#tree");
	$("#tree").treeTable();
    }
    
    this.check_first = function()
    {
	if( oxim_external_url().length )
	{
// 		callback_InstallTabWindow_connect(null);
	}
	else
	{
		//處理mirrors.site
		//檔案不存在 或 經過一天沒更新 就重新下載mirrors.site
		if(!file_exists(USER_MIRRORS_SITE_FILE) || (new Date().getTime()/1000 - file_info(USER_MIRRORS_SITE_FILE).modify_time)>86400)
		{
		    wget(WWW_MIRRORS_SITE_FILE, USER_MIRRORS_SITE_FILE);
		}
	}
    }

    // 網路上的mirrors.site列表
    this.showMirrorSites = function(tree_id, connect_id)
    {
	this.check_first();
	var sContent = file_get_contents(USER_MIRRORS_SITE_FILE);
	var matches = sContent.match(/\".*\" *= *\".*\"/g);
	var tmpHTML = "";
	for(var i in matches)
	{
	    var match_s = matches[i].match(/\"(.*)\" *= *\"(.*)\"/);
	    tmpHTML += sprintf("<tr name='' onclick=configs.setData('current_site','%s');><td>%s</td><td></td></tr>", 
			       match_s[2], match_s[1]);
	}
	$(tree_id).find("tbody").html(tmpHTML)
	.find("tr").click(function(){
	    toggleBackground(this);
	    $(connect_id).removeAttr('disabled');
	});
    }

    this.changeTabLabel = function(sel)
    {
	if ( 0 == sel )
	{
	    $('#labelNet1').html('請選擇下載站台');
	    $('#labelNet2').html('');
	}
	else
	{
	    $('#labelNet1').html('適用語言與輸入法名稱');
	    $('#labelNet2').html('說明');
	}
    }
    
    this.connect = function(tree_id, connect_id, url)
    {
	wget(url + "/" + CIN_LIST_FILE_NAME , USER_CIN_LIST_FILE);
	if( ! file_exists( USER_CIN_LIST_FILE ) )
	    return ;
	
	var tmpHTML = "";
	var content = file_get_contents(USER_CIN_LIST_FILE);
	
	this.changeTabLabel(1);
	$(connect_id).attr('disabled', 'disabled');
	
	if( matches = content.match(/Language *= *\"[^=]*\"/gsm) )
	{
	    for(var i in matches)
	    {
		var sSubContent = matches[i];
		//test_pattern:中文(繁體)xxx
		if( sub_matches = sSubContent.match(/Language *= *\"(.*)\"/s) )
		{
		    tmpHTML += sprintf("<tr id='node-%d'><td>%s</td><td></td></tr>", i, sub_matches[1].split(',')[0]);
		}
		//test_pattern:3corner.cin.gz,"3Corner(三角編號)","胡立人﹑張源渭﹑黃克東發明的三角編號輸入法;Three Corner Code"
		if( sub_matches = sSubContent.match(/.*,\".*\",\".*\"/g) )
		{
		    for( var j in sub_matches )
		    {
			sub_matches[j] = sub_matches[j].match(/(.*),\"(.*)\",\"(.*)\"/);
			tmpHTML += sprintf("<tr id='node-%d-%d' class='child-of-node-%d'><td><input type=checkbox value=%s>%s</td><td>%s</td></tr>", 
					   i, j, i, sub_matches[j][1], sub_matches[j][2], sub_matches[j][3].split(';')[0]);
		    }
		}
	    }
	    $(tree_id).find("tbody").html(tmpHTML)
		.find("tr").click(function(){
		    toggleBackground(this);
		});

	    $(tree_id).treeTable();
	}
    }
    
}