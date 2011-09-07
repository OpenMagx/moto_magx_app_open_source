/****************************************
callhelper for E8 EM30
callgui
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "setup.h"
#include "code.h"
//#include "dbhelper.h"
#include "db.h"
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>
#include <ZSingleCaptureDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZNoticeDlg.h>

Setup::Setup(QWidget* parent):ZListBox("%I%M", parent),daemonID(0xd30fb72b,0xd284,0x4ca0,0x8b,0x00,0xe4,0xee,0x1f,0x3b,0xa7,0xf1)
{
	conf = new ZConfig(getAppDir()+"incalladd.ini", true);
	sysreg = new ZConfig("/ezxlocal/download/appwrite/am/InstalledDB",true);

	search = new ZSettingItem(this);
	search->appendSubItem(1,tr("Incall Location Enquiry"));
	//search->setPixmap(0, QPixmap(getAppDir()+"img/attrib.png"));
	insertItem(search);


    state = new ZSettingItem(this);
	//state->setPixmap(0, QPixmap(getAppDir()+"img/state.png"));
	insertItem(state);

	//allowgoout = new ZSettingItem(this);
	//allowgoout->setPixmap(0, QPixmap(getAppDir()+"img/go.png"));
	//insertItem(allowgoout);

	showno = new ZSettingItem(this);
	insertItem(showno);	

  	reg = new ZSettingItem(this);
 	insertItem(reg);
  	numberDlg = new ZSingleCaptureDlg(tr("Incall Location Enquiry"),tr("Please input phone No.:"),ZSingleCaptureDlg::TypeLineEdit,NULL,"A", true, 0, 0);

	
	callrecord = new ZSettingItem(this);
	insertItem(callrecord);
	
	ipedit = new ZSettingItem(this);
	insertItem(ipedit);
	connect(this, SIGNAL(selected(int)), this, SLOT(slotSelect(int)));
	loadConfig();
}

void Setup::slotSelect(int index)
{
    switch(index)
    {
		case 0:
	  	  		showSearch();
				break;
        case 1:
				showState();
        		break;
       /* case 2:
 				showAllowgo();
	   			break;*/
		case 2:
				showShowno();
				break;
        case 3:
				showAutorun();
				break;
		case 4:
				showCallRecord();
				break;
		case 5:
				showIpEdit();
				break;
		default:
        break;
         
    }
}

void Setup::showSearch()
{
		numberDlg->getLineEdit()->clear();
		if(!numberDlg->exec()) return;
	    QString num = numberDlg->getResultText();	    
		SqlHelp sql;
		QString title = sql.search(num);
	    ZMessageDlg* showQDlg = new ZMessageDlg(tr("Inquiry Result"), QString::fromUtf8(title), (ZMessageDlg::MessageDlgType)2);
	    showQDlg->exec();
	    delete showQDlg;
}

void Setup::showState()
{
        if(status)
        {
            QCopChannel::send("/EZX/CALL_ASSISTANT", "Quit");
			state->setSubItem(1, 0, tr("Runing State: Stop"));
        }
        else
        {
            QString cmd = QString("%1%2").arg(getAppDir()).arg("calldaemon");
		   	int pid = fork();
			if(pid ==-1)
			return;
			else if(pid==0)
			execl(cmd, cmd, NULL);
			ZNoticeDlg *ndlg = new ZNoticeDlg(ZNoticeDlg::Information, tr(""), tr("loading..."));
			ndlg->setAutoDismissTime(7000);
			ndlg->exec();
			state->setSubItem(1,  0, tr("Runing State: Runing"));
       }
		status = !status;
}

/*void Setup::showAllowgo()
{
       if(allowgo)
        {
			conf->writeEntry("CONFIG","allowout", 0);
            allowgoout->setSubItem(1,0,ctr("限制呼出： 开启"));
	    }
		else
        {
			conf->writeEntry("CONFIG","allowout", 1);
            allowgoout->setSubItem(1,0,ctr("限制呼出： 关闭"));
        }
		allowgo=!allowgo;
		conf->flush();
        QCopChannel::send("/EZX/CALL_ASSISTANT", "RefreshConfig");
}*/


void Setup::showShowno()
{
	if(!bool_showno)
	{
		conf->writeEntry("CONFIG", "showno", 1);
		showno->setSubItem(1,0,tr("Show No.:  Yes"));
	}
	else
	{
		conf->writeEntry("CONFIG", "showno", 0);
		showno->setSubItem(1,0,tr("Show No.:  No"));
	}
	bool_showno=!bool_showno;
	conf->flush();
	QCopChannel::send("/EZX/CALL_ASSISTANT", "RefreshConfig");

}

void Setup::showAutorun()
{
        if(autorun)
        {
            AM_AppRegistry *regtmp1 = new AM_AppRegistry(NULL);
            regtmp1->init();
            regtmp1->setAutoStartEnabled(daemonID,false);
            delete regtmp1;
            reg->setSubItem(1,0,tr("AutorunWhenPoweron:  No"));
        }
        else
        {
            writeAppRegistry();
            AM_AppRegistry *regtmp2 = new AM_AppRegistry(NULL);
            regtmp2->init();
            regtmp2->setAutoStartEnabled(daemonID,true);
            delete regtmp2;
            reg->setSubItem(1,0,tr("AutorunWhenPoweron:  Yes"));
        }
        autorun=!autorun;
        conf->writeEntry("CONFIG","AutoRun",autorun);
}

