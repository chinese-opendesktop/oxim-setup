function Dialogs()
{
    var tags = configs.tags;
    var content = file_get_contents(configs.baseurl+"/include/dialogs.html");

    $("body").append(content);

    $(tags.dlgDeleteIMConfirm).dialog({
	    autoOpen: false,
	    modal: true,
	    bgiframe: true,
	    resizable: false,
	    width: 500,
	    overlay: {
		backgroundColor: '#000',
		opcity: 0.5
	    },
	    buttons: {
		    "確定移除": function() { 
			    imlist.deleteIM( "#node-", "#tree", configs.getNodeId() );
			    $(this).dialog("close"); 
		    }, 
		    "取消": function() { 
			    $(this).dialog("close"); 
		    } 
	    }
    });
    $(tags.dlgGlobal).dialog({
	    autoOpen: false,
	    modal: true,
	    bgiframe: true,
	    resizable: false,
	    width: 500,
	    overlay: {
		backgroundColor: '#000',
		opcity: 0.5
	    },
	    buttons: {
		    "確定": function() { 
			    globalsettings.save( configs.getNodeId() );
			    $(this).dialog("close"); 
		    }, 
		    "取消": function() { 
			    $(this).dialog("close"); 
		    } 
	    }
    });
    $(tags.dlgSunpinyin).dialog({
	    autoOpen: false,
	    modal: true,
	    bgiframe: true,
	    resizable: false,
	    width: 500,
	    overlay: {
		backgroundColor: '#000',
		opcity: 0.5
	    },
	    buttons: {
		    "確定": function() { 
			    sunpinyin.submit();
			    $(this).dialog("close"); 
		    }, 
		    "取消": function() { 
			    $(this).dialog("close"); 
		    } 
	    }
    });
    $(tags.dlgChewing).dialog({
	    autoOpen: false,
	    modal: true,
	    bgiframe: true,
	    resizable: false,
	    width: '50%',
	    overlay: {
		backgroundColor: '#000',
		opcity: 0.5
	    },
	    buttons: {
		    "確定": function() { 
			    chewing.submit();
			    $(this).dialog("close"); 
		    }, 
		    "取消": function() { 
			    $(this).dialog("close"); 
		    } 
	    }
    });
    $(tags.dlgGen).dialog({
	    autoOpen: false,
	    modal: true,
	    bgiframe: true,
	    resizable: false,
	    width: 500,
	    overlay: {
		backgroundColor: '#000',
		opcity: 0.5
	    },
	    buttons: {
		    "確定": function() { 
			    gencin.submit();
			    $(this).dialog("close"); 
		    }, 
		    "取消": function() { 
			    $(this).dialog("close"); 
		    },
		    "預設值": function() { 
			    gencin.reload();
			    gencin.setData( configs.getNodeId() );
		    } 
	    }
    });
    $(tags.dlgInstall).dialog({
	    autoOpen: false,
	    modal: true,
	    bgiframe: true,
	    resizable: false,
	    width: '80%',
	    overlay: {
		backgroundColor: '#000',
		opcity: 0.5
	    },
	    buttons: {
		    "確定": function() { 
			    installim.localInstall($(tags.inputUploadFile).attr("value"));
			    installim.networkInstall("#treeNetwork");
			    $(this).dialog("close"); 
		    }, 
		    "取消": function() { 
			    $(this).dialog("close"); 
		    } 
	    }
    });

}
