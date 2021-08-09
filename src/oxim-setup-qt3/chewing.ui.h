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


void Chewing::init()
{
    setCaption(_("The Chewing Input Method Property"));
    
    buttonGroup1->setTitle(_("Keybord's keymapping"));
    KeyMap0->setText(_("Standard"));
    KeyMap1->setText(_("Shius'"));
    KeyMap2->setText(_("IBM"));
    KeyMap3->setText(_("Ginya"));
    KeyMap4->setText(_("Eten"));
    KeyMap5->setText(_("Eten 26 key"));
    KeyMap6->setText(_("DVORAK"));
    KeyMap7->setText(_("DVORAK Shius'"));
    KeyMap8->setText(_("Pingin"));
    
    buttonGroup3->setTitle(_("SelectionKeys"));
    SelectionKeys0->setText(_("1234567890 KeSel"));
    SelectionKeys1->setText(_("qwertyuiop KeSel"));
    SelectionKeys2->setText(_("asdfghjkl; KeSel"));
    SelectionKeys3->setText(_("zxcvbnm,./ KeSel"));
    
    buttonGroup4->setTitle(_("CapsLock Output"));
    CapsLockMode0->setText(_("Lower"));
    CapsLockMode1->setText(_("Upper"));
    
    buttonOk->setText(_("_OK"));
    buttonCancel->setText(_("_Cancel"));
}
