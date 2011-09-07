/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "recordlist.h"
#include "db.h"
//#include "MSGCTR_ENG_StatusApi.h"
#include <MSGCTR_ENG_StatusApi.h>
#define Debug
#include <PHONE_VoiceCallInterface.h>
#include <ADDRBK_ENG_Manager.h>
#include <ADDRBK_UI.h>
#include <ZApplication.h>
#include <PHONE_ENG_RecentCall.h>
#include "code.h"
#include "PHONE_RecentCall.h"

RecordListBox::RecordListBox(PHONE_RecentCallList list, QWidget* parent):ZListBox(parent)
{
	conf = new ZConfig(getAppDir()+"incalladd.ini");
	QRect rect = ZGlobal::getSubContentR();
	menu = new ZOptionsMenu(rect ,this, "menu", 0, ZSkinService::WidgetClsID(55));
	//menu->insertItem(tr("sendMessage"), NULL, this, SLOT(sendMessage()), true, false, false, 0, 0, false);
	menu->insertItem(tr("sendMessage"), NULL, this, SLOT(sendMessage()), true, false, false, 0, 0, false);
	ip_menu = new ZOptionsMenu(rect ,menu, "ip_menu", 0, ZSkinService::WidgetClsID(55));
	ip_menu->insertItem(tr("CallingWithIp1"),NULL, this, SLOT(makeCallWithIp1()), true, false, false, 0, 0, false);
	ip_menu->insertItem(tr("CallingWithIp2"),NULL, this, SLOT(makeCallWithIp2()), true, false, false, 1, 1, false);
	menu->insertItem(tr("CallingWithIp"), ip_menu, NULL, true, 1, 1, false, false, false);
	contact_menu = new ZOptionsMenu(rect, menu, "contact_menu", 0, ZSkinService::WidgetClsID(55));
	contact_menu ->insertItem(tr("CreateContact"),NULL, this, SLOT(creatContact()), true, false, false, 0, 0, false);
	contact_menu ->insertItem(tr("UpdateContact"),NULL, this, SLOT(updateContact()), true, false, false, 1, 1, false);
	menu->insertItem(tr("SaveToContact"), contact_menu, NULL, true, 2, 2, false, false, false);
	menu->insertItem(tr("delete"),NULL,this,SLOT(deleteRecord()),true,false,false,3,3,false);
	refresh(list);
	enableMarquee((ListItemRegion)0,true);
}

RecordListBox::~RecordListBox()
{
	delete item1;
	//delete call;
	delete menu;
	delete ip_menu;
	delete contact_menu;
}

void RecordListBox::refresh(PHONE_RecentCallList list)
{
	int j = list.count();
	int k = this->count();
	/*if(j==k && k==50)
	{
		removeItem(49);
		for(int count = 0; count<50; ++count)
		{
			QString subtext = static_cast<RecordSettingItem*>(this->item(count))->getSubItemText(1, 0);
			static_cast<RecordSettingItem*>(this->item(count))->setSubItem(1, 0 ,QString("%1%2").arg(50-count).arg(subtext.mid(1)));
		}
	int i = list.count();
	PHONE_ENG_RecentCall *face;
	face=list.first();
	addItem(face, true, i);
	}
	else if(j==k)
	{
		return;
	}*/
	if(j-k==1)
	{
		int i = list.count();
		PHONE_ENG_RecentCall *face;
		face=list.first();
		addItem(face, true, i);
	}
	else
	{
		this->clear();
		PHONE_ENG_RecentCall *face;
		int i;
		for(face=list.first(), i = list.count(); face; face=list.next(), --i)
		{
			addItem(face, false, i);
		}//for
	}//else
	this->clist = list;
}

void RecordListBox::showMenu()
{
	qDebug("showmenu");
	QPoint p=itemRect(item(currentItem())).bottomRight();
	menu->setPosition(ZOptionsMenu::TopRight,p);
	menu->popup();
}

QString RecordListBox::getCurrentFace()
{
#ifdef Debug
qDebug("DEBUG::getcurrentface");
#endif
	unsigned int index=this->currentItem ();
	RecordSettingItem* current_item=static_cast<RecordSettingItem*>(this->item(index));
#ifdef Debug
qDebug("DEBUG::before getFace");
#endif
	QString interface=current_item->getFace();
#ifdef Debug
qDebug("DEBUG::getcurrentface   end");
#endif
	return interface;
}


