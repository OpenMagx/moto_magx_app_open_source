/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "recordwidget.h"
//#include "RC_Interface.h"
#include "code.h"
#include "RecentCall_ENG_RecordStore.h"
#include "PHONE_ENG_RecentCall.h"
#include "ZKeyDef.h"
#include "ZSingleSelectDlg.h"
#include "ZSingleCaptureDlg.h"
#define DEBUG

RecordWidget::RecordWidget() : ZKbMainWidget(ZHeader::MAINDISPLAY_HEADER)
{
	#ifdef DEBUG
	qDebug("DEBUG::   recordwidget start...");
	#endif
	znt = new  ZNavTabWidget(this, 0, (ZSkinService::WidgetClsID)63);
	znt->stopNextWhenKeyRepeat(false);
	connect(znt, SIGNAL(currentChanged(QWidget*)) , this , SLOT(slotSetArea(QWidget*)));
	
	RecentCall_ENG_RecordStore  p;

	PHONE_RecentCallList  unanseredlist;
	PHONE_RecentCallList  calledlist;
	PHONE_RecentCallList  answeredlist;
	#ifdef DEBUG
	qDebug("DEBUG::   get record list...");
	#endif
	p.readDataList(unanseredlist,RC_CALL_CATEGORY_UNANSWERED);
	p.readDataList(calledlist,RC_CALL_CATEGORY_CALLED);
	p.readDataList(answeredlist,RC_CALL_CATEGORY_ANSWERED);
	#ifdef DEBUG
	qDebug("DEBUG::   get record list end...");
	#endif
	tab3 = new RecordListBox(unanseredlist,this);
	tab1 = new RecordListBox(calledlist,this);
	tab2 = new RecordListBox(answeredlist,this);
	tab1->setFocus();
	#ifdef DEBUG
	qDebug("DEBUG::   tabend...");
	#endif
	//QPixmap map
	znt->addTab(tab1,  iconReader.getIcon("recnt_dial_call_tab.png"), "tab1");
	znt->addTab(tab2,  iconReader.getIcon("recnt_receive_call_tab.png"), "tab2");
	znt->addTab(tab3,  iconReader.getIcon("recnt_missed_call_tab.png"), "tab3");
	setContentWidget(znt);
	#ifdef DEBUG
	qDebug("DEBUG::   addtabend...");
	#endif

	zsk = new ZSoftKey("CST_2A",this);
	setSoftKey(zsk);
	
	QRect rect=ZGlobal::getContentR();
	zom=new ZOptionsMenu(rect, this, 0, 0, ZSkinService::WidgetClsID(55));
	zom->insertItem(tr("EditIp"), NULL, this, SLOT(slotEditIp()), true, false, false, 0);
	zom->insertItem(tr("fresh"),NULL, this, SLOT(slotFresh()),true, false, false, 0);
	
	
	zsk->setTextForOptMenuHide(tr("options"));
	zsk->setTextForOptMenuShow(tr("select"),tr("cancel"));
	zsk->setText(ZSoftKey::LEFT, tr("options"));
	zsk->setText(ZSoftKey::RIGHT, tr("cancel"));
	zsk->setOptMenu(ZSoftKey::LEFT, zom);
	zsk->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(hide()));
	#ifdef DEBUG
	qDebug("DEBUG::   record list end...");
	#endif
	connect(tab1, SIGNAL(hidewidget()), this, SLOT(hide()));
	connect(tab2, SIGNAL(hidewidget()), this, SLOT(hide()));
	connect(tab3, SIGNAL(hidewidget()), this, SLOT(hide()));
	connect(tab1, SIGNAL(fresh()), this, SLOT(slotFresh()));
	connect(tab2, SIGNAL(fresh()), this, SLOT(slotFresh()));
	connect(tab3, SIGNAL(fresh()), this, SLOT(slotFresh()));
}
RecordWidget::~RecordWidget()
{
	delete znt;
	delete zsk;
	delete zom;
	delete tab1;
	delete tab2;
	delete tab3;
}

void RecordWidget::showN()
{
	tab1->setCurrentItem(0);
	znt->setCurrentPage(0);
	show();
}

void RecordWidget::slotSetArea(QWidget*)
{
	switch(znt->currentPageIndex())
	{
		case 0:
			setAppTitle(tr("Called"));
			break;
		case 1:
			setAppTitle(tr("Answered Call"));
			break;
		case 2:
			setAppTitle(tr("Unanswered Call"));
		default:
			break;
	}
}


