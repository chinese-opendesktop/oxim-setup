/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include "module.h"
#include "common.h"
void InstallIM::ChoiceFile_clicked()
{
    QString sel_file = QFileDialog::getOpenFileName(
                    getenv("HOME"),
                    _("Standard Input Method Ref. File (*.cin *.cin.gz *.tab);;SCIM Input Method Ref. File(*.txt.in)"),
                    this,
                    _("open file dialog"),
                    _("Please choose") );
    FileName->setText(sel_file);
}


void InstallIM::ConnectButton_clicked()
{
    if (mirrorURL.protocol() == "ftp")
    {
	
	ftp->connectToHost(mirrorURL.host());
	ftp->login();
    }
    downloadStep = 1;
    ConnectButton->setEnabled(false);
    cinListFileName = QString::fromUtf8(oxim_user_dir()).append("/cin.list");
    downloadFile(mirrorURL+"/cin.list", cinListFileName);
}

void InstallIM::init()
{
    setCaption(_("Install Input Method"));
    installTab->changeTab(installTab->page(0), _("Instal_L from local"));
    installTab->changeTab(installTab->page(1), _("Install from _Network"));
    textLabel1->setText(_("Input full file name include file path, or press \"browse\" button to choose file;"));
    ChoiceFile->setText(_("Browse"));
    ConnectButton->setText(_("Connect"));
    buttonOk->setText(_("_OK"));
    buttonCancel->setText(_("_Cancel"));
    
    CINList->setSorting(-1);
    ConnectButton->setIconSet(QIconSet::QIconSet(QPixmap::fromMimeSource("connect.png")));
    // 鏡射站台列表位址
    mirrorsFileURL = QUrl(QString::fromUtf8(oxim_mirror_url()) + "/mirrors.site");
    // 鏡射站台列表存檔路徑與檔名
    mirrorsFileName = QString::fromUtf8(oxim_user_dir()) + "/mirrors.site";

    http = new QHttp(this);

    // Http 
    connect(http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));
    connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),this, SLOT(readResponseHeader(const QHttpResponseHeader &)));
    // ftp
    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandStarted(int)), SLOT(ftp_commandStarted(int)));
    connect(ftp, SIGNAL(commandFinished(int,bool)), SLOT(ftp_commandFinished(int, bool)));
    //connect(ftp, SIGNAL(dataTransferProgress( int, int)), SLOT(ftp_dataTransferProgress( int, int)));
    
    connect(ftp, SIGNAL(done(bool)), SLOT(ftp_done(bool)));
    connect(ftp, SIGNAL(stateChanged(int)), SLOT(ftp_stateChanged(int)));
}

/*
  * 完成讀取後續處理(有可能會有 error, 從 http->errorString() 可以取得訊息)
  */
void InstallIM::httpRequestFinished(int requestId, bool error)
{
    if (error)
    {
	QMessageBox::information(this, _("Error"),
                                 _("Download failed: %1.")
                                 .arg(http->errorString()));
	saveFile->close();
	return;
    } 

    if (requestId != httpGetId)
        return;

    saveFile->close();
    switch (downloadStep)
    {
    case 0: // 下載 mirror 站台列表
	MakeMirrorList();
	break;
    case 1: // 分析對照表列表
	MakeListView();
	break;
    }
}

/*
  * 處理 http 回應的 header
  */
void InstallIM::readResponseHeader( const QHttpResponseHeader &responseHeader )
{    
    if (responseHeader.statusCode() != 200)
    {
	QMessageBox::information(this, _("HTTP"),
                                 _("Download failed: %1.")
                                 .arg(responseHeader.reasonPhrase()));
	httpRequestAborted = true;
	http->abort();
	saveFile->close();
	return;
    }
}

