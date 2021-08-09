/* 20120702
*/
#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QtGui>

#include "oxim-setup.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	
    mainDialog *main = new mainDialog;
    main->main_init();
    main->show();

    return app.exec();
}


