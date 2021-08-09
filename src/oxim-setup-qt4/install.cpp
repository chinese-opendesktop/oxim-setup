/*
*/
#include <iostream>
#include <QtGui>
#include <QtNetwork>
#include "install.h"
#include "oximtool.h"

using namespace std;

installDialog::installDialog(QDialog *parent): QDialog(parent)
{
    ui.setupUi(this);
    IMnetList();
    http = new QHttp(this);
    connect(http, SIGNAL(done(bool)), this, SLOT(done(bool)));
}

void installDialog::Browser_clicked()
{	
    QString sel_file = QFileDialog::getOpenFileName(this, "Open File","/home",("Standard Input Method Ref. File < *.cin *.cin.gz *.tab >;;SCIM Input Method Ref. File < *.txt.in >"));           
    ui.FileName->setText(sel_file);	
}

void installDialog::accept()
{
    QString tables_dir(QString::fromUtf8(oxim_user_dir()).append("/tables"));
    QString modules_dir(QString::fromUtf8(oxim_user_dir()).append("/modules"));

    QFileInfo file(ui.FileName->text());
    if(file.exists()){
        QString path(file.filePath());
        QString name(file.fileName());
        QString basename(file.baseName());
        QString extname(file.suffix());
        if (extname == "cin" || extname == "gz" || extname == "in"){
            QString tabname(basename.append(".tab"));
            QString cmd("oxim2tab");
            cmd.append(" -o ");
            cmd.append(tables_dir + "/" + tabname);
            cmd.append( " " );
            cmd.append(ui.FileName->text());
            system(cmd.toUtf8());
        }
    }
    if(!dfilename.isNull()){
    QString cinfile = QString::fromUtf8(oxim_user_dir()) + "/" + dfilename;
//    QString cinfile = "/tmp/" + dfilename;
    convert2table(cinfile);
    cinfile.clear();
    }
//    saveFile->close();
//    saveFile->remove();
//    saveFile = 0;

    // 重新寫入 config 檔案
    oxim_make_config();
    // 清除 oxim config
    oxim_destroy();
    //返回mainDialog
    reject();
}

void installDialog::IMnetList()
{
//    ui.IMnettreeView->resizeColumnToContents(0);
    QStandardItemModel *model = new QStandardItemModel(0,1);
    model->setHeaderData(0, Qt::Horizontal,QString::fromUtf8("請選擇下載網站"));
//    model->setHeaderData(1, Qt::Horizontal,QString::fromUtf8(""));  
    QStandardItem *item1 = new QStandardItem(QString::fromUtf8("宜蘭玉田國小"));
    QStandardItem *item2 = new QStandardItem(QString::fromUtf8("國家高速網路與計算中心"));
    QStandardItem *item3 = new QStandardItem(QString::fromUtf8("高雄市教育網路"));
    QStandardItem *item4 = new QStandardItem(QString::fromUtf8("Alan字型庫"));
    model->setItem(0, 0,item1);
    model->setItem(1, 0,item2);
    model->setItem(2, 0,item3);
//    model->setItem(3, 0,item4);
    ui.IMnettreeView->setModel(model);
}

void installDialog::Connect_clicked()
{
    QStandardItemModel *model = new QStandardItemModel(0,2);
    model->setHeaderData(0, Qt::Horizontal,QString::fromUtf8("適用語言與輸入法名稱"));
    model->setHeaderData(1, Qt::Horizontal,QString::fromUtf8("說明"));

    ui.IMnettreeView->setModel(model);
    this->MaketreeViewItem();
}

void installDialog::connecturl(QModelIndex index)
{
    switch(index.row())
    {
        case 0:
            if (index.data().toString() == QString::fromUtf8("宜蘭玉田國小"))
            QMessageBox::warning(this, QString::fromUtf8("警告!!"), QString::fromUtf8("目前暫不提供下載"), QMessageBox::Ok);
         // url = new QUrl("http://opensource.nchc.org.tw/odp/others/OXIM/cin_tables/" + dfilename);
            break;
        case 1:            
            url = new QUrl("http://opensource.nchc.org.tw/odp/others/OXIM/cin_tables/");
            break;
        case 2:
            url = new QUrl("http://ftp.kh.edu.tw/odp/OXIM/cin_tables/");
            break;
        case 3:
            url = new QUrl("http://192.168.1.245/Font/" + dfilename);
            break;
    }
}


void installDialog::download()
{
//    QUrl *url = new QUrl("http://opensource.nchc.org.tw/odp/others/OXIM/cin_tables/" + dfilename);
    QFileInfo fileInfo(url->path());
  //  QString filename = fileInfo.fileName();
 //   QString filename = dfilename.at(fileidx);
 //   file = new QFile(filename);
    file = new QFile(dfilename);
    QFile *saveFile = new QFile(QString::fromUtf8(oxim_user_dir()) +  "/" + dfilename);
//    QFile *saveFile = new QFile("/tmp/" + dfilename);

    http->setHost(url->host(), url->port(80));
    http->get(url->path(), saveFile);
//    http->get(url->toEncoded(), saveFile);
    QProgressDialog progress("Copying files...", "Cancel", 0, 100, this);
    for(int i=1;i<=100;i++){
        progress.setValue(i);
            if(progress.wasCanceled())
                return;
    }
//    http->get(url->path(), file);
//      http->close();
//      http->closeConnection();

}

void installDialog::done(bool error) {
    if (error) {
        cerr << "Error: " << qPrintable(http->errorString()) << endl;
    } else {
        cerr << "File downloaded as " << qPrintable(file->fileName())<< endl;
    }
//    file->close();
    //delete file;
    //file->remove();
//    file = 0;
}

