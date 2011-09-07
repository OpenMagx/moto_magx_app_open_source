/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#ifndef _GETDATA_H_
#define _GETDATA_H_
#include "ZDataSessionManager.h"
#include "qsocket.h"
#include <ZConfig.h> 
#include <qcanvas.h>


class GetData : public QObject
{
Q_OBJECT
public:
	GetData(QString);
	~GetData();
	bool init();
	void destroy();
	void setCityid(QString);

signals:
	/*3 init error 4 openlinkerror 5 readdataerror
	0 1 2 host error
	*/
	void signalError(int);
	void signalStat(int);
	void signalFindHost();
	void success();
public slots:
	void zconnected(int linkid, ZLinkInfo&);
	void slothostFound();
	void sloterror(int);
	void slotconnectionClosed();
	void slotconnected();
	void slotreadyRead();
private slots:
	void slotStat(int);
private:
	bool checkProfile();
	QString cityid;
	void loadConfig();
	QSocket *socket;
	ZDataSessionManager *zd;
	int linkID;
	QString wstr;
	QString profile;
	ZConfig *conf;
	ZConfig *infoconf;
	int i;
};
#endif


