
#include <ZApplication.h>
#include <ZConfig.h>
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>

#include <AM_LauncherClient.h>
#include <TAPI_ACCE_Client.h>

#include <qstring.h>
#include <qstringlist.h>
#include <qfile.h>
#include <qdir.h>
#include <qtextcodec.h>
#include <qtextstream.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>

#include "UtilsTools.h"

using namespace std;

QString ctr(const char*ChineseString)
{
	QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString);
}

QString getAppDir()
{
    QString tmp = QString(qApp->argv()[0]);
    int i = tmp.findRev("/");
    tmp.remove(i+1,tmp.length()-1);
    return tmp;
}

QString getIMEI()
{
	QString result = QString::null;

	unsigned int res;
	TAPI_IMEI_NUMBER_A imei;

	TAPI_CLIENT_Init ( NULL, 0 );
	res = TAPI_ACCE_GetImei ( imei );
	if ( res == 0 ) 
	{
		QString pImei = QString::fromLatin1 ( reinterpret_cast<char*> ( imei ) );
		result = pImei;
	}
	TAPI_CLIENT_Fini();
	
	return result;
}

QString getGname(int step)
{
	time_t t;
	srand( (unsigned)time(&t) );
	
	srand(time(NULL));

    int data[8];
    QString uuid;

    for (int i = 0; i < 8; ++i) {
        data[i] = rand() % step;//255;
    }

    // So you know it was created
    // It starts and ends in FF
    data[0] &= 0x0;
    data[0] |= 0xff;
    data[8] &= 0x0;
    data[8] |= 0xff;

    for (int i = 0; i < 4; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
    uuid += "-";
    for (int i = 4; i < 6; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
    uuid += "-";
    for (int i = 6; i < 8; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
   
    return uuid;
}
int showQ(const QString &title, const QString &text, int type)
{
	ZMessageDlg* dlg = new ZMessageDlg(title, text, (ZMessageDlg::MessageDlgType)type);
	int ret = dlg->exec();
	delete dlg;
	dlg = NULL;
	return ret;
}

void showNotify(const QString &title, const QString &text, int type, int time)
{
	ZNoticeDlg *dlg = new ZNoticeDlg((ZNoticeDlg::Type)type, text, "");
	if(type==2) dlg->setTitleIcon("error_pop.bmp");
	dlg->setTitle(title);
	dlg->setAutoDismissTime(time*1000);
	dlg->exec();
	delete dlg;
	dlg = NULL;
}

int basename(char *str)
{
	int ret=0, k=0;
	for (; str[k]!='\0'; k++) {
		if (str[k]=='/') ret=k;
	}
	return ret+1;
}
unsigned int getDirSize(const char* path)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	unsigned int size=0;
	char newDir[256];
	if ((dp=opendir(path))==NULL) {
		return 0;
	}
	chdir(path);
	while ((entry=readdir(dp))!=NULL)
	{
		if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
		{
			stat(entry->d_name, &statbuf);
			if ((statbuf.st_mode&S_IFMT)==S_IFDIR) 	{
				sprintf(newDir, "%s/%s", path, entry->d_name);
				size+=getDirSize(newDir);
			}
			else if ((statbuf.st_mode&S_IFMT)==S_IFREG) {
				size+=statbuf.st_size;
			}
		}
	}
	return size;
}

QString size2string(unsigned long size)
{
    if (size < 1024) 
        return QString("%1 b").arg(size);
    else if (size < 1024 * 1024)
        return QString("%1 Kb").arg((double) size / 1024);
    else 
        return QString("%1 Mb").arg((double) size / 1024 / 1024);
	return "";
}

bool df2MtdFreeSize(const QString mtdKeyName, unsigned int KBLimitSize )
{
	FILE *pp;
	bool state = false;
	if( (pp = popen("df", "r")) == NULL )//system调用
	{
		printf("popen() error!\n");
		return true;
	}
	char buf[500];
			 
	while(fgets(buf, sizeof buf, pp))//读文件
	{
		QString line(buf);
		//cout<<"== cur line  "<<line<<endl;
		if( line.find(mtdKeyName) > -1 ) {
			QStringList list = QStringList::split(" ", line.stripWhiteSpace() );
			//QStringList::ConstIterator p;
			//for (p = list.begin(); p != list.end(); ++p) {
			//	cout<<"list data   "<<*p<<endl;
			//}	
			cout<<"target data "<<list[3]<<endl;
			if( list[3].toUInt() < KBLimitSize ) 
				state = true;
			else
				state = false;		
		}
	}		
	pclose(pp);	 
	return state;
}
unsigned int getDf2MtdFreeSize(const QString mtdKeyName)
{
	FILE *pp;
	unsigned int size = 0;
	if( (pp = popen("df", "r")) == NULL )//system调用
	{
		printf("popen() error!\n");
		return 0;
	}
	char buf[500];
			 
	while(fgets(buf, sizeof buf, pp))//读文件
	{
		QString line(buf);
		//cout<<"== cur line  "<<line<<endl;
		if( line.find(mtdKeyName) > -1 ) {
			QStringList list = QStringList::split(" ", line.stripWhiteSpace() );
			//QStringList::ConstIterator p;
			//for (p = list.begin(); p != list.end(); ++p) {
			//	cout<<"list data   "<<*p<<endl;
			//}
			size = list[3].toUInt();
		}
	}		
	pclose(pp);	 
	return size;
}

