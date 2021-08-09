/*
*/
#include <QtGui>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include "commonsetting.h"
#include "attribute.h"
#include "oxim-setup.h"
#include "chewingsetting.h"
#include "install.h"
#include "oximtool.h"

mainDialog::mainDialog(QDialog *parent): QDialog(parent)
{

    ui.setupUi(this);
}

void mainDialog::main_init()
{
    oxim_init();
    IMList_Init();
}

//List初始化
void mainDialog::IMList_Init()
{
    idx = -1;
    ui.VersionLabel->setText(_("Open X Input Method Setup ") + QString(oxim_version()));
//TreeView
   // QStandardItemModel *model = new QStandardItemModel(0,4);
    model = new QStandardItemModel(0,4);
    model->setHeaderData(0, Qt::Horizontal,"circular");
    model->setHeaderData(1, Qt::Horizontal,"Input Method");
    model->setHeaderData(2, Qt::Horizontal,"HotKey");
    model->setHeaderData(3, Qt::Horizontal,"==");

    int i = 0;
    char key[2];
    key[1] = '\0';
//    QStandardItem *item[9];
    int n_IM = oxim_get_NumberOfIM();
    int default_idx = oxim_get_Default_IM();
    for (int j=0; j<n_IM; j++){
        iminfo_t *imp = oxim_get_IM(j);
        item[j] = new QStandardItem(QString::fromUtf8(imp->aliasname ? imp->aliasname : imp->inpname));
//      QStandardItem *item = new QStandardItem(QString::fromUtf8(imp->inpname));

        if (j == default_idx)
        {
            item[j]->setIcon(QIcon("./images/cd01.png"));
        }
        QStandardItem *box = new QStandardItem("");
        box->setCheckState(Qt::Checked);

        if (imp->key > 0 && imp->key <= 10){

            if (imp->key == 10){
                key[0] = '0';
            } else {
                key[0] = '0' + (char)imp->key;
            }

            QStandardItem *itemQ = new QStandardItem("Ctrl+Alt+" + QString(key));
            model->setItem(i, 2,itemQ);
        } else {
            QStandardItem *itemnone = new QStandardItem("none");
            model->setItem(i, 2,itemnone);
        }

        if(imp->inuserdir){
            QStandardItem *itembuit_none = new QStandardItem("");
            model->setItem(i,3,itembuit_none);
        } else {
            QStandardItem *itembuit_in = new QStandardItem( QString::fromUtf8("內建") );
            model->setItem(i,3,itembuit_in);
        }

        model->setItem(i,0,box);
        model->setItem(i,1,item[j]);
        i++;
    }
    ui.treeView->setModel(model);

// 讀取系統的字型資料
    bool ok;
    QString size;
    QFontDatabase fdb;
    ui.FontcomboBox->clear();
    ui.FontcomboBox->insertItems(1,fdb.families());
//  ui.FontcomboBox->addItems(fdb.families());

    // 讀取 OXIM 預設的字型名稱
    ui.FontcomboBox->setItemText(0,QString::fromUtf8(oxim_get_config(DefaultFontName)));

    // 讀取組字區字型大小
    size = QString::fromUtf8(oxim_get_config(PreeditFontSize));
    ui.PreedSize->setValue(size.toInt(&ok, 10));

    // 讀取選字區字型大小
    size = QString::fromUtf8(oxim_get_config(SelectFontSize));
    ui.SelectSize->setValue(size.toInt(&ok, 10));

    // 讀取狀態區字型大小
    size = QString::fromUtf8(oxim_get_config(StatusFontSize));
    ui.StateSize->setValue(size.toInt(&ok, 10));

    // 讀取選單區字型大小
    size = QString::fromUtf8(oxim_get_config(MenuFontSize));
    ui.MenuSize->setValue(size.toInt(&ok, 10));

    // 讀取符號表字型大小
    size = QString::fromUtf8(oxim_get_config(SymbolFontSize));
    ui.SymbolSize->setValue(size.toInt(&ok, 10));

    // 讀取 XCIN 風格字型大小
    size = QString::fromUtf8(oxim_get_config(XcinFontSize));
    ui.XCINSize->setValue(size.toInt(&ok, 10));


#if 0
/*測試部份 tableWidget==================================================================================*/
    ui.tableWidget_2->setColumnCount(4);
    int rowcount = oxim_get_NumberOfIM();
    ui.tableWidget_2->setRowCount(rowcount);
        QStringList header;
        header.append("circular");
        header.append("Input Method");
        header.append("Hotkey");
        header.append("==");
        ui.tableWidget_2->setHorizontalHeaderLabels(header);

    //    int n_IM = oxim_get_NumberOfIM();
    //    QCheckBox *setcheckbox = new QCheckBox;
        for (int i=0; i<n_IM; i++){
            ui.tableWidget_2->setCellWidget(i,0,new QCheckBox);
        }
        for (int j=0; j<n_IM; j++){
            iminfo_t *imp = oxim_get_IM(j);
            ui.tableWidget_2->setItem(j, 1, new QTableWidgetItem(QString::fromUtf8(imp->inpname)));

            // 快速鍵
            char key[2];
                    key[1] = '\0';
                    if (imp->key > 0 && imp->key <= 10)
                    {
                        if (imp->key == 10)
                        {
                            key[0] = '0';
                        }
                        else
                        {
                            key[0] = '0' + (char)imp->key;
                        }
                        ui.tableWidget_2->setItem(j, 2, new QTableWidgetItem(QString("Ctrl+Alt+") + QString(key)));
                    }
                    else
                    {
                        ui.tableWidget_2->setItem(j, 2, new QTableWidgetItem("none"));
                    }
        }

/*==================================================================================================*/

/*測試部份 treeWidget===============================================================================*/
    //List顯示輸入法
        ui.treeWidget->clear();
        QStringList columnTitle;
        columnTitle.append("circular");
        columnTitle.append("Input Method");
        columnTitle.append("HotKey");
        columnTitle.append("==");
        ui.treeWidget->setHeaderLabels(columnTitle);
        ui.treeWidget->resizeColumnToContents(0);

        for (int j=0; j<n_IM; j++){
            iminfo_t *imp = oxim_get_IM(j);
            QTreeWidgetItem *child = new QTreeWidgetItem();

            //判斷是否為輪換
    //      child->setFlags(child->flags()|Qt::ItemIsUserCheckable);
    //      child->setFlags(child->flags());
            if (imp->circular == true){
                child->setCheckState(0, Qt::Checked);
            }else{
                child->setCheckState(0, Qt::Unchecked);
            }

            child->setText(1, QString::fromUtf8(imp->inpname));
            ui.treeWidget->addTopLevelItem(child);

            //顯示快速鍵
            char key[2];
            key[1] = '\0';
            if (imp->key > 0 && imp->key <= 10){
                if (imp->key == 10){
                    key[0] = '0';
                }
                else{
                    key[0] = '0' + (char)imp->key;
                }
                    child->setText(2, "Ctrl+Alt+" + QString(key));
            }
            else{
                child->setText(2, "none");
            }
        }

/*==================================================================================================*/
#endif
}
void mainDialog::AddIM_clicked()
{
    installDialog *insdialog = new installDialog;
    int callback =insdialog->exec();
    if(callback == 0){
        main_init();
    }
}

