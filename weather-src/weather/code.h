/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#ifndef CODE_H_
#define CODE_H_
#include <qstring.h>

QString getAppDir();

#define SETUPPATH getAppDir()+"setup.ini"
#define INFOPATH getAppDir()+"weatherinfo.data"
#endif
