function FontList(font_list_id, area_id)
{
    var tmp = "";
    var fontlist = font_list();

    this.save = function()
    {
	var prefix = "#sel";
	var enums = [ "PreeditFontSize", "SelectFontSize", "StatusFontSize", 
			"MenuFontSize", "SymbolFontSize", "XcinFontSize"];

	oxim_set_config("DefaultFontName", $(configs.tags.selFontList).attr("value"));
	// 
	for (var i in enums)
	    oxim_set_config(enums[i], $(prefix+enums[i]).attr("value"));

	// 重新寫入 config 檔案
	oxim_make_config();
    }

    this.setDefault = function()
    {
	for (var i in fontlist)
	{
	    var sel_txt = "";
	    
	    if ( oxim_get_config("DefaultFontName") == fontlist[i] )
		sel_txt = "selected";
	    tmp += sprintf("<option %s>%s</option>", sel_txt, fontlist[i]);
	}
	$(font_list_id).html( tmp );

	var objs = $(area_id).find("input");
	for (var i=0; i<objs.length; i++)
	{
	    var id = objs.get(i).id;
	    var key = id.replace(/^sel/, "");
	    objs.eq(i).attr("value", oxim_get_config(key));
	}
    }

}