void Setup::showCallRecord()
{
	if(switchcallrecord)
	{
		conf->writeEntry("CONFIG", "switchcallrecord", 0);
		callrecord->setSubItem(1,0,tr("Switch CallRecord:  No"));
	}
	else
	{
		conf->writeEntry("CONFIG", "switchcallrecord", 1);
		callrecord->setSubItem(1,0,tr("Switch CallRecord:  Yes"));
	}
	switchcallrecord=!switchcallrecord;
	conf->flush();
	QCopChannel::send("/EZX/CALL_ASSISTANT", "RefreshConfig");
}

void Setup::showIpEdit()
{
	ZMessageDlg* dlg = new ZMessageDlg(tr("IP List"), tr("manager IP"), ZMessageDlg::TypeChoose);
	dlg->setSoftkeyText(tr("increase"), tr("manage"));
	if(dlg->exec()==ZPopup::Accepted)
	{
		ZSingleCaptureDlg *cdlg= new ZSingleCaptureDlg(tr("IP List"), tr("please input the ip:"),ZSingleCaptureDlg::TypeLineEdit,NULL,"A", true, 0, 0);
		if(cdlg->exec()) 
		{
			QString num = cdlg->getResultText();
			if(num!=QString::null)
			{
				iplist<<num;
				conf->writeEntry("IP", "iplist", iplist,QChar(';'));	
				conf->flush();
			}
			delete cdlg;
		}
	}
	else
	{
		ZSingleSelectDlg *sdlg = new ZSingleSelectDlg(this);
		sdlg->setSoftkeyText(tr("delete"),tr("cancel"));
		sdlg->addItemsList(iplist);
		if(sdlg->exec()==ZPopup::Accepted)
		{
			iplist.remove(iplist[sdlg->getCheckedItemIndex()]);
			conf->writeEntry("IP", "iplist", iplist, QChar(';'));
			conf->flush();
		}
		delete sdlg;
	}
	delete dlg;
	QCopChannel::send("/EZX/CALL_ASSISTANT", "RefreshConfig");
}

Setup::~Setup()
{
    delete conf;
    delete numberDlg;
}

void Setup::loadConfig()
{
    status = QCopChannel::isRegistered("/EZX/CALL_ASSISTANT");
	if(status)
		state->appendSubItem(1, tr("Runing State: Runing"));
	else
		state->appendSubItem(1, tr("Runing State: Stop"));
		
    //allowgo = conf->readBoolEntry("CONFIG","allowout");
	/*if(allowgo)
		allowgoout->appendSubItem(1,ctr("限制呼出： 关闭"));
	else
		allowgoout->appendSubItem(1,ctr("限制呼出： 开启"));*/

	bool_showno = conf->readBoolEntry("CONFIG", "showno");
	if(bool_showno)
		showno->appendSubItem(1, tr("Show No.:  Yes"));
	else
		showno->appendSubItem(1, tr("Show No.:  No"));

    AM_AppRegistry *regtmp3 = new AM_AppRegistry(NULL);
    regtmp3->init();
    regtmp3->isAutoStartEnabled(daemonID,autorun);
    delete regtmp3;
	
	reg->appendSubItem(1, autorun?tr("AutorunWhenPoweron:  Yes"):tr("AutorunWhenPoweron:  No"));	
	switchcallrecord = conf->readBoolEntry("CONFIG", "switchcallrecord");
	callrecord->appendSubItem(1, switchcallrecord?tr("Switch CallRecord:  Yes"):tr("Switch CallRecord:  No"));
	
	iplist = conf->readListEntry("IP", "iplist", QChar(';'));
	ipedit->appendSubItem(1, tr("Ip Editor"));

}

void Setup::writeAppRegistry()
{
    QString qsID = daemonID.toString();
    QString tmp = qsID;
    qsID.remove(0,1);
    qsID.remove(36,37);
   // qDebug(qsID);
    sysreg->writeEntry(qsID,"AniIcon","icon.png");
    sysreg->writeEntry(qsID,"AppID",tmp);
    sysreg->writeEntry(qsID,"AppType",0);
    sysreg->writeEntry(qsID,"Args","");
    sysreg->writeEntry(qsID,"Attribute",2);
    sysreg->writeEntry(qsID,"BigIcon","icon.png");
    sysreg->writeEntry(qsID,"Daemon",0);
    sysreg->writeEntry(qsID,"Directory",getAppDir());
    sysreg->writeEntry(qsID,"ExecId","calldaemon");
    sysreg->writeEntry(qsID,"GroupID","root");
    sysreg->writeEntry(qsID,"Icon","icon.png");
    sysreg->writeEntry(qsID,"LockEnabled",1);
    sysreg->writeEntry(qsID,"Name","Call Daemon");
    sysreg->writeEntry(qsID,"NameResourceId","");
    sysreg->writeEntry(qsID,"ObjectType",2);
    sysreg->writeEntry(qsID,"SVGIcon","icon.png");
    sysreg->writeEntry(qsID,"SimpleIcon","icon.png");
    sysreg->writeEntry(qsID,"UserID","root");
}



