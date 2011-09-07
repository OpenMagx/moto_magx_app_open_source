#ifndef _PYDB_H_
#define _PYDB_H_

#include <qstring.h>
#include <sqlite3.h>
#include <iostream>
using namespace std;


class PYDB
{
public:
	QString dbname;//数据库名
	QString result;//查找结果
	QString resultori;
	sqlite3 *db;//数据库
	char *mrrmsg;//错误信息
public:
	PYDB(QString filename);
	~PYDB();
	void find(QString table,QString tittle,QString src);
	void add(QString table,QString tittle,QString src);
	void update(QString table,QString tittle,QString src,QString tittle2,QString src2);
};

#endif// PYDB_H_
