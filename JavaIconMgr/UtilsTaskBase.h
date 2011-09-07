#ifndef _UTILSTASKBASE_H
#define _UTILSTASKBASE_H

#include <qcopchannel_qws.h>

#include <qstring.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#include <AM_LauncherClient.h>

#include "myDef.h"
#include "UtilsEnum.h"
#include "UtilsTools.h"


void launchAppObject( QString uid );

void loadJava(const QString &gname, bool isSD, bool isMult = true);//, QString &existAppInProcListStr = QString::null);

bool processIsRuning(int pid);

#endif //UTILSTASKBASE_H

