function GenCin()
{
    var tags = configs.tags;
    var fields = [
	    { "name": "AutoCompose", "type": "boolean" },
	    { "name": "AutoUpChar", "type": "boolean" },
	    { "name": "AutoFullUp", "type": "boolean" },
	    { "name": "SpaceAutoUp", "type": "boolean" },
	    { "name": "SelectKeyShift", "type": "boolean" },
	    { "name": "SpaceIgnore", "type": "radio" },
	    { "name": "SpaceReset", "type": "boolean" },
	    { "name": "WildEnable", "type": "boolean" },
	    { "name": "EndKey", "type": "boolean" },
	    { "name": "DisableSelectList", "type": "string" }
	];

    this.reload = function()
    {
	var imp = imlist.get(current_index);
	if ( ! imp )
	    return false;

	var name = imp.objname;
	var pattern = new RegExp("^<InputMethod \""+name+"\">[^\/]*$", "/m");
	var content = file_get_contents(configs.configfile);

	buffer = content.match(pattern)[0];
    }

    var buffer = undefined;
    var current_index = -1;
    var imp_sets = new Array();
    var changed = false;
    
/*    this.debug = function(idx)
    {
	for(var i in imp_sets)
	{
	    var imp = imp_sets[i];

	    for(var j in fields)
	    {
		alert(i+"\t"+imp[fields[j].name]);
	    }
	}
    }
*/
    this.setData = function(idx)
    {
	var isnew = false;
	var imp = imlist.get(idx);
	if (! imlist.get(idx) )
	    return false;

	current_index = idx;
	$(tags.dlgGen).find(tags.lblIMName).html( 
		imp.aliasname!='' ? imp.aliasname : imp.inpname 
	    );

	if ( !imp_sets[idx] )
	{
// 	    alert("reload");
	    imp_sets[idx] = {};
	    this.reload();
	    isnew = true;
	}

	for (var i in fields)
	{
	    var field = fields[i];
	    var pattern = new RegExp(field.name + " .*= .*\"+(.*)\"+");

	    if ( isnew )
		imp_sets[idx][field.name] = buffer.match(pattern)[1];

	    if (field.type == "boolean")
	    {
		var flag = (-1 == imp_sets[idx][field.name].search(/(yes)|(true)/i)) ? false : true;
		$(tags.dlgGen).find("input[name="+field.name+"]").get(0).checked = flag;
	    }
	    if (field.type == "radio")
	    {
		var sel_idx = (-1 == imp_sets[idx][field.name].search(/(yes)|(true)/i)) ? 1 : 0;
		$(tags.dlgGen).find("input[name="+field.name+"]").get(sel_idx).checked = true;
	    }
	    if (field.type == "string")
	    {
		var prevalue = str_trim(imp_sets[idx][field.name]);
		var value = prevalue == 'None' ? '' : prevalue;
		$(tags.dlgGen).find("input[name="+field.name+"]").attr("value", value);
	    }
	}
	//this.debug();

	return true;
    }

    this.submit = function()
    {
// 	alert('submit');
	changed = true;
	for (var i in fields)
	{
	    var field = fields[i];

	    if (field.type == "boolean")
	    {
		var value = $(tags.dlgGen).find("input[name="+field.name+"]").get(0).checked ? "Yes" : "No";
		imp_sets[current_index][field.name] = value;
	    }
	    if (field.type == "radio")
	    {
		var value = $(tags.dlgGen).find("input[name="+field.name+"]:checked").val()==0 ? "Yes" : "No";
		imp_sets[current_index][field.name] = value;
	    }
	    if (field.type == "string")
	    {
		var value = $(tags.dlgGen).find("input[name="+field.name+"]").attr("value");
		imp_sets[current_index][field.name] = value;
	    }
	}
    }

    this.save = function()
    {
	if ( !changed )
	    return;

	var content = file_get_contents(configs.configfile);
	var before = "";
	var after = "";
	
	for( var i in imp_sets )
	{
	    var imp_set = imp_sets[i];
	    current_index = i;
	    this.reload();
	    before = buffer;

	    for ( var j in fields )
	    {
		var field = fields[j];
// 		if ( field.type == 'boolean' )
		{
		    var pattern = new RegExp(field.name+" *= *\".*\"");
		    buffer = buffer.replace(pattern, field.name+" = \""+imp_set[field.name]+"\"");
		}
	    }
	    after = buffer;
	    content = content.replace(before, after);
	}

	var file = new File();
	file.open(configs.configfile, "wb");
	file.write(content.replace(before, after));
	file.close();
    }

}
