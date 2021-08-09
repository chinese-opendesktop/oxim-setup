<?php
function callback_msg_dialog_OkButton_clicked($button)
{
	global $wMsgDialog;
	$wMsgDialog->get_widget("MsgDialog")->set_visible(false);
}
?>