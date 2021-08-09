#ifndef CHEWINGSETTING_H
#define CHEWINGSETTING_H

#include <QObject>
#include "ui_chewingsetting.h"

class chewingsettingDialog : public QDialog
{
    Q_OBJECT

public:
    chewingsettingDialog(QDialog *parent =0 );

public slots:

private:
        Ui::chewingsettingDialog ui;

};

#endif // CHEWINGSETTING_H
