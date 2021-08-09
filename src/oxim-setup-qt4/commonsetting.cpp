/*
*/
#include <QtGui>
#include "commonsetting.h"
#include "oximtool.h"
#include "oximtool.h"

commonsettingDialog::commonsettingDialog(QDialog *parent): QDialog(parent)
{
    ui.setupUi(this);
}

void commonsettingDialog::setting_init(int idx)
{
    iminfo_t *imp = oxim_get_IM(idx);
    ui.comboBox->setEnabled(false);
    ui.IMNameLabel->setText(QString::fromUtf8(imp->inpname));
    ui.AliasNameEdit->setText(QString::fromUtf8(imp->aliasname));

    if(imp->key > 0){
        ui.checkBox->setCheckable(true);
        ui.comboBox->setEnabled(true);
        ui.comboBox->setCurrentIndex(imp->key);
    }
}

QString commonsettingDialog::check_lineEdit()
{
    QString alias = ui.AliasNameEdit->text();
    return alias;
}

void commonsettingDialog::combobox_enable()
{
    ui.comboBox->setEnabled(true);
}

        
