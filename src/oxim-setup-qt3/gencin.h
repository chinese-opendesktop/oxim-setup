/****************************************************************************
** Form interface generated from reading ui file 'gencin.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GENCIN_H
#define GENCIN_H

#include <qvariant.h>
#include <qdialog.h>
#include "qradiobutton.h"
#include "oximtool.h"
#include "gencin.h"
#include "common.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QCheckBox;
class QLineEdit;
class QButtonGroup;
class QFrame;
class QPushButton;
class QRadioButton;

class GenCin : public QDialog
{
    Q_OBJECT

public:
    GenCin( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GenCin();

    QLabel* textLabel3;
    QCheckBox* EndKey;
    QCheckBox* WildEnable;
    QCheckBox* AutoCompose;
    QLineEdit* DisableSelectList;
    QButtonGroup* AutoUpChar;
    QCheckBox* SelectKeyShift;
    QCheckBox* SpaceAutoUp;
    QCheckBox* SpaceReset;
    QFrame* line1;
    QLabel* IMName;
    QPushButton* buttonCancel;
    QPushButton* defaultButton;
    QButtonGroup* AutoFullUp;
    QRadioButton* SpaceIgnoreNo;
    QRadioButton* SpaceIgnoreYes;
    QPushButton* buttonOk;
    QLabel* textLabel1;

    QString imname;

    virtual void init();

public slots:
    virtual void defaultButton_clicked();

protected:

protected slots:
    virtual void languageChange();

};

#endif // GENCIN_H
