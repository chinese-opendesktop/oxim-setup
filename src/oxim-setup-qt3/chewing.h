/****************************************************************************
** Form interface generated from reading ui file 'chewing.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CHEWING_H
#define CHEWING_H

#include <qvariant.h>
#include <qdialog.h>
#include "common.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QButtonGroup;
class QRadioButton;

class Chewing : public QDialog
{
    Q_OBJECT

public:
    Chewing( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~Chewing();

    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QButtonGroup* buttonGroup1;
    QRadioButton* KeyMap2;
    QRadioButton* KeyMap6;
    QRadioButton* KeyMap0;
    QRadioButton* KeyMap1;
    QRadioButton* KeyMap3;
    QRadioButton* KeyMap4;
    QRadioButton* KeyMap5;
    QRadioButton* KeyMap7;
    QRadioButton* KeyMap8;
    QButtonGroup* buttonGroup3;
    QRadioButton* SelectionKeys0;
    QRadioButton* SelectionKeys1;
    QRadioButton* SelectionKeys2;
    QRadioButton* SelectionKeys3;
    QButtonGroup* buttonGroup4;
    QRadioButton* CapsLockMode1;
    QRadioButton* CapsLockMode0;

    virtual void init();

protected:
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // CHEWING_H
