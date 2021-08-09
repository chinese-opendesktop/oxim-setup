#include "config.h"
#include <libintl.h>
#include <qapplication.h>
#include "oxim-setup.h"
#include "oximtool.h"
#include <X11/Xlib.h>
#include <string>

int main( int argc, char ** argv )
{
    setlocale(LC_ALL, "");
    bindtextdomain("oxim-setup", "/usr/share/locale");
    textdomain("oxim-setup");
    
    QApplication oxim_setup(argc, argv);
    QFont font(QString::fromUtf8("文鼎ＰＬ新宋"));
    font.setPointSize(10);
    oxim_setup.setFont(font, true);
    
    OXIM_Setup w;
    
    // 檢查 oxim-setup 是否正在執行?
    Window os_win;
    Atom myatom = XInternAtom(w.x11Display(), "OXIM_SETUP", False);
    os_win = XGetSelectionOwner(w.x11Display(), myatom);
    if (os_win != None)
    {
	exit(0);
    }
    XSetSelectionOwner(w.x11Display(), myatom, w.winId(), CurrentTime);

    w.IMListInit();
    w.show();

    oxim_setup.connect(&oxim_setup, SIGNAL( lastWindowClosed() ), &oxim_setup, SLOT( quit()));

    return oxim_setup.exec();
}
