
#include <ZGlobal.h>
#include <ZMessageDlg.h>
#include <ZConfig.h>

#include <qtextcodec.h>
#include <qcopchannel_qws.h>
#include <qfile.h>

#include <iostream>

#include "lockUI.h"
#include "skinDlg.h"

using namespace std;


/*	
QString LockUI::ctr(const char *ChineseString)
{
	QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString);
}

QString LockUI::getAppDir()
{
    QString tmp = QString(qApp->argv()[0]);
    int i = tmp.findRev("/");
    tmp.remove(i+1,tmp.length()-1);
    return tmp;
}
*/

LockUI::LockUI(QWidget *parent)
	:ZPopup(ZPopup::DIALOG, parent)
{
	isRun = false;
    isAutorun = false;
	
	
	this->setTitle(ctr("SoftLock"));
	this->setTitleIcon(QPixmap(getAppDir()+"/img/title.png"));
	
	QRect rect=ZGlobal::getContentR();
		
    listBox = new ZListBox("%I%M",this);	
	this->insertChild(listBox);

	buildListItem();
	
    printf("soft key\n");
	softKey = this->getSoftKey();
	softKey->setText(ZSoftKey::LEFT,  ctr("关于"));
    softKey->setText(ZSoftKey::RIGHT, ctr("退出"));
   // this->setCLISoftKey(softKey);
	softKey->setClickedSlot(ZSoftKey::LEFT, this ,SLOT(slotAbout()));
	softKey->setClickedSlot(ZSoftKey::RIGHT, this ,SLOT(slotQuit()));

	connect(listBox, SIGNAL(returnPressed(int)), this, SLOT(slotItemClicked(int)));
}	

void LockUI::getThemeInfo(QString &info)
{
	printf("get theme info\n");
	
	ZConfig skinCfg(getAppDir()+"/config.cfg");
	QString cSkin = skinCfg.readEntry("General", "Skin", "");
	cout<<"skin "<<cSkin<<endl;
	
	ZConfig cfg(getAppDir()+"/skin/"+cSkin+"/skin.cfg");
	cout<<"skin cfg "<<getAppDir()+"/skin/"+cSkin+"/skin.cfg"<<endl;
	
	QString a = cfg.readEntry("General", "SkinName", "");
	QString b = cfg.readEntry("General", "Author", "");
	
	info = /*ctr("主题：")+*/a+ctr("；")+/*ctr("作者：")+*/b;
	
	cout<<a<<b<<endl;
}

void LockUI::buildListItem()
{
	printf("build list item \n");
	
	for (int i=0; i<3; i++)
    {
        listBoxItem[i] = new ZListBoxItem(listBox);
		listBox->insertItem(listBoxItem[i]);
    }	
	
	getThemeInfo(themeInfo);
	
	printf("after theme info\n");
	isRun = QCopChannel::isRegistered("/EZX/vLock");
	
    if(QFile::exists(AUTORUN_FILE)) 
	    isAutorun = true;
    else 
	    isAutorun = false;
	
	if(isRun)
		onoffString = ctr("当前状态：开启");
	else
		onoffString = ctr("当前状态：关闭");
		
	if(isAutorun)
        autorunString = ctr("自启动状态：开启");
	else
	    autorunString = ctr("自启动状态：关闭");
	
	/*************************************************/
	printf("list box item\n");
    
	listBoxItem[0]->appendSubItem(1, ctr("运行状态"));
	listBoxItem[0]->appendSubItem(1, onoffString);
	if(isRun)
        listBoxItem[0]->setPixmap(0, QPixmap(getAppDir()+"/img/status.png"));
	else
        listBoxItem[0]->setPixmap(0, QPixmap(getAppDir()+"/img/off.png"));		
	
	listBoxItem[1]->appendSubItem(1, ctr("开机自启动"));
    listBoxItem[1]->appendSubItem(1, autorunString);
	if(isAutorun)
        listBoxItem[1]->setPixmap(0, QPixmap(getAppDir()+"/img/autorun.png"));
	else
	    listBoxItem[1]->setPixmap(0, QPixmap(getAppDir()+"/img/off.png"));
		
	listBoxItem[2]->appendSubItem(1, ctr("设置主题"));	
	listBoxItem[2]->appendSubItem(1, themeInfo);
    listBoxItem[2]->setPixmap(0, QPixmap(getAppDir()+"/img/theme.png"));
} 

void LockUI::slotItemClicked(int index)
{
    printf("itme cliked %d\n", index);
	if(index == 0)
	{
	    if(isRun)
		{
			QCopChannel::send("/EZX/vLock","Quit()");
			listBoxItem[0]->setSubItem(1,1, ctr("当前状态：关闭"));
			listBoxItem[0]->setPixmap(0, QPixmap(getAppDir()+"/img/off.png"));
			isRun = !isRun;
		}
		else
		{
			if(!QCopChannel::isRegistered("/EZX/vLock"))
			{
				system(QString("exec %1/lock_daemon &").arg(getAppDir()));
			    listBoxItem[0]->setSubItem(1,1, ctr("当前状态：开启"));
			    listBoxItem[0]->setPixmap(0, QPixmap(getAppDir()+"/img/status.png"));					
				isRun = !isRun;
			}
		}
	}
	if(index == 1)
	{
	    if(isAutorun)
		{
			system( QString("rm -f %1").arg( QString(AUTORUN_FILE) ) );
			listBoxItem[1]->setSubItem(1,1,ctr("自启动状态：关闭"));
            listBoxItem[1]->setPixmap(0,QPixmap(getAppDir()+"/img/off.png"));		
		}
		else
		{
			//QString tmp = "cp -f "+getAppDir()+"/load.sh /ezxlocal/download/mystuff/unKnown/S60DesktopShow";
			//system(tmp);
			system( QString("cp -f %1/load.sh %2").arg( getAppDir() ).arg( QString(AUTORUN_FILE) ) );
			listBoxItem[1]->setSubItem(1,1,ctr("自启动状态：开启"));
            listBoxItem[1]->setPixmap(0,QPixmap(getAppDir()+"/img/autorun.png"));
		}
	    isAutorun = !isAutorun;	
	}
	if(index == 2)
	{
		skinDlg *dlg = new skinDlg();
		int ret = dlg->exec();
		delete dlg;
		cout<<"dlg ret "<<ret<<endl;	
		
		getThemeInfo(themeInfo);
		listBoxItem[2]->setSubItem(1,1, themeInfo);
	}
}

void LockUI::slotQuit()
{
	qApp->quit();
}

void LockUI::slotAbout()
{
	ZMessageDlg *dlg = new ZMessageDlg(ctr("关于"), ctr(ABOUT_TEXT), (ZMessageDlg::MessageDlgType)2);
	dlg->exec();
	delete dlg;	
	//ZPopup::accept();
}


