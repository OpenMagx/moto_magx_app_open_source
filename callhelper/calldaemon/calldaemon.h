/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef _GETCALL_H_
#define _GETCALL_H_
#include <TAPI_General.h>
#include <TAPI_AppMsg.h>
#include <TAPI_AppMsgId.h>
#include <TAPI_VOICE_Client.h>
#include <TAPI_CLIENT_Func.h>
#include <TAPI_CALL_General.h>
#include <TAPI_VOICE_AppData.h>
#include <TAPI_Result.h>
#include <TAPI_CALL_Client.h>
#include <iostream>

#include <ZKbMainWidget.h>
#include <ZHeader.h>
#include <ZConfig.h>
#include <qtimer.h>
#include <ZGlobal.h>

#include<stdlib.h>
#include<sys/types.h>
#include "recordwidget.h"

using namespace std;

#define ctr QString::fromUtf8


class CallDaemon:public QObject 
{
    Q_OBJECT
    public:
        CallDaemon();
        ~CallDaemon();
    public slots:
        void slotSysMsg(const QCString &msg, const QByteArray &data);
        void slotInComingCall(const QCString &msg, const QByteArray &data);
        void slotOutGoingCall(const QCString &msg, const QByteArray &data);
        void slotCheckCallStatus();
		void slotRecordMsg(const QCString &msg, const QByteArray &data);
		void slotCome();
    private:
        QString mode; //firmwallmode  DropAll Black White
        //bool fired;
  		//bool allowout;
		bool showno;
        //QString ignorewav; //fan hui yin
       // QStringList blacklist;
       // QStringList whitelist;	
        QStringList iplist;
        TAPI_CALL_SESSION_TABLE_S *pSession;
        //ZKbMainWidget* w;
		ZHeader *w;
		RecordWidget *rc_widget;
        INT32 call_fd ;
        //ZConfig *conf;
        QTimer *timer;
		QTimer *timer2;
		bool switchrc;
		bool answered;
    private:
        void loadConfig(); 
        //void ignore(UINT8*);
		void strcutip(QString&);
};
#endif
