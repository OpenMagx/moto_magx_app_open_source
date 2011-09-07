/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "calldaemon.h"
#include <qcopchannel_qws.h>
#include <qdatetime.h>
#include "db.h"

extern bool UTIL_setWidgetPriority(QWidget *,int);

QString getProgramDir()
{
    QString m_sProgramDir = QString ( qApp->argv() [0] ) ;
    int i = m_sProgramDir.findRev ( "/" );
    m_sProgramDir.remove ( i+1, m_sProgramDir.length() - i );
    return m_sProgramDir;
}

CallDaemon::CallDaemon()
{
    //fired = false;
    //load config
   // conf = new ZConfig(getProgramDir()+"incalladd.ini", true);
    answered=false;
    loadConfig();
    //create tapi client
    TAPI_APP_MSGID_T msg_id[] = { TAPI_APP_ASYNC_VOICECALL_MSG_GRPID };
    pSession = new TAPI_CALL_SESSION_TABLE_S;
    call_fd  = TAPI_CLIENT_Init(msg_id, sizeof(msg_id) / sizeof(TAPI_APP_MSGID_T));
    //w = new ZHeader(ZHeader::MAINDISPLAY_HEADER, 0, "", WStyle_Tool);
	w = new ZHeader(ZHeader::MAINDISPLAY_HEADER, 0,"", WStyle_Tool);
	w->setGeometry(ZGlobal::getHeaderR());
	rc_widget = new RecordWidget();
    //UTIL_setWidgetPriority(w,7);
    //create channel
    QCopChannel *outchnl = new QCopChannel("/EZX/PHONE/OUTGOING_CALL",this);
    QCopChannel *inchnl = new QCopChannel("/EZX/PHONE/INCOMING_CALL",this);
    QCopChannel *syschnl = new QCopChannel("/EZX/CALL_ASSISTANT",this);
	QCopChannel *recordchnl = new QCopChannel("LJ/IdleToPhoneChannel",this);
    connect(outchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(slotOutGoingCall(const QCString &, const QByteArray &)));
    connect(inchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(slotInComingCall(const QCString &, const QByteArray &)));
    connect(syschnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(slotSysMsg(const QCString &, const QByteArray &)));
	connect(recordchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(slotRecordMsg(const QCString &, const QByteArray &)));
	
    //create a timer for outgoing call status check
    timer = new QTimer(this);
	timer2 = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slotCheckCallStatus()));
	connect(timer2,SIGNAL(timeout()), this, SLOT(slotCome()));
}

void CallDaemon::slotCheckCallStatus()
{
    TAPI_CALL_STATUS_E status;
    TAPI_VOICE_GetCallStatus(pSession->session->appCallId,pSession->session->callType,&status);
    if(status==TAPI_CALL_STATUS_CONNECTED_EV || status==TAPI_CALL_STATUS_IDLE_EV)
    {
        timer->stop();
        w->hide();
		//QTimer::singleShot(500,rc_widget,SLOT(refresh()));
		//system("/usr/SYSqtapp/phone/vibrateprocess");
    }
}

void CallDaemon::slotCome()
{
	TAPI_CALL_STATUS_E status;
    TAPI_VOICE_GetCallStatus(pSession->session->appCallId,pSession->session->callType,&status);
	 if(status==TAPI_CALL_STATUS_CONNECTED_EV)
	 {
		answered = true;
	 }
    if(status==TAPI_CALL_STATUS_IDLE_EV)
    {
        timer2->stop();
		if(answered)
		QTimer::singleShot(1000,rc_widget,SLOT(refreshAns()));
		else
		QTimer::singleShot(1000,rc_widget,SLOT(refreshUnAns()));
		answered=false;
		//system("/usr/SYSqtapp/phone/vibrateprocess");
    }
}

CallDaemon::~CallDaemon()
{
    TAPI_CLIENT_Fini();
    delete w;
    delete pSession;
}

void CallDaemon::strcutip(QString& number)
{
	for(unsigned int j = 0; j<iplist.count(); j++)
    {
        if(number.startsWith(iplist[j]))
            number = number.mid(iplist[j].length(),15);
    }
}

