#include "config.h"
#include <libintl.h>
#include "oxim-setup.h"
#include "oximtool.h"

#define _(string) ((trUtf8(gettext(string))).replace("_", "&"))
//#define _(string) ((QString(gettext(string).utf8())).replace("_", "&"))
