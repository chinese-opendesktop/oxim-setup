configs = 
{
    baseurl: file_pathinfo(window.location).dirname.replace(/file:\/\//, ""),
    configfile: oxim_user_dir() + "/oxim.conf",
    
    tags: 
    {
	tabMain: '#tabs',
	dlgInstall: '#dlgInstall',
	dlgInstallTab: '#dlgInstall > #atabs',
	dlgDeleteIMConfirm: '#dlgDeleteIMConfirm',
	dlgGlobal: '#dlgGlobal',
	dlgSunpinyin: '#dlgSunpinyin',
	dlgChewing: '#dlgChewing',
	dlgGen: '#dlgGen',
	
	btnOK: '#btnOK',
	btnCancel: '#btnCancel',
	btnDefault: '#btnDefault',
	btnInstallIM: '#btnInstallIM',
	btnRemoveIM: '#btnRemoveIM',
	btnGlobal: '#btnGlobal',
	btnProperty: '#btnProperty',
	btnConnect: '#btnConnect',
	
	frmUploadFile: '#frmUploadFile',
	inputUploadFile: '#txtUploadFile',
	lblIMName: '#labelIMName',
	inputAlias: '#inputAlias',
	chkHotkey: '#chkHotkey',
	selHotkey: '#selHotkey',
	selFontList: '#selFontList',
    },
    
    getData: function(key)
    {
	return $('body').data(key);
    },
    setData: function(key, value)
    {
	$('body').data(key, value);
    },
    
    getNodeId: function()
    {
	return this.getData('node_id');
    },
    setNodeId: function(value)
    {
	this.setData('node_id', value);
    }
};