void mainDialog::DelIM_clicked()
{
    if(idx <0)
        return;
/*  QMessageBox msgBox;
    msgBox.setText("Remove Input Method");
    msgBox.setInformativeText("It'll remove the input method you choose from your computer,and cannot use it again, are you sure to do?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int yesno = msgBox.exec(); */

    bool yesno = QMessageBox::warning( this, ("Remove Input Method"),
                 ("It'll remove the input method you choose from your computer,\nand cannot use it again, are you sure to do?"),
                 ("Remove(&Y)"), ("Cancel(&N)"), 0, 1, 0 );
    if (yesno != 0)
        return;

    iminfo_t *imp = oxim_get_IM(idx);
    QString tables_dir(QString::fromUtf8(oxim_user_dir()).append("/tables"));
    QString tab_name(QString::fromUtf8(imp->objname).append(".tab"));
    QFile::remove(tables_dir.append("/").append(tab_name));


// 重新寫入 config 檔案
    oxim_make_config();
//  清除 oxim config
    oxim_destroy();
// 重新讀取List
    main_init();
}

//找出TreeView的index value
void mainDialog::findindex(QModelIndex index)
{
    idx =index.row();
//    ui.testlabel05->setNum(index.row());

 }

// 更新字型資料
void mainDialog::UpdateFont()
{
    int size;
// 變更字型名稱
    oxim_set_config(DefaultFontName, ui.FontcomboBox->currentText().toUtf8().data());

// 讀取組字區字型大小
    size = ui.PreedSize->value();
    oxim_set_config(PreeditFontSize, QString::number(size).toUtf8().data());

// 設定選字區字型大小
    size = ui.SelectSize->value();
    oxim_set_config(SelectFontSize, QString::number(size).toUtf8().data());

// 設定狀態區字型大小
    size = ui.StateSize->value();
    oxim_set_config(StatusFontSize, QString::number(size).toUtf8().data());

// 設定選單區字型大小
    size = ui.MenuSize->value();
    oxim_set_config(MenuFontSize, QString::number(size).toUtf8().data());

// 設定符號表字型大小
    size = ui.SymbolSize->value();
    oxim_set_config(SymbolFontSize, QString::number(size).toUtf8().data());

// 設定 XCIN 風格字型大小
    size = ui.XCINSize->value();
    oxim_set_config(XcinFontSize, QString::number(size).toUtf8().data());

// 重新寫入 config 檔案
    oxim_make_config();
}