#define BUFFER_LEN 1024
void installDialog::MaketreeViewItem()
{

    QStandardItemModel *model = new QStandardItemModel(0,2);
    model->setHeaderData(0, Qt::Horizontal,QString::fromUtf8("適用語言與輸入法名稱"));
    model->setHeaderData(1, Qt::Horizontal,QString::fromUtf8("說明"));
//    QString saveFileName = "cin.list";
//    QString cinListFileName = QString::fromUtf8(oxim_user_dir()).append("/cin.list");
    QString cinListFileName = "./cin.list";
    listFile = new QFile(cinListFileName);

    gzFile *fp = oxim_open_file(listFile->fileName().toUtf8().data(), "r", OXIMMSG_WARNING);
    char line[BUFFER_LEN], cmd[BUFFER_LEN];
    char *loc = strdup(setlocale(LC_MESSAGES, NULL));
    bool bShowChn = (0 == strncmp(loc, "zh", 2)) ? True : False;	//語系判斷
    int i = -1;
    int k = 0;
while (oxim_get_line(line, BUFFER_LEN, fp, NULL, "#\r\n"))
{
    set_item_t *set_item = oxim_get_key_value(line);
    QList<QStandardItem *>itemR;

        // 語言項目
      if (set_item)
      {
                    if (strcasecmp(set_item->key, "Language") == 0)
                    {
                        char *s = set_item->value;
                        int col = 0;
                        while(oxim_get_word(&s, cmd, BUFFER_LEN, ","))
                        {

                            switch(col)
                            {
                            case 0:
                                i++;
                                if(bShowChn)    //中文
                                    viewitem[i] = new QStandardItem(QString::fromUtf8(cmd));
                                    model->setItem(i,0,viewitem[i]);
                                break;
                            case 2:
                                if(!bShowChn)   //英文
                                    viewitem[i] = new QStandardItem(QString::fromUtf8(cmd));                                    
                                    model->setItem(i,1,viewitem[i]);
                                break;
                            }
                           col++;
                         }
                    }
                    oxim_key_value_destroy(set_item);
        } else {
        // CIN 紀錄
        char *s = line;
        int col = 0;
        char field[BUFFER_LEN];
        char *ss = cmd;
        QString String1, String2;
        int row = 0;
        int k = 0;

        while (oxim_get_word(&s, cmd, BUFFER_LEN, ","))
        {
        if (cmd[0] != ',')
        {
            switch (col)
            {
            case 0: // 檔名
                {
                String1 = cmd;
            }
            break;
            case 1: // 輸入法名稱
                {
                if (cmd[0] != '='){
                box= new QStandardItem(QString::fromUtf8(cmd));
                String2 = cmd;
                map.insert(String2, String1);
                // 是否已經安裝
                 for (unsigned int i=0 ; i < oxim_get_NumberOfIM(); i++)
                 {
                     iminfo_t *imp = oxim_get_IM(i);
                     QFileInfo fi(cmd);

                 /*    printf("%s ",imp->objname);
                     if (strcmp(imp->objname, fi.baseName().toUtf8().data()) == 0)
                     {
                         box->setEnabled(false);
                         box->setCheckState(Qt::Checked);
                         box->setCheckable(true);
                         printf("asdfsadf");
                     break;
                    }else{
                        box->setCheckState(Qt::Unchecked);
                        box->setCheckable(true);
                    }*/
                 }
               // box->setCheckState(Qt::Checked);
              //  box->setCheckable(true);
                box->setCheckState(Qt::Unchecked);
                itemR << box;
                }
            }
            break;
            case 2: // 說明
            {
                if(!bShowChn){
                    box2= new QStandardItem(QString::fromUtf8(cmd));
                    itemR << box2;
                } else {
                    box2= new QStandardItem(QString::fromUtf8(cmd));
                    itemR << box2;
                }
            }
            break;
            }//switch-end
            col ++;
        }//if-end

        }//while-end
        viewitem[i]->appendRow(itemR);
    }//else-end

 /*   dfilename.removeAt(0);
    dfilename.removeAt(39);
    dfilename.removeAt(51);
    dfilename.removeAt(60);
ui.label_2->setNum(dfilename.size());
//ui.label_2->setText(dfilename.at(60));
//ui.label_2->setText(aaa);
QStandardItem *test = new QStandardItem("test");
model->setItem(0,1,test);*/
}
gzclose(fp);
ui.IMnettreeView->setModel(model);
}

void installDialog::returnIMname(QModelIndex index)
{
  //  ui.label_3->setText(index.data().toString());
  //  ui.label_3->setNum(index.row());
//    ui.label_3->setText(map.value(index.data().toString().toUtf8()));
    dfilename = map.value(index.data().toString().toUtf8());
  //    ui.label_3->setText(map.key("3corner.cin.gz"));
 //   fileidx = index.row();
}

void installDialog::convert2table( QString sourceFile )
{
    QFileInfo fileInfo(sourceFile);
    QString tables_dir(QString::fromUtf8(oxim_user_dir()).append("/tables"));
    QString targetFile = tables_dir.append("/") + fileInfo.baseName().append(".tab");

    printf("source name = %s \n", sourceFile.toUtf8().data());
    printf("target name = %s \n", targetFile.toUtf8().data());

    QString cmd = QString( "oxim2tab" ) + " -o " + targetFile + " " + sourceFile;
    system(cmd.toUtf8().data());
}

