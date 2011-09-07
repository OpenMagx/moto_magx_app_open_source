
#include <ZConfig.h>
#include <ZListBoxItem.h>
#include <ZMessageDlg.h>

#include <qdir.h>
#include <qtextcodec.h>
#include <qcopchannel_qws.h>

#include <iostream>

#include "skinDlg.h"

using namespace std;

/*QString skinDlg::ctr(const char *ChineseString)
{
    QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString);
}

QString skinDlg::getAppDir()
{
    QString tmp = QString(qApp->argv()[0]);
    int i = tmp.findRev("/");
    tmp.remove(i+1,tmp.length()-1);
    return tmp;
}
*/
skinDlg::skinDlg() :ZPopup()
{
	appDir = getAppDir();
	
	this->setTitle(ctr("选择主题"));
	this->setTitleIcon(iconReader.getIcon("fm_folder_small.bmp"));

	QRect rect=ZGlobal::getContentR();
		
    listBox = new ZListBox("%I%M",this);	
	this->insertChild(listBox);
	
    //softKey = new ZSoftKey("CST_2A",this, this);
	softKey = this->getSoftKey();
	//softKey->setText(ZSoftKey::LEFT,  ctr("选择"));
    softKey->setText(ZSoftKey::RIGHT, ctr("返回"));
    //this->setCSTWidget(softKey);
	
	softKey->setClickedSlot(ZSoftKey::LEFT, this ,SLOT(slotQuit()));
	softKey->setClickedSlot(ZSoftKey::RIGHT, this ,SLOT(slotQuit()));
	
	initList();
	
	connect ( listBox, SIGNAL ( selected ( int ) ), this, SLOT ( itemSelected( int ) ) );	
}

skinDlg::~skinDlg()
{
	//printf("dlg quite\n");
}

void skinDlg::initList()
{
	bulidSkinList();
	
	listBox->clear();
	append2_ui(listBox, objList);
}

void skinDlg::bulidSkinList()
{
	QDir dir(getAppDir()+"/skin");
	if(!dir.isReadable()) 
		return;
	
	struct skinObj *obj = NULL;
	int mark;
	
	objList.setAutoDelete(TRUE);
	objList.clear();
		
	dir.setFilter(QDir::Dirs | QDir::NoSymLinks);
	
	QStringList entries;
	QStringList::Iterator p;

	entries = dir.entryList();
	entries.sort();
	
	for (p=entries.begin(); p!=entries.end(); p++)
	{
		mark = 0;
		if ( *p == "." || *p == ".." ) continue;	
		obj = new skinObj; 
		obj->dir = *p;
		ZConfig cfg(appDir+"/skin/"+*p+"/skin.cfg");
		cout<<"cur cfg is "<<appDir+"/skin/"+*p+"/skin.cfg"<<endl;
		obj->author = cfg.readEntry("General", "Author", "");
		if(obj->author != "") mark++;
		obj->name = cfg.readEntry("General", "SkinName", "");
		if(obj->name != "") mark ++;
		
		if(mark == 0)
		{
			delete obj;
			continue;
		}
		objList.append(obj);
	}
}

void skinDlg::append2_ui(ZListBox *target, QList<struct skinObj> list)
{
	ZListBoxItem *pItem = NULL;
	QPixmap pm(appDir+"/img/skin.png");
	
	struct skinObj *obj = list.first(); 
	
	while(obj != NULL)
	{
		pItem = new ZListBoxItem(target);
		pItem->appendSubItem(1, obj->name);
		pItem->appendSubItem(1, ctr("作者：")+obj->author);
		pItem->setPixmap(0, pm);
		
		target->insertItem(pItem);
		
		obj = list.next();
	}
}

void skinDlg::slotQuit()
{
	printf("slot quite\n");
	this->close();
	//qApp->quit();
	
	//ZPopup::reject();
}

void skinDlg::itemSelected(int index)
{
	//if(index == 0) 
	//	return;
	printf("click item %d\n", index);
	struct skinObj *obj = objList.at(index);
	
	ZMessageDlg *dlg = new ZMessageDlg(ctr("主题应用"), ctr("是否应用当前主题：")+obj->name, (ZMessageDlg::MessageDlgType)1);
	int ret = dlg->exec();
	if(ret == 1)
	{
		ZConfig cfg(appDir+"/config.cfg");
		cfg.writeEntry("General", "Skin", obj->dir);
		cfg.flush();
		
		// Fix for /EZX/vLock reloadcfg()
		QCopChannel::send("/EZX/vLock", "Quit()");	
		sleep(1);
		system(QString("exec %1/lock_daemon &").arg(getAppDir()));
		
		slotQuit();
	}
	
}


