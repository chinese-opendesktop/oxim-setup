/********************************************************************************
** Form generated from reading UI file 'commonsetting.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONSETTING_H
#define UI_COMMONSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_commonsettingDialog
{
public:
    QLabel *label;
    QLabel *IMNameLabel;
    QLabel *label_3;
    QLineEdit *AliasNameEdit;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *commonsettingDialog)
    {
        if (commonsettingDialog->objectName().isEmpty())
            commonsettingDialog->setObjectName(QString::fromUtf8("commonsettingDialog"));
        commonsettingDialog->resize(399, 237);
        label = new QLabel(commonsettingDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 61, 31));
        IMNameLabel = new QLabel(commonsettingDialog);
        IMNameLabel->setObjectName(QString::fromUtf8("IMNameLabel"));
        IMNameLabel->setGeometry(QRect(100, 30, 271, 31));
        label_3 = new QLabel(commonsettingDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 80, 63, 21));
        AliasNameEdit = new QLineEdit(commonsettingDialog);
        AliasNameEdit->setObjectName(QString::fromUtf8("AliasNameEdit"));
        AliasNameEdit->setGeometry(QRect(90, 80, 281, 27));
        checkBox = new QCheckBox(commonsettingDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 130, 171, 31));
        comboBox = new QComboBox(commonsettingDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(200, 130, 171, 27));
        buttonBox = new QDialogButtonBox(commonsettingDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(190, 180, 181, 34));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        retranslateUi(commonsettingDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), commonsettingDialog, SLOT(reject()));
        QObject::connect(checkBox, SIGNAL(stateChanged(int)), commonsettingDialog, SLOT(combobox_enable()));
        QObject::connect(buttonBox, SIGNAL(accepted()), commonsettingDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(commonsettingDialog);
    } // setupUi

    void retranslateUi(QDialog *commonsettingDialog)
    {
        commonsettingDialog->setWindowTitle(QApplication::translate("commonsettingDialog", "\350\274\270\345\205\245\346\263\225\351\200\232\347\224\250\350\250\255\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("commonsettingDialog", "\350\274\270\345\205\245\346\263\225:", 0, QApplication::UnicodeUTF8));
        IMNameLabel->setText(QApplication::translate("commonsettingDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("commonsettingDialog", "\345\210\245\345\220\215:", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("commonsettingDialog", "\344\275\277\347\224\250\347\265\204\345\220\210\351\215\265Ctrl+Alt+", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("commonsettingDialog", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("commonsettingDialog", "0", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class commonsettingDialog: public Ui_commonsettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONSETTING_H
