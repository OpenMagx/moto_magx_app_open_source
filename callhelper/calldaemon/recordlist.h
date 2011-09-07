/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef _RECORDLIST_H_
#define _RECORDLIST_H_
#include <ZListBox.h>
#include <RC_Interface.h>
#include <ZOptionsMenu.h>
#include <ZGlobal.h>
#include <qpoint.h>
#include "recordSettingItem.h"
#include <ZConfig.h>
#include <RecentCall_ENG_RecordStore.h>
#include <PHONE_ENG_RecentCall.h>
#include <RC_RecordInterfaceImpl.h>

class RecordListBox : public ZListBox
{
Q_OBJECT
public:
	RecordListBox(PHONE_RecentCallList, QWidget*);
	~RecordListBox();
public slots:
	void refresh(PHONE_RecentCallList);
	void sendMessage();
	void makeCall();
	void makeCallWithIp1();
	void makeCallWithIp2();
	void creatContact();
	void updateContact();
	void keyReleaseEvent(QKeyEvent*);
	void deleteRecord();
private:
	void showMenu();
	QString getCurrentFace();
	void sendMessage(QString);
	void makeCall(QString);
	void makeCallWithIp1(QString);
	void makeCallWithIp2(QString);
	void creatContact(QString);
	void updateContact(QString);
	void addItem(PHONE_ENG_RecentCall*, bool, int);
	//void deleteRecord(RcRecord* face);
	
private:
	ZConfig *conf;
	ZOptionsMenu* menu;
	ZOptionsMenu* ip_menu;
	ZOptionsMenu* contact_menu;
	QString ip1;
	QString ip2;
	//QString* call;
	RecordSettingItem* item1;
	PHONE_RecentCallList clist;
	
signals:
	void hidewidget();
	void fresh();
};

#endif


