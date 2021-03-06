/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef _RECORD_WIDGET_H_
#define _RECORD_WIDGET_H_
#include <ZKbMainWidget.h>
#include <ZNavTabWidget.h>
#include <ZOptionsMenu.h>
#include <ZSoftKey.h>
#include <qlist.h>
#include "recordlist.h"
#include <ZConfig.h>
#include <RES_ICON_Reader.h>

class RecordWidget:public ZKbMainWidget
{
Q_OBJECT
public:
	RecordWidget();
	~RecordWidget();
	void keyPressEvent(QKeyEvent *e);
	void showN();
private:
	RES_ICON_Reader iconReader;
    ZNavTabWidget* znt;
    ZSoftKey* zsk;
    ZOptionsMenu* zom;	
	RecordListBox* tab1;
	RecordListBox* tab2;
	RecordListBox* tab3;
	//QList<RC_RecordInterface>*  unanseredlist;
	//QList<RC_RecordInterface>*  calledlist;
	//QList<RC_RecordInterface>*  answeredlist;
private slots:
    void slotSetArea(QWidget*);
	void slotEditIp();
	void slotFresh();
public slots:
	void refresh();
	void refreshCalled();
	void refreshAns();
	void refreshUnAns();

};
#endif
