#include "PYDB.h"

QString find_result;//全局结果
QString find_resultori;//全局结果
int LoadInfo(void *para, //db
		int n_column, //记录的列数目
		char** column_value,//查出值
		char** column_name)//字段名称
{
	int i;
	find_result=QString("");
	find_result+=column_value[1];
	find_resultori=QString("");
	find_resultori+=column_value[0];
	return 0;
}

//-----------------------------------------------------------------------
PYDB::PYDB(QString filename)
{
	dbname=filename;
	result=QString("");
	db=NULL;mrrmsg = 0; 
	int rc = sqlite3_open(filename.latin1(), &db);
	if(rc)
	{ 
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); 
		sqlite3_close(db);
	} 
	else 
	{
		//printf("open successfully!\n"); 
	}
}
//----------------------------------------------------------------------------------------
PYDB::~PYDB()
{
	sqlite3_close(db);
}
//----------------------------------------------------------------------------------------
void PYDB::find(QString table,QString tittle,QString src)
{
	result=QString("");find_result=QString("");
	resultori=QString("");find_resultori=QString("");
	if(src.length()!=0)
	{
		sqlite3_exec(db,QString("select * from %1 where %2='%3'").arg(table).arg(tittle).arg(src).latin1(),LoadInfo,NULL,&mrrmsg);
	}
	else find_result="";
	result=find_result;
	resultori=find_resultori;
}
//----------------------------------------------------------------------------------------
void PYDB::add(QString table,QString tittle,QString src)
{
	//result=QString("");find_result=QString("");
	if(table.length()!=0&&src.length()!=0&&tittle.length()!=0)
	{
		sqlite3_exec(db,QString("insert into %1 values('%2','%3');").arg(table).arg(tittle).arg(src).latin1(),LoadInfo,NULL,&mrrmsg);
	}
	//cout<<"sql:"<<QString("insert into %1 values('%2','%3');").arg(table).arg(tittle).arg(src).latin1()<<endl;
	//else find_result="";
	//result=find_result;
}
//----------------------------------------------------------------------------------------
void PYDB::update(QString table,QString tittle,QString src,QString tittle2,QString src2)
{
	//result=QString("");find_result=QString("");
	if(table.length()!=0&&src.length()!=0&&tittle.length()!=0)
	{
		sqlite3_exec(db,QString("update %1 set %2 ='%3' where %4='%5';").arg(table).arg(tittle).arg(src).arg(tittle2).arg(src2).latin1(),LoadInfo,NULL,&mrrmsg);
	}
	else find_result="";
	//cout<<"sql:"<<QString("update %1 set %2 ='%3' where %4='%5';").arg(table).arg(tittle).arg(src).arg(tittle2).arg(src2).latin1()<<endl;
	//result=find_result;
}
//----------------------------------------------------------------------------------------
