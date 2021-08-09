/****************************************************************************
** Form interface generated from reading ui file 'globolsetting.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GLOBOLSETTING_H
#define GLOBOLSETTING_H

#include <qvariant.h>
#include <qdialog.h>
#include "qlineedit.h"
#include "qcheckbox.h"
#include "qmessagebox.h"
#include "common.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QComboBox;
class QCheckBox;
class QLineEdit;

class GlobolSetting : public QDialog
{
    Q_OBJECT

public:
    GlobolSetting( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GlobolSetting();

    QLabel* textLabel2;
    QPushButton* GlobolOKButton;
    QPushButton* GlobolCancelButton;
    QComboBox* HotKey;
    QCheckBox* HotKeyBox;
    QLabel* IMNameLabel;
    QLabel* textLabel1;
    QLineEdit* AliasNameEdit;

    virtual void init();

public slots:
    virtual void HotKeyBox_stateChanged( int state );

protected:
    QGridLayout* GlobolSettingLayout;

protected slots:
    virtual void languageChange();

};

#endif // GLOBOLSETTING_H
