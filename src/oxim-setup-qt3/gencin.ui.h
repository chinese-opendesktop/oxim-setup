/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/



void GenCin::defaultButton_clicked()
{
    settings_t *settings = oxim_get_default_settings(imname, false);
    if (!settings)
    {
	return;
    }

	int yesno;
	// AutoCompose
	if (oxim_setting_GetBoolean(settings, "AutoCompose", &yesno))
	{
	    AutoCompose->setChecked(yesno);
	}
	
	// AutoUpChar
	if (oxim_setting_GetBoolean(settings, "AutoUpChar", &yesno))
	{
	    AutoUpChar->setChecked(yesno);
	}
	
	// AutoFullUp
	if (oxim_setting_GetBoolean(settings, "AutoFullUp", &yesno))
	{
	    AutoFullUp->setChecked(yesno);
	}
	
	// SpaceAutoUp
	if (oxim_setting_GetBoolean(settings, "SpaceAutoUp", &yesno))
	{
	    SpaceAutoUp->setChecked(yesno);
	}
	
	// SelectKeyShift
	if (oxim_setting_GetBoolean(settings, "SelectKeyShift", &yesno))
	{
	    SelectKeyShift->setChecked(yesno);
	}
	
	// SpaceIgnore
	if (oxim_setting_GetBoolean(settings, "SpaceIgnore", &yesno))
	{
	    if (yesno)
		SpaceIgnoreYes->setChecked(true);
	    else
		SpaceIgnoreNo->setChecked(true);
	}

	// SpaceReset
	if (oxim_setting_GetBoolean(settings, "SpaceReset", &yesno))
	{
	    SpaceReset->setChecked(yesno);
	}
	
	// WildEnable
	if (oxim_setting_GetBoolean(settings, "WildEnable", &yesno))
	{
	    WildEnable->setChecked(yesno);
	}
	
	// 設定 EndKey
	if (oxim_setting_GetBoolean(settings, "EndKey", &yesno))
	{
	    EndKey->setChecked(yesno);
	}

	// 設定特殊字根
	char *spstroke;
	if (oxim_setting_GetString(settings, "DisableSelectList", &spstroke))
	{
	    if (strcasecmp(spstroke, "None") != 0)
		DisableSelectList->setText(spstroke);
	}
}


void GenCin::init()
{
    setCaption(_("Input Method Property Settings"));
    
    textLabel1->setText(_("IM:"));
    AutoCompose->setText(_("Auto show word-combined rst."));
    WildEnable->setText(_("Enable '*','?' wild case word f."));
    SpaceReset->setText(_("Press space key to reset."));
    AutoUpChar->setTitle(_("Auto show char mode"));
    SpaceAutoUp->setText(_("Auto out wrd"));
    SelectKeyShift->setText(_("Shift selkey."));
    AutoFullUp->setTitle(_("Auto output word"));
    SpaceIgnoreYes->setText(_("Ignore space"));
    SpaceIgnoreNo->setText(_("Space key valid"));
    EndKey->setText(_("end key to out. wrd"));
    QToolTip::add(EndKey, _("If the Input Method defined EndKey(input method like chewing, etc), then when you press EndKey you choose, OXIM output the word automatic."));
    textLabel3->setText(_("Special Chars:"));
    QToolTip::add(DisableSelectList, _("This function just design for array30's special require. Set this to disable select list when press some special key."));
    
    buttonOk->setText(_("_OK"));
    buttonCancel->setText(_("_Cancel"));
    defaultButton->setText(_("_Default"));
    QToolTip::add(defaultButton, _("Default Input Method Setting"));
}
