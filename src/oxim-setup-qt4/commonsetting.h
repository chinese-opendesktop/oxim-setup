#ifndef COMMONSETTING_H
#define COMMONSETTING_H

#include <QObject>
#include "ui_commonsetting.h"

class commonsettingDialog : public QDialog
{
    Q_OBJECT

public:
    commonsettingDialog(QDialog *parent =0 );
    void setting_init(int );
    QString setting_alias();
    QString check_lineEdit();

public slots:
    void combobox_enable();

private:
    Ui::commonsettingDialog ui;

};

#endif // COMMONSETTING_H
