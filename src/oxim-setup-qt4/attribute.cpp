/*
*/
#include <QtGui>
#include "attribute.h"
#include "oximtool.h"

attributeDialog::attributeDialog(QDialog *parent): QDialog(parent)
{
    ui.setupUi(this);
}

void attributeDialog::setting(int idx)
{
    iminfo_t *imp = oxim_get_IM(idx);
    ui.IMName->setText(QString::fromUtf8(imp->inpname));
}
