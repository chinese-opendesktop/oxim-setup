/*
*/
#ifndef INSTALL_H
#define INSTALL_H

#include <QObject>
#include <QStandardItem>
#include "ui_install.h"

class QUrl;
class QHttp;
class QFile;

class installDialog : public QDialog
{
	Q_OBJECT
	
public:
    installDialog(QDialog *parent =0 );
    void accept();
    void IMnetList();
    void MaketreeViewItem();
    void convert2table(QString);

signals:

public slots:
    void Browser_clicked();
    void Connect_clicked();
    void connecturl(QModelIndex);
    void returnIMname(QModelIndex);
    void download();
    void done(bool );
	
private:
    Ui::installDialog ui;
    QUrl *url;
    QHttp *http;
    QFile *file;
    QFile *listFile;
    QFile *saveFile;
    QStandardItemModel *model;
    QStandardItem *viewitem[20];
    QStandardItem *box;
    QStandardItem *box1;
    QStandardItem *box2;
    QMap<QString ,QString > map;
    QString dfilename;

//    QStringList dfilename;
 //   int fileidx;

};
	
#endif 
