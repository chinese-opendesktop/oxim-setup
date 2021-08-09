function Pharse()
{
    this.data = new Array();

    for (var i=0; i<50; i++)
    {
	var buffer = oxim_qpharse_str(i).split(",");
	if ( buffer[0].length )
	    this.data[i] = { "key": buffer[0], "value": buffer[1] };
    }

    this.save = function(id)
    {
	var file = new File();
	var oInputs = $(id).find("input");

	if ( ! file.open( oxim_user_dir()+"/tables/default.phr" , "w" ) )
	    return;
	for ( var i=0; i<oInputs.length; i++ )
	{
	    file.write( 
		sprintf("%s \"%s\"\n", 
		    oInputs.eq(i).attr("name"), 
		    str_trim( oInputs.eq(i).attr("value") ) 
		) 
	    );
	}

	file.close();
    }

    this.setDefault = function(template_id, insert_to)
    {
	for (var i in this.data)
	{
	    var data = this.data[i];
	    var oPharse = $(template_id).clone();
	    oPharse.find("span").html( data.key );
	    oPharse.find("input").attr("value", data.value ).attr("name", data.key);
	    oPharse.appendTo(insert_to);
	}
    }
}
