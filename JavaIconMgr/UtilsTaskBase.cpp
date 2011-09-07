/******************************
Java Mgr
by wanggjghost(¿·§Œµ•“ÌÃÏ π)

www.591fan.cn
41245110@qq.com

please keep author information if you redistribute this program

**********************************/

#include "UtilsTaskBase.h"


void launchAppObject( QString uid )
{
	if ( uid.isEmpty() ) return;
	
	AM_LauncherClient::launchAppObject( uid );
}

bool processIsRuning(int pid)
{
    QString fn;
    QString s = readFileLine(fn.sprintf("/proc/%d/cmdline", pid));
    if(s.isEmpty())
        return false;
    else
        return true;
}

void loadJava(const QString &gname, bool isSD, bool isMult)
{
	if ( isMult ) 
	{
		QString exec;
		if(isSD == true)
		{
			ZConfig cfg(SD_INSTALL_DB);
			exec = cfg.readEntry(gname, "ExecId", "");
		}
		else
		{
			ZConfig cfg(PHONE_INSTALL_DB);
			exec = cfg.readEntry(gname, "ExecId", "");
		}
		system( QString("exec /usr/SYSjava/kvm -launch %1 &").arg(exec) );
	} else 
	{
		launchAppObject( gname );	
	}
	
}
