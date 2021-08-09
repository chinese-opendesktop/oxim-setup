/****************************************************************************
** Form interface generated from reading ui file 'installim.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef INSTALLIM_H
#define INSTALLIM_H

#include <qvariant.h>
#include <qdialog.h>
#include "qhttp.h"
#include "qfile.h"
#include "qmessagebox.h"
#include "qmap.h"
#include "qlistview.h"
#include "qurl.h"
#include "qfileinfo.h"
#include "qftp.h"
#include "qapplication.h"
#include "qprogressdialog.h"
#include "qfiledialog.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTabWidget;
class QWidget;
class QLineEdit;
class QLabel;
class QListView;
class QListViewItem;

class InstallIM : public QDialog
{
    Q_OBJECT

public:
    InstallIM( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~InstallIM();

    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QTabWidget* installTab;
    QWidget* tab;
    QLineEdit* FileName;
    QPushButton* ChoiceFile;
    QLabel* textLabel1;
    QWidget* tab_2;
    QPushButton* ConnectButton;
    QListView* CINList;

    QMap<QCheckListItem *, QString> CheckMap;

    bool downloadFile( QUrl URL, QString saveFileName );

public slots:
    void ChoiceFile_clicked();
    void ConnectButton_clicked();
    void httpRequestFinished( int requestId, bool error );
    void readResponseHeader( const QHttpResponseHeader & responseHeader );
    void MakeListView();
    void accept();
    void ftp_commandStarted( int id );
    void ftp_commandFinished( int id, bool error );
    void ftp_done( bool error );
    void ftp_stateChanged( int state );
    void installTab_currentChanged( QWidget * tab );
    virtual void CINList_clicked( QListViewItem * item );
    virtual void ftp_dataTransferProgress( int bytes, int total );

protected:
    QGridLayout* InstallIMLayout;
    QVBoxLayout* Layout5;
    QSpacerItem* Spacer1;

protected slots:
    virtual void languageChange();

private:
    QMap <QListViewItem *, QUrl> MirrorMap;
    int downloadStep;
    QString mirrorsFileName;
    QFtp *ftp;
    QString cinListFileName;
    bool httpRequestAborted;
    int httpGetId;
    QFile *saveFile;
    QHttp *http;
    QUrl mirrorsFileURL;
    QUrl mirrorURL;
    int ftpGetId;

    void init();
    void MakeMirrorList();

};

#endif // INSTALLIM_H
