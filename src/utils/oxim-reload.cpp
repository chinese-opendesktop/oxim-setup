#include <X11/Xlib.h>
#include "oximtool.h"

int main(void)
{
    // 取得 OXIM 控制視窗 atom
    Display *dpy = XOpenDisplay(0);
    Atom oxim_atom = XInternAtom(dpy, OXIM_ATOM, true);
    // 有 oxim_atom 表示 OXIM 執行中，送 ClientMessage 給 OXIM
    // 叫他 Reload
    if (oxim_atom != None)
    {
        Window config_win = XGetSelectionOwner(dpy, oxim_atom);
        if (config_win != None)
        {
            XClientMessageEvent event;
            event.type = ClientMessage;
            event.window = config_win;
            event.message_type = oxim_atom;
            event.format = 32;
            event.data.l[0] = 0;
            XSendEvent(dpy, config_win, False, 0, (XEvent *)&event);
            XSync(dpy, False);
        }
    }
    
    return 0;
}
