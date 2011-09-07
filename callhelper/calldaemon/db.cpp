/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "db.h"
#include "code.h"
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#include <qobject.h>

SqlHelp::SqlHelp()
{
	dbpath = getAppDir()+"callinfo.db";
	flag=false;
}

SqlHelp::~SqlHelp()
{
	if(flag)
	this->closeDb();
}

bool SqlHelp::openDb(QString dbpath)
{
	if(sqlite3_open(dbpath, &db)==SQLITE_OK)
	{
		flag=true;
		return true;
	}
	return false;
}

bool SqlHelp::closeDb()
{
	flag=false;
	sqlite3_close(db);
	return true;
}


bool SqlHelp::execute(QString sql)
{
	return true;
}

QString SqlHelp::search(QString number)
{
	QString res = QString::null;
	char **dbresult;
	int nrow, ncolumn;
	char **dbresult1;
	int nrow1, ncolumn1;
	char **errmsg=NULL;
	QString str = strcut(number);
	if(openDb(dbpath))
	{
		QString sql1 = QString("select name from region where id=(select regionid from call where number=%1)").arg(str);
		QString sql2 = QString("select name from city where id=(select cityid from call where number=%1)").arg(str);
		if(sqlite3_get_table(db,sql1,&dbresult,&nrow,&ncolumn,errmsg)==SQLITE_OK)
		{
			if(ncolumn>0)
			res = dbresult[1];
			if(sqlite3_get_table(db,sql2,&dbresult1,&nrow1,&ncolumn1,errmsg)==SQLITE_OK)
			{
				if(ncolumn>0)
				res+=dbresult1[1];
			}
			else
			return QObject::tr("inquiry error");
		}
		else
		return QObject::tr("inquiry error");
	}
	else
	{
		return QObject::tr("Open database failed");
	}
	
	if(res==QString::null)
	{
		return QObject::tr("unknow");
	}
	return res;
}


QString SqlHelp::strcut(QString number)
{
    QString qstr = number;
    /*for(unsigned int j = 0; j<iplist.count(); j++)
    {
        if(qstr.startsWith(iplist[j]))
            qstr = qstr.mid(iplist[j].length(),7);
    }*/
    if(qstr.startsWith("01")||qstr.startsWith("02"))
        qstr = qstr.mid(1, 2);
    else if(qstr.startsWith("1"))
        qstr = qstr.left(7);
    else 
        qstr = qstr.mid( 1, 3 );
    return qstr;
}
