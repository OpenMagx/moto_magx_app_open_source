/****************************************
callhelper for E8 EM30
callgui
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "callgui.h"
#include "code.h"
#include <ZMessageDlg.h>



Callgui::Callgui() : ZKbMainWidget(ZHeader::MAINDISPLAY_HEADER)
{
		znt = new ZNavTabWidget(this, 0, (ZSkinService::WidgetClsID)63);
		znt->stopNextWhenKeyRepeat(false);
    	tab1 = new Setup(znt);
    	setInputMethod(tab1->numberDlg->getLineEdit(), ZKB_INPUT_NUMERIC);
		tab1->setFocus();
    	znt->addTab(tab1,iconReader.getIcon("settings_simple.bmp"),"setup");
		setContentWidget(znt);
		connect(znt, SIGNAL(currentChanged(QWidget*)) , this , SLOT(slotSetArea(QWidget*)));
		connect(znt, SIGNAL(currentChanged(QWidget*)) , this , SLOT(slotSetZom(QWidget*)));	

		zsk = new ZSoftKey("CST_2A",this);
		setSoftKey(zsk);
	
		QRect rect=ZGlobal::getContentR();
		zom=new ZOptionsMenu(rect, this, 0, 0, ZSkinService::WidgetClsID(55));
	
		zsk->setTextForOptMenuHide(tr("options"));
		zsk->setTextForOptMenuShow(tr("select"),tr("cancel"));
		zsk->setText(ZSoftKey::LEFT, tr("options"));
		zsk->setText(ZSoftKey::RIGHT, tr("cancel"));
		zsk->setOptMenu(ZSoftKey::LEFT, zom);
		zsk->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
}

void Callgui::slotSetArea(QWidget*)
{
	switch(znt->currentPageIndex())
	{
		case 0:
			setAppTitle(tr("setup"));
			break;
		case 1:
			setAppTitle(tr("additional function"));
			break;
		default:
			break;
	}
}

void Callgui::slotSetZom(QWidget*)
{
	zom->clear();	
	int i = znt->currentPageIndex();
	switch(i)
	{
		case 0:
			zom->insertItem(tr("about"), NULL, this, SLOT(slotAbout()), true, false, false, 0);
			break;
		case 1:
			//zom->insertItem(tr(""), NULL, tab2, SLOT(slotAddBlack()), true, false, false, 0);
			break;
		default:
			break;
	}
}

void Callgui::slotAbout()
{
	ZMessageDlg *dlg = new ZMessageDlg(tr("About"),"Call Helper 1.1\n"
            "Author:slbear \n"
			"thanks to tulanix Xmifeng MaybeLoveU."
            ,ZMessageDlg::TypeOK,0,this);
    dlg->exec();
    delete dlg;

}


