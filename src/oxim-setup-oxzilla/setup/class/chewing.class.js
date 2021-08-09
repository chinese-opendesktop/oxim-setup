function Chewing()
{
    this.reload = function()
    {
	content = file_get_contents(configs.configfile);
	buffer = content.match(/^<InputMethod \"chewing\">[^\/]*$/m)[0];
    }

    var tags = configs.tags;
    var content;
    var buffer;
    
    this.reload();
   /*
    <InputMethod "sunpinyin">
	    Circular = Yes
	    PinyinScheme = "1"
    </InputMethod>
    */
    // default values
    var default_keymap = buffer.match(/KeyMap *= *\"+(.*)\"+/)[1];
    var default_selectionkeys = buffer.match(/SelectionKeys *= *\"+(.*)\"+/)[1];
    var default_capslockmode = buffer.match(/CapsLockMode *= *\"+(.*)\"+/)[1];
    var keymap = undefined;
    var selectionkeys = undefined;
    var capslockmode = undefined;


    this.setData = function(idx)
    {
	var sel_keymap = 0;
	var sel_selectionkeys = 0;
	var sel_capslockmode = 0;

	sel_keymap = ( keymap == undefined ) ? default_keymap : keymap;
	sel_selectionkeys = ( selectionkeys == undefined ) ? default_selectionkeys : selectionkeys;
	sel_capslockmode = ( capslockmode == undefined ) ? default_capslockmode : capslockmode;
	$(tags.dlgChewing).find("input[name=keyboard]").eq(sel_keymap).attr("checked", "checked");
	$(tags.dlgChewing).find("input[name=selectkey]").eq(sel_selectionkeys).attr("checked", "checked");
	$(tags.dlgChewing).find("input[name=capslock]").eq(sel_capslockmode).attr("checked", "checked");

	return true;
    }

    this.submit = function()
    {
	keymap = $(tags.dlgChewing).find("input:radio[name=keyboard]:checked").val();
	selectionkeys = $(tags.dlgChewing).find("input:radio[name=selectkey]:checked").val();
	capslockmode = $(tags.dlgChewing).find("input:radio[name=capslock]:checked").val();
    }

    this.save = function()
    {
	if ( keymap == undefined )
	    return;
	this.reload();
	/*<InputMethod "sunpinyin">
		    Circular = Yes
		    PinyinScheme = "1"*/
	var after = buffer.replace(/KeyMap *= *\".*\"/, "KeyMap = \""+keymap+"\"")
	    .replace(/SelectionKeys *= *\".*\"/, "SelectionKeys = \""+selectionkeys+"\"")
	    .replace(/CapsLockMode *= *\".*\"/, "CapsLockMode = \""+capslockmode+"\"");

	var file = new File();
	file.open(configs.configfile, "wb");
	file.write(content.replace(buffer, after));
	file.close();
    }

}
