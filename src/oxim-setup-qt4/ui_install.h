/********************************************************************************
** Form generated from reading UI file 'install.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALL_H
#define UI_INSTALL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_installDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *FileName;
    QPushButton *BrowserButton;
    QLabel *label;
    QWidget *tab_2;
    QPushButton *connectButton;
    QTreeView *IMnettreeView;
    QPushButton *pushButton;

    void setupUi(QDialog *installDialog)
    {
        if (installDialog->objectName().isEmpty())
            installDialog->setObjectName(QString::fromUtf8("installDialog"));
        installDialog->resize(557, 382);
        buttonBox = new QDialogButtonBox(installDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(440, 20, 81, 91));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(installDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(40, 20, 381, 301));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        FileName = new QLineEdit(tab);
        FileName->setObjectName(QString::fromUtf8("FileName"));
        FileName->setGeometry(QRect(20, 110, 321, 27));
        BrowserButton = new QPushButton(tab);
        BrowserButton->setObjectName(QString::fromUtf8("BrowserButton"));
        BrowserButton->setGeometry(QRect(250, 160, 85, 27));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 331, 71));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        connectButton = new QPushButton(tab_2);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(270, 220, 85, 34));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../src/oxim-setup-qt3/images/connect.png"), QSize(), QIcon::Normal, QIcon::On);
        connectButton->setIcon(icon);
        IMnettreeView = new QTreeView(tab_2);
        IMnettreeView->setObjectName(QString::fromUtf8("IMnettreeView"));
        IMnettreeView->setGeometry(QRect(20, 10, 341, 201));
        tabWidget->addTab(tab_2, QString());
        pushButton = new QPushButton(installDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(440, 180, 90, 27));

        retranslateUi(installDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), installDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), installDialog, SLOT(reject()));
        QObject::connect(BrowserButton, SIGNAL(clicked()), installDialog, SLOT(Browser_clicked()));
        QObject::connect(connectButton, SIGNAL(clicked()), installDialog, SLOT(Connect_clicked()));
        QObject::connect(pushButton, SIGNAL(clicked()), installDialog, SLOT(download()));
        QObject::connect(IMnettreeView, SIGNAL(clicked(QModelIndex)), installDialog, SLOT(returnIMname(QModelIndex)));
        QObject::connect(IMnettreeView, SIGNAL(clicked(QModelIndex)), installDialog, SLOT(connecturl(QModelIndex)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(installDialog);
    } // setupUi

    void retranslateUi(QDialog *installDialog)
    {
        installDialog->setWindowTitle(QApplication::translate("installDialog", "\345\256\211\350\243\235\350\274\270\345\205\245\346\263\225", 0, QApplication::UnicodeUTF8));
        BrowserButton->setText(QApplication::translate("installDialog", "\347\200\217\350\246\275", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("installDialog", "\350\253\213\350\274\270\345\205\245\346\252\224\346\241\210\345\256\214\346\225\264\350\267\257\345\276\221\345\220\215\347\250\261,\346\210\226\346\214\211\344\270\200\344\270\213\343\200\214\347\200\217\350\246\275\343\200\215,\n"
"\346\214\211\351\210\225\351\201\270\346\223\207 ; \345\246\202\346\236\234\346\230\257*.cin\346\252\224\346\241\210\347\232\204\350\251\261,\350\253\213\347\242\272\345\256\232\350\251\262\346\252\224\n"
"\346\230\257UTF-8\347\267\250\347\242\274.", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("installDialog", "\345\276\236\346\234\254\346\251\237\345\256\211\350\243\235(L)", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("installDialog", "\351\200\243\347\267\232", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("installDialog", "\345\276\236\347\266\262\350\267\257\345\256\211\350\243\235(N)", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("installDialog", "\344\270\213\350\274\211", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class installDialog: public Ui_installDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALL_H
