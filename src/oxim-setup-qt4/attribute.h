#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QObject>
#include "ui_attribute.h"

class attributeDialog : public QDialog
{
    Q_OBJECT

public:
    attributeDialog(QDialog *parent =0 );
    void setting(int idx);

public slots:

private:
    Ui::attributeDialog ui;

};

#endif // ATTRIBUTE_H
