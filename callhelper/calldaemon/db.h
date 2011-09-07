/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef _DB_H_
#define _DB_H_
extern "C"
{
#include "sqlite3.h"
#include "sqlite3ext.h"
};
#include <qstring.h>
//#include "sqlite3ext.h"


class SqlHelp
{
public:
	SqlHelp();
	~SqlHelp();
	bool openDb(QString dbname);
	bool execute(QString sql);
	QString search(QString number);
	bool closeDb();
private:
	QString strcut(QString);
	QString dbpath;
	sqlite3 *db;
	int flag;
};









#endif