//按下OK鍵
void mainDialog::DialogOK()
{ 
  this->UpdateFont();
  system("oxim-agent -r");
}

void mainDialog::Default_clicked()
{
    if (idx < 0){
        return;
    }
    int default_IM = oxim_get_Default_IM();
    if (idx == default_IM){
        return;
    }
    item[default_IM]->setIcon(QIcon("NULL"));
    item[idx]->setIcon(QIcon("./images/cd01.png"));
    iminfo_t *newimp = oxim_get_IM(idx);
    oxim_set_config(DefauleInputMethod, newimp->objname);
}

void mainDialog::Enable_clicked()
{
    iminfo_t *imp = oxim_get_IM(idx);
    int default_idx = oxim_get_Default_IM();
    if(idx >= 0){
        if(default_idx != idx){
            ui.DefaultButton->setEnabled(true);
        } else {
            ui.DefaultButton->setEnabled(false);
        }
        if(imp->inuserdir){
            ui.DelIMButton->setEnabled(true);
        } else {
            ui.DelIMButton->setEnabled(false);
        }
        ui.AttributeButton->setEnabled(true);
        ui.ComButton->setEnabled(true);
    }
}

void mainDialog::Common_clicked()
{ 
    iminfo_t *imp = oxim_get_IM(idx);
    if (!imp){
        return;
    }
    commonsettingDialog *commondialog = new commonsettingDialog;
    commondialog->setting_init(idx);
    commondialog->exec();

    QString alias = commondialog->check_lineEdit();
    if (alias.isEmpty()){
        oxim_set_IMAliasName(idx, NULL);
        this->IMList_Init();
    }
    oxim_set_IMAliasName(idx, alias.toUtf8());
    QStandardItem *item = new QStandardItem(alias);
    model->setItem(idx,1,item);
    ui.treeView->setModel(model);
    this->IMList_Init();
}

void mainDialog::Attribute_clicked()
{
    if(idx < 0)
        return;
    iminfo_t *imp = oxim_get_IM(idx);
    if(QString::fromUtf8(imp->objname) == "chewing"){
        chewingsettingDialog *chewingsettingdialog = new chewingsettingDialog;
        chewingsettingdialog->exec();
    } else {
        attributeDialog *attributedialog = new attributeDialog;
        attributedialog->setting(idx);
        attributedialog->exec();
    }

}