#define BUFFER_LEN 1024
void InstallIM::MakeListView()
{
    CINList->clear();
    int i;
    for (i = 0 ; i < CINList->columns(); i++)
    {
	CINList->removeColumn(i);
    }
//     CINList->addColumn(trUtf8("適用語言與輸入法名稱"));
    CINList->addColumn(_("Language&Input Method Name"));
    CINList->addColumn(_("Description"));
    gzFile *fp = oxim_open_file(saveFile->name().utf8().data(), "r", OXIMMSG_WARNING);
    char line[BUFFER_LEN], cmd[BUFFER_LEN];
    QListViewItem *viewitem = NULL;
    QCheckListItem *chkitem = NULL;
    CINList->setRootIsDecorated (true);
    char *loc = strdup(setlocale(LC_MESSAGES, NULL));
    bool bShowChn = (0 == strncmp(loc, "zh", 2)) ? True : False;	//語系判斷
    while (oxim_get_line(line, BUFFER_LEN, fp, NULL, "#\r\n"))
    {
	set_item_t *set_item = oxim_get_key_value(line);
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
			if(bShowChn)
			    viewitem = new QListViewItem(CINList, viewitem, trUtf8(cmd));
			break;
		    case 2:
			if(!bShowChn)
			    viewitem = new QListViewItem(CINList, viewitem, trUtf8(cmd));
			break;
		    }
		    col++;
		}
		viewitem->setExpandable(true);
	    }
	    oxim_key_value_destroy(set_item);
	}
	else // CIN 紀錄
	{
	    chkitem = new QCheckListItem(viewitem, chkitem, "", QCheckListItem::CheckBox);
	    char *s = line;
	    int col = 0;
	    char field[BUFFER_LEN];
	    char *ss = cmd;			
	    int row = 0;
	    while (oxim_get_word(&s, cmd, BUFFER_LEN, ","))
	    {
		if (cmd[0] != ',')
		{
		    switch (col)
		    {
		    case 0: // 檔名
			CheckMap.insert(chkitem, trUtf8(cmd));
			// 是否已經安裝
			for (unsigned int i=0 ; i < oxim_get_NumberOfIM(); i++)
			{
			    iminfo_t *imp = oxim_get_IM(i);
			    QFileInfo fi(cmd);
			    if (strcmp(imp->objname, fi.baseName().utf8().data()) == 0)
			    {
				chkitem->setEnabled(false);
				break;
			    }
			}
			break;
		    case 1: // 輸入法名稱
			chkitem->setText(col - 1, trUtf8(cmd));
			break;
		    case 2: // 說明
			{
			if(!bShowChn)
				chkitem->setText( col - 1, QString(ss).section(';', 1, 1) );
			else
				chkitem->setText( col - 1, trUtf8( QString(ss).section(';', 0, 0) ) );

			/*
			while(oxim_get_word(&ss, field, BUFFER_LEN, ";"))
			{
			  switch(row)
			  {
			  case 0:  
			      if(bShowChn)
				  chkitem->setText(col - 1, trUtf8(field));
			      break;
			  case 2:
			      if(!bShowChn)
			      {
				  char *p = strchr(cmd, ';');
				  if( NULL!= p)
				  {
				      *p++;
				      chkitem->setText(col - 1, trUtf8(p));
				  }
			      }
			      break;
			  }
			  row++;
			}*/
		              }
			break;
			
		    default:
			printf("other = %s\n", QUrl(cmd));
		    }
		    col ++;
		}
	    }
	}
    }
    gzclose(fp);
}


void InstallIM::accept()
{
    downloadStep = 2;
    QMap<QCheckListItem *, QString>::Iterator it;
    for (it = CheckMap.begin(); it != CheckMap.end(); ++it)
    {
	QCheckListItem *item = it.key();
	QString cinfile = it.data();
	if (item->isOn())
	{
	    printf("download = %s\n", (mirrorURL+"/"+cinfile).utf8().data());
	    downloadFile(mirrorURL+"/"+cinfile, QString::fromUtf8(oxim_user_dir()) + "/" + cinfile);
	}
    }
    ftp->close();
    QDialog::accept();
}



void InstallIM::ftp_commandStarted(int id)
{
    printf("Start id=%d\n", id);
    //QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
}


void InstallIM::ftp_commandFinished(int id, bool error)
{
    if ( error )
    {
	QMessageBox::critical( this, tr("FTP Error"), ftp->errorString() );
	return;
    }
    printf("Finished id=%d\n", id);
    //QApplication::restoreOverrideCursor();
    
    if (id != ftpGetId)
    {
	return;
    }

    printf("Close file %s\n", saveFile->name().utf8().data());
    saveFile->close();
    switch (downloadStep)
    {
    case 0: // 下載 mirror 站台列表
	MakeMirrorList();
	break;
    case 1: // 分析對照表列表
	MakeListView();
	break;
    }
}


void InstallIM::ftp_done( bool error )
{
    if ( error )
    {
        QMessageBox::critical( this, tr("FTP Error"), ftp->errorString() );
        // If we are connected, but not logged in, it is not meaningful to stay
        // connected to the server since the error is a really fatal one (login
        // failed).
        if ( ftp->state() == QFtp::Connected )
            ftp->close();
    }
    printf("Ftp Done\n");
}

void InstallIM::ftp_stateChanged( int state )
{
    switch ( (QFtp::State)state )
    {
        case QFtp::Unconnected:
            printf("Unconnected\n");
            break;
        case QFtp::HostLookup:
            printf("Host lookup\n");
            break;
        case QFtp::Connecting:
            printf("Connecting\n");
            break;
        case QFtp::Connected:
            printf("Connected\n");
            break;
        case QFtp::LoggedIn:
            printf("Logged in\n");
            break;
        case QFtp::Closing:
            printf("Closing\n");
            break;
    }
}