void RecordListBox::addItem(PHONE_ENG_RecentCall* face, bool top, int i)
{
		RC_RecordInterfaceImpl *impl = new RC_RecordInterfaceImpl(face);
		QString num = impl->getPhoneNumber();
		int time = impl->getDuration();
		QDateTime dt = impl->getStartDateTime();
		QString hour;
		QString min;
		if(time<0)
		{
			hour = QString::null;
			min = QString::null;
		}
		else
		{
			QString mid;
			if((time/60)<10)
				hour = '0'+mid.setNum(time/60);
			else
				hour = mid.setNum(time/60);
			if((time%60)<10)
				min = ":0"+mid.setNum(time%60);
			else
				min = ':' + mid.setNum(time%60);
		}	
		
		
		ADDRBK_SEARCH_RESULT_S asrs;
		ADDRBK_ENG_Manager::searchByNumber(asrs, num);
		
		SqlHelp sql;
		QString title = sql.search(num);
		
		if(title == "unknow")
		{
			title = QString::null;
		}
		
		item1 = new RecordSettingItem(num, this);
		item1->appendSubItem(0, QString("%1) %2 %3 %4").arg(i).arg(asrs.name).arg(num).arg(QString::fromUtf8(title)));
		item1->appendSubItem(0, QString("%1 %2/%3/%4  %5%6").arg((dt.time()).toString()).arg(dt.date().year()).arg(dt.date().month()).arg(dt.date().day()).arg(hour).arg(min));
		if(top)
			this->insertItem(item1, 0);
		else
			this->insertItem(item1);
		delete impl;
}


void RecordListBox::keyReleaseEvent(QKeyEvent* e)
{
	if(this->count()>0)
	{
		if(e->key()==KEYCODE_CENTER_SELECT)
		showMenu();
	}
	QWidget::keyReleaseEvent (e);
}

void RecordListBox::sendMessage()
{
	emit hidewidget();
	sendMessage(getCurrentFace());
}

void RecordListBox::makeCall()
{
	emit hidewidget();
	makeCall(getCurrentFace());
}

void RecordListBox::makeCallWithIp1()
{
	emit hidewidget();
	makeCallWithIp1(getCurrentFace());
}

void RecordListBox::makeCallWithIp2()
{
	emit hidewidget();
	makeCallWithIp2(getCurrentFace());
}

void RecordListBox::creatContact()
{
	emit hidewidget();
	creatContact(getCurrentFace());
	emit fresh();
}

void RecordListBox::updateContact()
{
	emit hidewidget();
	updateContact(getCurrentFace());
	emit fresh();
}

void RecordListBox::deleteRecord()
{
	int i = this->currentItem();
	PHONE_RecentCall_DeleteRecord(*(clist.at(i)));
	clist.remove(i);
	this->clear();
	refresh(clist);
}


void RecordListBox::sendMessage(QString face)
{
	MSGCTR_ENG_StatusApi api(this, "msg");
	#ifdef Debug
	//qDebug(face->getPhoneNumber());
	#endif
	api.gotoScreenOfComposingNewMsg(face,QString::null);	
}

void RecordListBox::makeCall(QString face)
{
	char a[20];
	sprintf(a,face);
	PHONE_MakeVoiceCall(a) ; 
}

void RecordListBox::makeCallWithIp1(QString face)
{
	ip1 = conf->readEntry("IP","ip1");
	QString num = ip1+face;
	char a[20];
	sprintf(a,num);
	PHONE_MakeVoiceCall(a) ; 
}

void RecordListBox::makeCallWithIp2(QString face)
{
	ip2 = conf->readEntry("IP","ip2");
	QString num = ip2+face;
	char a[20];
	sprintf(a,num);
	PHONE_MakeVoiceCall(a) ; 
}

void RecordListBox::creatContact(QString face)
{
	QString num = face;
	ADDRBK_UI::newContact(ADDRBK_UI::FIELD_NUMBER,num);
}

void RecordListBox::updateContact(QString face)
{
	ADDRBK_UI::addDataToContact(ADDRBK_UI::FIELD_NUMBER,face);	
}

/*void RecordListBox::deleteRecord(QString* face)
{
	PHONE_ENG_RecentCall *call = new PHONE_ENG_RecentCall;
	call->setPhoneNumber(face->getPhoneNumber());
	call->setStartDateTime(face->getStartDateTime());
	call->setDuration(face->getDuration());
}*/









