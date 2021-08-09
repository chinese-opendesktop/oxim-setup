/********************************************************************************
** Form generated from reading UI file 'attribute.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTRIBUTE_H
#define UI_ATTRIBUTE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_attributeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *IMName;
    QLabel *label;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QGroupBox *groupBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QFrame *frame;
    QGroupBox *groupBox_2;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QFrame *frame_2;
    QCheckBox *checkBox_8;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QFrame *line;

    void setupUi(QDialog *attributeDialog)
    {
        if (attributeDialog->objectName().isEmpty())
            attributeDialog->setObjectName(QString::fromUtf8("attributeDialog"));
        attributeDialog->resize(553, 410);
        buttonBox = new QDialogButtonBox(attributeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(450, 30, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        IMName = new QLabel(attributeDialog);
        IMName->setObjectName(QString::fromUtf8("IMName"));
        IMName->setGeometry(QRect(100, 20, 271, 31));
        label = new QLabel(attributeDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 61, 31));
        checkBox = new QCheckBox(attributeDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 70, 401, 22));
        checkBox_2 = new QCheckBox(attributeDialog);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(20, 100, 411, 22));
        checkBox_3 = new QCheckBox(attributeDialog);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(20, 130, 411, 22));
        groupBox = new QGroupBox(attributeDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 160, 411, 71));
        groupBox->setFlat(false);
        groupBox->setCheckable(true);
        groupBox->setChecked(false);
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(20, 40, 161, 22));
        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(200, 40, 161, 22));
        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 20, 401, 51));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        checkBox_4->raise();
        checkBox_5->raise();
        groupBox_2 = new QGroupBox(attributeDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 240, 411, 71));
        groupBox_2->setCheckable(true);
        groupBox_2->setChecked(false);
        checkBox_6 = new QCheckBox(groupBox_2);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(20, 40, 161, 22));
        checkBox_7 = new QCheckBox(groupBox_2);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(200, 40, 161, 22));
        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 20, 401, 51));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->raise();
        checkBox_6->raise();
        checkBox_7->raise();
        checkBox_8 = new QCheckBox(attributeDialog);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(20, 330, 421, 22));
        label_3 = new QLabel(attributeDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 360, 111, 31));
        lineEdit = new QLineEdit(attributeDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 360, 291, 27));
        pushButton = new QPushButton(attributeDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(440, 360, 90, 27));
        line = new QFrame(attributeDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 50, 421, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(attributeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), attributeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), attributeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(attributeDialog);
    } // setupUi

    void retranslateUi(QDialog *attributeDialog)
    {
        attributeDialog->setWindowTitle(QApplication::translate("attributeDialog", "\350\274\270\345\205\245\346\263\225\345\261\254\346\200\247\350\250\255\345\256\232", 0, QApplication::UnicodeUTF8));
        IMName->setText(QApplication::translate("attributeDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("attributeDialog", "\350\274\270\345\205\245\346\263\225:", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("attributeDialog", "\346\211\223\345\255\227\346\231\202\357\274\214\350\207\252\345\213\225\351\241\257\347\244\272\347\265\204\345\255\227\347\265\220\346\236\234\343\200\202", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("attributeDialog", "\345\225\237\347\224\250\342\200\230*\342\200\231\343\200\201\342\200\230?\342\200\231\350\220\254\347\224\250\347\265\204\345\255\227\345\212\237\350\203\275\343\200\202", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("attributeDialog", "\351\214\257\350\252\244\346\231\202\357\274\214\346\214\211\347\251\272\347\231\275\351\215\265\346\270\205\351\231\244\343\200\202", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("attributeDialog", "\350\207\252\345\213\225\345\207\272\345\255\227\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("attributeDialog", "\346\273\277\345\255\227\346\240\271\350\207\252\345\213\225\345\207\272\345\255\227", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("attributeDialog", "\351\201\270\345\255\227\351\215\265\345\276\214\347\247\273\344\270\200\344\275\215", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("attributeDialog", "\350\207\252\345\213\225\345\207\272\345\255\227\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("attributeDialog", "\345\277\275\347\225\245\345\276\214\347\272\214\347\251\272\347\231\275", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("attributeDialog", "\345\276\214\347\272\214\347\251\272\347\231\275\350\246\226\347\202\272\346\234\211\346\225\210", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("attributeDialog", "\346\214\211\344\270\213\347\265\220\346\235\237\351\215\265\345\207\272\345\255\227\343\200\202", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("attributeDialog", "\347\211\271\346\256\212\345\255\227\346\240\271\350\250\255\345\256\232:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("attributeDialog", "\351\240\220\350\250\255\345\200\274", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class attributeDialog: public Ui_attributeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTRIBUTE_H