void CallDaemon::loadConfig()
{
	ZConfig conf(getProgramDir()+"incalladd.ini", true);
	//allowout = conf.readBoolEntry("CONFIG","allowout");
	showno = conf.readBoolEntry("CONFIG", "showno");
	switchrc = conf.readBoolEntry("CONFIG", "switchcallrecord");
    //ignorewav = conf.readEntry("FIREWALL","ignorewav");
    //mode = conf.readEntry("FIREWALL", "mode");
	qDebug(mode);
    //blacklist = conf.readListEntry("FIREWALL", "blacklist", QChar(';'));
    //whitelist = conf.readListEntry("FIREWALL", "whitelist", QChar(';'));
    iplist = conf.readListEntry("IP", "iplist", ';');
}

void CallDaemon::slotSysMsg(const QCString &msg, const QByteArray &)
{
    if(msg == "RefreshConfig")
    {
				//conf->flush();
        qDebug("refreshconfig");
        loadConfig();
    }
    if(msg == "Quit")
    {
        qDebug("qapp->quit");
        qApp->quit();
    }
}

/*void CallDaemon::ignore(UINT8* phoneNum)
{
    if(ignorewav == "busy")
        TAPI_VOICE_RejectCall(pSession->session->appCallId, TAPI_VOICE_REJECT_CALL_BUSY_EV);
    else if(ignorewav == "ignore")
        TAPI_VOICE_RejectCall(pSession->session->appCallId, TAPI_VOICE_REJECT_CALL_IGNORE_EV);
	else 
		TAPI_VOICE_CancelCall(pSession->session->appCallId);
    RECORD r;
    QString dbpath = getProgramDir()+"record.db";
    r.phoneNum = (char*)phoneNum;
    r.date = QDate::currentDate().toString();
    r.time = QTime::currentTime().toString();
    if(opendb(dbpath)==0)
    {	
        insertdb(r);
    }
}*/

void CallDaemon::slotInComingCall(const QCString &msg, const QByteArray &)
{
    if(msg == "ON")
    {
      //  bool fired = false;
        TAPI_CALL_GetAllCallSessions(pSession);
		QString phoneNo = (char*)pSession->session->phoneNumber;

        /*if(mode == "DropAll")
        {
            ignore(pSession->session->phoneNumber);
            fired = true;
        }
        else if(mode == "Black")
        {

            for (QStringList::Iterator it = blacklist.begin();it != blacklist.end();++it)
            {
                if(phoneNo ==*it)
                {
					qDebug(*it);
                    ignore(pSession->session->phoneNumber);
                    fired = true;
                }
            }
        }
        else if(mode == "White")
        {
            int count = 0;
            for (QStringList::Iterator it = whitelist.begin();it != whitelist.end();++it)
            {
                if(phoneNo == *it)
                {
                    count++;
                }
            }
            if (count == 0) {ignore(pSession->session->phoneNumber);fired = true;}
        }

        if(!fired)
        {	*/
			QString orinumber=phoneNo;
			QString title = QString::null;
			if(phoneNo.length()<9)
			title = "本地号码";
			else
			{
				SqlHelp sql;
				title = sql.search(orinumber);
				if(title == "unknow")
				{
					title = "未知号码";
				}
			}
			
			if(showno)
			title = title + '('+ orinumber + ')';

            w->setPrimTitle(ctr(title));
            w->show();          
       // }  if!fired
    }
    else if(msg == "OFF")
    {
        w->hide();
		timer2->start(100,false);
    }			
}

void CallDaemon::slotOutGoingCall(const QCString &msg, const QByteArray &)
{
    if(msg == "MO")
    {
        
        /*if(!allowout)
        {
            TAPI_VOICE_DropAllCall();
        }
        else
        {*/
            TAPI_CALL_GetAllCallSessions(pSession);
            QString phoneNo = (char*)pSession->session->phoneNumber;
		    QString title = QString::null;
	
			strcutip(phoneNo);	
			QString orinumber = phoneNo;

			if(phoneNo.length()<9)
			{
				title = "本地号码";
			}
			else
			{
  				SqlHelp sql;
				title = sql.search(orinumber);
				if(title == "unknow")
				{
					title = "未知号码";
				}
			}
				
			if(showno)
			title = title + '('+ orinumber + ')';

            w->setPrimTitle(ctr(title));
            w->show();

            timer->start(100,false);
       // }
    }
    else if(msg == "ENDED")
    {
        w->hide();
		QTimer::singleShot(1000,rc_widget,SLOT(refreshCalled()));
    }
}


void CallDaemon::slotRecordMsg(const QCString &msg, const QByteArray &)
{		
	if(switchrc)
	{
		if(msg == "showRecentCall")
		{	
				rc_widget->showN();
				QCopChannel::send("/EZX/recentcall","RECENTCALL_MSG_7");		
		}
	}
}