bool InstallIM::downloadFile(QUrl URL, QString saveFileName)
{    
    QString protocol = URL.protocol();
    QString host = URL.host();
    QString path = URL.dirPath();
    QString name = URL.fileName();

    QString fullName = (path == "/" ? (path+name) : (path+"/"+name));
    saveFile = new QFile(saveFileName);

    if (!saveFile->open(IO_WriteOnly|IO_Raw))
    {
	QMessageBox::information(this, tr("File"),
			 _("Write error : %1.")
			 .arg(trUtf8(name)));
	delete saveFile;
	return false;
    }
    QProgressDialog progress(
	_("Downloading..."),
	_("Cancel"),
	0, this,
	_("download progress dialog"),
	true
	);
    if (protocol == "ftp")
    {
	/*connect(ftp, SIGNAL(dataTransferProgress(int,int)),
		 &progress, SLOT(setProgress(int,int)) );*/
	connect(ftp, SIGNAL(commandFinished(int,bool)),
		 &progress, SLOT(reset()) );
	connect(&progress, SIGNAL(cancelled()),ftp, SLOT(abort()));
	ftpGetId = ftp->get(fullName, saveFile);
	printf("ftpGetId = %d\n", ftpGetId);
	progress.exec();
    }
    else if (protocol == "http")
    {
/*	connect(http, SIGNAL(dataReadProgress(int,int)),
		 &progress, SLOT(setProgress(int,int)) );*/
	connect(http, SIGNAL(requestFinished(int, bool)),
		&progress, SLOT(reset()) );
	connect(&progress, SIGNAL(cancelled()),http, SLOT(abort()));
	http->setHost(host);
	httpRequestAborted = false;
	httpGetId = http->get(fullName, saveFile);
	progress.exec();
    }
    return true;
}

void InstallIM::installTab_currentChanged( QWidget *tab)
{
    // 不是第一頁(從網路安裝)或已經有列表了, 就不動作
    if (installTab->indexOf(tab) != 1 || CINList->childCount())
    {
	return;
    }

    if (!oxim_external_url())
    {
	downloadStep = 0;
	// 檢查 mirrors.site 是否存在？
	QFileInfo mirrorFile(mirrorsFileName);
	bool isUpdate = true;
	if (mirrorFile.exists() && mirrorFile.size() > 0)
	{
	    // 檔案存在 local 端，則檢查建立的時間
	    QDateTime dt = mirrorFile.created();
	    QDateTime now = QDateTime::currentDateTime();
	    // 保持 cache 一天
	    if ((now.toTime_t() - dt.toTime_t()) > 86400)
	    {
		isUpdate = true;
	    }
	    else
	    {
		isUpdate = false;
	    }
	}

	if (isUpdate)
	{
	    downloadFile(mirrorsFileURL, mirrorsFileName);
	}
	else
	{
	    MakeMirrorList();
	}
    }
    else
    {
	mirrorURL = QString(oxim_external_url());
	ConnectButton_clicked();
    }
}


void InstallIM::MakeMirrorList()
{
    CINList->clear();
    int i;
    for (i = 0 ; i < CINList->columns(); i++)
    {
	CINList->removeColumn(i);
    }
    gzFile *fp = oxim_open_file(mirrorsFileName.utf8().data(), "r", OXIMMSG_WARNING);
    char line[BUFFER_LEN], cmd[BUFFER_LEN];
    QListViewItem *viewitem = NULL;
    CINList->addColumn(_("Select a site to download"));
    while (oxim_get_line(line, BUFFER_LEN, fp, NULL, "#\r\n"))
    {
	set_item_t *set_item = oxim_get_key_value(line);
	// 站台列表
	if (set_item)
	{
	    viewitem = new QListViewItem(CINList, viewitem, trUtf8(set_item->key));
	    MirrorMap.insert(viewitem, trUtf8(set_item->value));
	}
	oxim_key_value_destroy(set_item);
    }
    gzclose(fp);
}


void InstallIM::CINList_clicked( QListViewItem *item)
{
    QMap<QListViewItem *, QUrl>::Iterator it;
    it = MirrorMap.find(item);
    if (it == MirrorMap.end())
    {
	ConnectButton->setEnabled(false);
    }
    else
    {
	ConnectButton->setEnabled(true);
	mirrorURL = it.data();
    }
}


void InstallIM::ftp_dataTransferProgress( int bytes, int total)
{
    printf("bytes=%d, total=%d\n", bytes, total);
}