void RecordWidget::refresh()
{
	RecentCall_ENG_RecordStore  p;

	PHONE_RecentCallList  unanseredlist;
	PHONE_RecentCallList  calledlist;
	PHONE_RecentCallList  answeredlist;
	
	p.readDataList(unanseredlist,RC_CALL_CATEGORY_UNANSWERED);
	p.readDataList(calledlist,RC_CALL_CATEGORY_CALLED);
	p.readDataList(answeredlist,RC_CALL_CATEGORY_ANSWERED);
	
	
	tab3->refresh(unanseredlist);
	tab1->refresh(calledlist);
	tab2->refresh(answeredlist);
}

void RecordWidget::refreshCalled()
{
	RecentCall_ENG_RecordStore  p;
	PHONE_RecentCallList  calledlist;
	p.readDataList(calledlist,RC_CALL_CATEGORY_CALLED);
	tab1->refresh(calledlist);

}
void RecordWidget::refreshAns()
{
	RecentCall_ENG_RecordStore  p;
	PHONE_RecentCallList  answeredlist;
	p.readDataList(answeredlist,RC_CALL_CATEGORY_ANSWERED);
	tab2->refresh(answeredlist);
}
void RecordWidget::refreshUnAns()
{
	RecentCall_ENG_RecordStore  p;
	PHONE_RecentCallList  unanseredlist;
	p.readDataList(unanseredlist,RC_CALL_CATEGORY_UNANSWERED);
	tab3->refresh(unanseredlist);
}
void RecordWidget::slotFresh()
{
	RecentCall_ENG_RecordStore  p;

	PHONE_RecentCallList  unanseredlist;
	PHONE_RecentCallList  calledlist;
	PHONE_RecentCallList  answeredlist;
	
	p.readDataList(unanseredlist,RC_CALL_CATEGORY_UNANSWERED);
	p.readDataList(calledlist,RC_CALL_CATEGORY_CALLED);
	p.readDataList(answeredlist,RC_CALL_CATEGORY_ANSWERED);
	
	tab1->clear();
	tab2->clear();
	tab3->clear();
	
	tab3->refresh(unanseredlist);
	tab1->refresh(calledlist);
	tab2->refresh(answeredlist);
}

void RecordWidget::slotEditIp()
{
	ZConfig conf(getAppDir()+"incalladd.ini");
	QString ip1 = conf.readEntry("IP", "ip1");
	QString ip2 = conf.readEntry("IP", "ip2");
	ZSingleSelectDlg *sdlg = new ZSingleSelectDlg(this);
	QStringList list;
	list << "ip1= " + ip1 << "ip2= "+ip2;
	sdlg->setSoftkeyText(tr("edit"), tr("cancel"));
	sdlg->addItemsList(list);
	if(sdlg->exec()==ZPopup::Accepted)
	{
		int i = sdlg->getCheckedItemIndex();
		if(i==0)
		{
			ZSingleCaptureDlg *cdlg= new ZSingleCaptureDlg(tr("IP Edit"),tr("ip1 = "),ZSingleCaptureDlg::TypeLineEdit,NULL,"A", true, 0, 0);
			if(cdlg->exec())
			{
				ip1 = cdlg->getResultText();
				conf.writeEntry("IP", "ip1", ip1);
				conf.flush();
			}
			delete cdlg;
		}
		else if(i==1)
		{
			ZSingleCaptureDlg *cdlg= new ZSingleCaptureDlg(tr("IP Edit"),tr("ip2 = "),ZSingleCaptureDlg::TypeLineEdit,NULL,"A", true, 0, 0);
			if(cdlg->exec())
			{
				ip2 = cdlg->getResultText();
				conf.writeEntry("IP", "ip2", ip2);
				conf.flush();
			}
			delete cdlg;
		}
	}
	delete sdlg;
}

void RecordWidget::keyPressEvent(QKeyEvent *e)
{
	if(e->key()==KEYCODE_SEND)
	{
		(static_cast<RecordListBox*>(znt->currentPage()))->makeCall();
	}
	else if(e->key()==KEYCODE_END)
	{
		hide();
	}
	QWidget::keyPressEvent(e);
}
