/****************************************************************************
** Form interface generated from reading ui file 'oxim-setup.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OXIM_SETUP_H
#define OXIM_SETUP_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>
#include "globolsetting.h"
#include "gencin.h"
#include "qfontdatabase.h"
#include "qbuttongroup.h"
#include "chewing.h"
#include "Sunpinyin.h"
#include "installim.h"
#include "qmap.h"
#include "common.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QPushButton;
class QListView;
class QListViewItem;
class QComboBox;
class QLabel;
class QGroupBox;
class QSpinBox;
class QIconView;
class QIconViewItem;
class QTable;
class QTextEdit;

class OXIM_Setup : public QDialog
{
    Q_OBJECT

public:
    OXIM_Setup( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~OXIM_Setup();

    QTabWidget* tabWidget;
    QWidget* Widget8;
    QPushButton* DeleteIM;
    QPushButton* AddIM;
    QPushButton* DefaultButton;
    QPushButton* GlobolButton;
    QListView* IMListView;
    QPushButton* PropertyButton;
    QWidget* Widget9;
    QComboBox* FontName;
    QLabel* textLabel1;
    QGroupBox* groupBox1;
    QSpinBox* PreeditSize;
    QSpinBox* SelectSize;
    QSpinBox* StatusSize;
    QSpinBox* MenuSize;
    QSpinBox* SymbolSize;
    QSpinBox* XCINSize;
    QLabel* textLabel2;
    QLabel* textLabel3;
    QLabel* textLabel4;
    QLabel* textLabel5;
    QLabel* textLabel6;
    QLabel* textLabel7;
    QIconView* iconView1;
    QWidget* TabPage;
    QTable* PharseTable;
    QLabel* textLabel1_3;
    QWidget* TabPage_2;
    QLabel* textLabel2_2;
    QLabel* textLabel3_2;
    QLabel* textLabel1_2;
    QLabel* VersionLabel;
    QTextEdit* textEdit1;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

    void IMListInit( void );
    void convert2table( QString sourceFile );
    virtual void init();

public slots:
    void IMListView_clicked( QListViewItem * item );
    void DefaultButton_clicked();
    void GlobolButton_clicked();
    void UpdateConfig();
    void PropertyButton_clicked();
    void RunGenCinForm( int idx, iminfo_t * imp );
    void RunChewing( int idx, iminfo_t * imp );
    virtual void RunSunpinyin( int idx, iminfo_t * imp );
    virtual void AddIM_clicked();
    bool CopyBinaryFile( QString target, QString source );
    virtual void DeleteIM_clicked();

protected:
    QVBoxLayout* OXIM_SetupLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;

    int getIndexByItem( QListViewItem * item );
    QListViewItem * getItemByIndex( int idx );

};

#endif // OXIM_SETUP_H
