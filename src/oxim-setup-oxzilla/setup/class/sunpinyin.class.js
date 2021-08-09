function Sunpinyin()
{
    this.reload = function()
    {
	content = file_get_contents(configs.configfile);
	buffer = content.match(/^<InputMethod \"sunpinyin\">[^\/]*$/m)[0];
    }

    var content;
    var buffer;

    this.reload();
   /*
    <InputMethod "sunpinyin">
	    Circular = Yes
	    PinyinScheme = "1"
    </InputMethod>
    */
    
    var default_schema = buffer.match(/PinyinScheme *= *\"+(.*)\"+/)[1];	//default value
    var schema = undefined;

    this.setData = function(idx)
    {
	var sel_schema = 1;

	sel_schema = ( schema == undefined ) ? default_schema : schema;
	$(configs.tags.dlgSunpinyin).find("input[name=schema]").eq(sel_schema-1).attr("checked", "checked");

	return true;
    }

    this.submit = function()
    {
	schema = $(configs.tags.dlgSunpinyin).find("input:radio[name=schema]:checked").val();
    }

    this.save = function()
    {
	if (schema == undefined)
	    return;
	this.reload();
	/*<InputMethod "sunpinyin">
		    Circular = Yes
		    PinyinScheme = "1"*/
	var replacement = "PinyinScheme = \""+schema+"\"";
	var after = buffer.replace(/PinyinScheme *= *\".*\"/, replacement);

	var file = new File();
	file.open(configs.configfile, "wb");
	file.write(content.replace(/^<InputMethod \"sunpinyin\">[^\/]*$/m, after));
	file.close();
    }

}
