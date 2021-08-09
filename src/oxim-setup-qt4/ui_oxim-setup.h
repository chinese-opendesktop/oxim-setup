/********************************************************************************
** Form generated from reading UI file 'oxim-setup.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OXIM_2D_SETUP_H
#define UI_OXIM_2D_SETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainDialog
{
public:
    QDialogButtonBox *OkCancelbuttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *AddIMButton;
    QPushButton *DelIMButton;
    QPushButton *DefaultButton;
    QPushButton *ComButton;
    QPushButton *AttributeButton;
    QTreeView *treeView;
    QWidget *tab_2;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *PreedSize;
    QSpinBox *SelectSize;
    QSpinBox *StateSize;
    QSpinBox *MenuSize;
    QSpinBox *SymbolSize;
    QSpinBox *XCINSize;
    QComboBox *FontcomboBox;
    QLabel *label_13;
    QWidget *tab_3;
    QDialogButtonBox *buttonBox_2;
    QTableWidget *tableWidget;
    QLabel *label_4;
    QWidget *tab_4;
    QLabel *VersionLabel;
    QTextBrowser *textBrowser;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *textLabel2_2;
    QLabel *textLabel1_2;

    void setupUi(QDialog *mainDialog)
    {
        if (mainDialog->objectName().isEmpty())
            mainDialog->setObjectName(QString::fromUtf8("mainDialog"));
        mainDialog->resize(562, 509);
        OkCancelbuttonBox = new QDialogButtonBox(mainDialog);
        OkCancelbuttonBox->setObjectName(QString::fromUtf8("OkCancelbuttonBox"));
        OkCancelbuttonBox->setGeometry(QRect(30, 450, 511, 32));
        OkCancelbuttonBox->setLayoutDirection(Qt::RightToLeft);
        OkCancelbuttonBox->setOrientation(Qt::Horizontal);
        OkCancelbuttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(mainDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(20, 20, 521, 411));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        AddIMButton = new QPushButton(tab);
        AddIMButton->setObjectName(QString::fromUtf8("AddIMButton"));
        AddIMButton->setGeometry(QRect(50, 310, 126, 34));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../oxim-setup-qt3/images/edit_add.png"), QSize(), QIcon::Normal, QIcon::On);
        AddIMButton->setIcon(icon);
        DelIMButton = new QPushButton(tab);
        DelIMButton->setObjectName(QString::fromUtf8("DelIMButton"));
        DelIMButton->setEnabled(false);
        DelIMButton->setGeometry(QRect(200, 310, 126, 34));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../oxim-setup-qt3/images/edit_remove.png"), QSize(), QIcon::Normal, QIcon::On);
        DelIMButton->setIcon(icon1);
        DefaultButton = new QPushButton(tab);
        DefaultButton->setObjectName(QString::fromUtf8("DefaultButton"));
        DefaultButton->setEnabled(false);
        DefaultButton->setGeometry(QRect(410, 70, 85, 27));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../oxim-setup-qt3/images/cd01.png"), QSize(), QIcon::Normal, QIcon::On);
        DefaultButton->setIcon(icon2);
        ComButton = new QPushButton(tab);
        ComButton->setObjectName(QString::fromUtf8("ComButton"));
        ComButton->setEnabled(false);
        ComButton->setGeometry(QRect(410, 120, 85, 27));
        AttributeButton = new QPushButton(tab);
        AttributeButton->setObjectName(QString::fromUtf8("AttributeButton"));
        AttributeButton->setEnabled(false);
        AttributeButton->setGeometry(QRect(410, 170, 85, 27));
        treeView = new QTreeView(tab);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(20, 30, 371, 261));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 20, 71, 31));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 60, 141, 31));
        verticalLayoutWidget = new QWidget(tab_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 100, 87, 211));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_2->addWidget(label_7);

        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_2->addWidget(label_9);

        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_2->addWidget(label_10);

        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_2->addWidget(label_11);

        label_12 = new QLabel(verticalLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_2->addWidget(label_12);

        verticalLayoutWidget_2 = new QWidget(tab_2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(120, 100, 81, 211));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        PreedSize = new QSpinBox(verticalLayoutWidget_2);
        PreedSize->setObjectName(QString::fromUtf8("PreedSize"));
        PreedSize->setMinimum(12);
        PreedSize->setMaximum(48);

        verticalLayout_3->addWidget(PreedSize);

        SelectSize = new QSpinBox(verticalLayoutWidget_2);
        SelectSize->setObjectName(QString::fromUtf8("SelectSize"));
        SelectSize->setMinimum(12);
        SelectSize->setMaximum(48);

        verticalLayout_3->addWidget(SelectSize);

        StateSize = new QSpinBox(verticalLayoutWidget_2);
        StateSize->setObjectName(QString::fromUtf8("StateSize"));
        StateSize->setMinimum(12);
        StateSize->setMaximum(18);

        verticalLayout_3->addWidget(StateSize);

        MenuSize = new QSpinBox(verticalLayoutWidget_2);
        MenuSize->setObjectName(QString::fromUtf8("MenuSize"));
        MenuSize->setMinimum(12);
        MenuSize->setMaximum(20);

        verticalLayout_3->addWidget(MenuSize);

        SymbolSize = new QSpinBox(verticalLayoutWidget_2);
        SymbolSize->setObjectName(QString::fromUtf8("SymbolSize"));
        SymbolSize->setMinimum(12);
        SymbolSize->setMaximum(24);

        verticalLayout_3->addWidget(SymbolSize);

        XCINSize = new QSpinBox(verticalLayoutWidget_2);
        XCINSize->setObjectName(QString::fromUtf8("XCINSize"));
        XCINSize->setMinimum(12);
        XCINSize->setMaximum(48);

        verticalLayout_3->addWidget(XCINSize);

        FontcomboBox = new QComboBox(tab_2);
        FontcomboBox->setObjectName(QString::fromUtf8("FontcomboBox"));
        FontcomboBox->setGeometry(QRect(130, 20, 341, 27));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(270, 50, 201, 311));
        label_13->setAutoFillBackground(false);
        label_13->setPixmap(QPixmap(QString::fromUtf8("images/picture.bmp")));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        buttonBox_2 = new QDialogButtonBox(tab_3);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setGeometry(QRect(190, 390, 176, 27));
        buttonBox_2->setLayoutDirection(Qt::RightToLeft);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableWidget = new QTableWidget(tab_3);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 34)
            tableWidget->setRowCount(34);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(16, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(17, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(18, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(19, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(20, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(21, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(22, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(23, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(24, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(25, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(26, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(27, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(28, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(29, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(30, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(31, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(32, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(33, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem36);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 20, 256, 341));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(280, 30, 231, 331));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        VersionLabel = new QLabel(tab_4);
        VersionLabel->setObjectName(QString::fromUtf8("VersionLabel"));
        VersionLabel->setGeometry(QRect(30, 20, 431, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Abyssinica SIL"));
        font.setPointSize(20);
        VersionLabel->setFont(font);
        VersionLabel->setAlignment(Qt::AlignCenter);
        textBrowser = new QTextBrowser(tab_4);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 180, 491, 192));
        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 311, 17));
        label_3 = new QLabel(tab_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 160, 81, 17));
        textLabel2_2 = new QLabel(tab_4);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(10, 60, 370, 18));
        textLabel2_2->setWordWrap(false);
        textLabel1_2 = new QLabel(tab_4);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(10, 100, 370, 22));
        textLabel1_2->setWordWrap(false);
        tabWidget->addTab(tab_4, QString());

        retranslateUi(mainDialog);
        QObject::connect(OkCancelbuttonBox, SIGNAL(accepted()), mainDialog, SLOT(accept()));
        QObject::connect(OkCancelbuttonBox, SIGNAL(rejected()), mainDialog, SLOT(reject()));
        QObject::connect(AddIMButton, SIGNAL(clicked()), mainDialog, SLOT(AddIM_clicked()));
        QObject::connect(DelIMButton, SIGNAL(clicked()), mainDialog, SLOT(DelIM_clicked()));
        QObject::connect(OkCancelbuttonBox, SIGNAL(accepted()), mainDialog, SLOT(DialogOK()));
        QObject::connect(treeView, SIGNAL(clicked(QModelIndex)), mainDialog, SLOT(findindex(QModelIndex)));
        QObject::connect(DefaultButton, SIGNAL(clicked()), mainDialog, SLOT(Default_clicked()));
        QObject::connect(ComButton, SIGNAL(clicked()), mainDialog, SLOT(Common_clicked()));
        QObject::connect(AttributeButton, SIGNAL(clicked()), mainDialog, SLOT(Attribute_clicked()));
        QObject::connect(treeView, SIGNAL(clicked(QModelIndex)), mainDialog, SLOT(Enable_clicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainDialog);
    } // setupUi

    void retranslateUi(QDialog *mainDialog)
    {
        mainDialog->setWindowTitle(QApplication::translate("mainDialog", "Open X Input Method \350\274\270\345\205\245\346\263\225\350\250\255\345\256\232", 0, QApplication::UnicodeUTF8));
        AddIMButton->setText(QApplication::translate("mainDialog", "\345\256\211\350\243\235\350\274\270\345\205\245\346\263\225", 0, QApplication::UnicodeUTF8));
        DelIMButton->setText(QApplication::translate("mainDialog", "\347\247\273\351\231\244\350\274\270\345\205\245\346\263\225", 0, QApplication::UnicodeUTF8));
        DefaultButton->setText(QApplication::translate("mainDialog", "\351\240\220\350\250\255", 0, QApplication::UnicodeUTF8));
        ComButton->setText(QApplication::translate("mainDialog", "\351\200\232\347\224\250\350\250\255\345\256\232", 0, QApplication::UnicodeUTF8));
        AttributeButton->setText(QApplication::translate("mainDialog", "\345\261\254\346\200\247", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("mainDialog", "\350\274\270\345\205\245\346\263\225(I)", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainDialog", "\345\201\217\345\245\275\345\255\227\345\236\213:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mainDialog", "<html><head/><body><p><span style=\" font-size:12pt;\">\345\255\227\345\236\213\345\244\247\345\260\217(Pixels)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mainDialog", "\347\265\204\345\255\227\347\265\204\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainDialog", "\351\201\270\345\255\227\347\265\204\357\274\232", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mainDialog", "\347\213\200\346\205\213\345\215\200\357\274\232", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("mainDialog", "\345\277\253\351\200\237\351\201\270\345\226\256\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("mainDialog", "\347\254\246\350\231\237\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("mainDialog", "XCIN\351\242\250\346\240\274\357\274\232", 0, QApplication::UnicodeUTF8));
        FontcomboBox->clear();
        FontcomboBox->insertItems(0, QStringList()
         << QApplication::translate("mainDialog", "\346\226\260\347\264\260\346\230\216\351\253\224", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("mainDialog", "\346\250\231\346\245\267\351\253\224", 0, QApplication::UnicodeUTF8)
         << QString()
        );
        label_13->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mainDialog", "\345\255\227\345\236\213(F)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("mainDialog", "Alt+Shift", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("mainDialog", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("mainDialog", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("mainDialog", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("mainDialog", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("mainDialog", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("mainDialog", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("mainDialog", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QApplication::translate("mainDialog", "8", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QApplication::translate("mainDialog", "9", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem10->setText(QApplication::translate("mainDialog", "0", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem11->setText(QApplication::translate("mainDialog", "a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem12->setText(QApplication::translate("mainDialog", "b", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem13->setText(QApplication::translate("mainDialog", "c", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem14->setText(QApplication::translate("mainDialog", "d", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem15->setText(QApplication::translate("mainDialog", "e", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem16->setText(QApplication::translate("mainDialog", "f", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(16);
        ___qtablewidgetitem17->setText(QApplication::translate("mainDialog", "g", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(17);
        ___qtablewidgetitem18->setText(QApplication::translate("mainDialog", "h", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(18);
        ___qtablewidgetitem19->setText(QApplication::translate("mainDialog", "i", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(19);
        ___qtablewidgetitem20->setText(QApplication::translate("mainDialog", "j", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(20);
        ___qtablewidgetitem21->setText(QApplication::translate("mainDialog", "k", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->verticalHeaderItem(21);
        ___qtablewidgetitem22->setText(QApplication::translate("mainDialog", "l", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->verticalHeaderItem(22);
        ___qtablewidgetitem23->setText(QApplication::translate("mainDialog", "m", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->verticalHeaderItem(23);
        ___qtablewidgetitem24->setText(QApplication::translate("mainDialog", "o", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->verticalHeaderItem(24);
        ___qtablewidgetitem25->setText(QApplication::translate("mainDialog", "p", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->verticalHeaderItem(25);
        ___qtablewidgetitem26->setText(QApplication::translate("mainDialog", "q", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->verticalHeaderItem(26);
        ___qtablewidgetitem27->setText(QApplication::translate("mainDialog", "r", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->verticalHeaderItem(27);
        ___qtablewidgetitem28->setText(QApplication::translate("mainDialog", "s", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->verticalHeaderItem(28);
        ___qtablewidgetitem29->setText(QApplication::translate("mainDialog", "t", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->verticalHeaderItem(29);
        ___qtablewidgetitem30->setText(QApplication::translate("mainDialog", "u", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->verticalHeaderItem(30);
        ___qtablewidgetitem31->setText(QApplication::translate("mainDialog", "v", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->verticalHeaderItem(31);
        ___qtablewidgetitem32->setText(QApplication::translate("mainDialog", "w", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->verticalHeaderItem(32);
        ___qtablewidgetitem33->setText(QApplication::translate("mainDialog", "x", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->verticalHeaderItem(33);
        ___qtablewidgetitem34->setText(QApplication::translate("mainDialog", "y", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->item(2, 0);
        ___qtablewidgetitem35->setText(QApplication::translate("mainDialog", "\346\231\237\351\221\253\347\247\221\346\212\200", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->item(3, 0);
        ___qtablewidgetitem36->setText(QApplication::translate("mainDialog", "\350\274\270\345\205\245\346\263\225\350\250\255\345\256\232", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_4->setText(QApplication::translate("mainDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\202\250\345\217\257\344\273\245\345\234\250\345\267\246\346\226\271\347\232\204\350\241\250\346\240\274\345\205\247,\345\273\272\347\253\213\346\202\250</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\266\223\345\270\270\344\275\277\347\224\250\347\232\204\347\211\207\350\252\236\343\200\201\350\251\236\345\217\245\346\210\226\350\200\205\346\230\257</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:"
                        "0px;\">\347\254\246\350\231\237,\345\276\200\345\276\214\345\234\250\350\274\270\345\205\245\347\232\204\346\231\202\345\200\231,\345\260\261\345\217\257\344\273\245</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\220\255\351\205\215Alt+Shift\346\214\211\351\215\265,\351\201\224\345\210\260\345\277\253\351\200\237\350\274\270\345\205\245</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\232\204\347\233\256\347\232\204.</p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("mainDialog", "\347\211\207\350\252\236(P)", 0, QApplication::UnicodeUTF8));
        VersionLabel->setText(QString());
        textBrowser->setHtml(QApplication::translate("mainDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Copyright (c) 2009 by  OpenDesktop.org.tw</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">This program is free software; you can redistribute it and/or modify</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-ri"
                        "ght:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    it under the terms of the GNU General Public License as published by</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    the Free Software Foundation; either version 2 of the License, or</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    (at your option) any later version.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    This program is distributed in the hope that it will be useful,</span></p>\n"
""
                        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    but WITHOUT ANY WARRANTY; without even the implied warranty of</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    GNU General Public License for more details.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    You sho"
                        "uld have received a copy of the GNU General Public License</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    along with this program; if not, write to the Free Software</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mainDialog", "<Qt4>Alantom<alan@ossii.com.tw>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mainDialog", "\346\216\210\346\254\212\345\256\243\345\221\212 :", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("mainDialog", "Author : Firefly <firefly@opendesktop.org.tw>", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("mainDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Website : <span style=\" color:#5555ff;\">http://opendesktop.org.tw</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("mainDialog", "\351\227\234\346\226\274(A)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainDialog: public Ui_mainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OXIM_2D_SETUP_H
