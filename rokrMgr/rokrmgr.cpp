
#include <ZGlobal.h>
#include <ZSettingItem.h>

#include <AM_LauncherClient.h>

#include <qfile.h>
#include <qdir.h>
#include <qcopchannel_qws.h>

#include <iostream>

#include "rokrmgr.h"
#include "tool.h"
#include "deathDlg.h"
#include "myDef.h"
#include "lng.h"
#include "ThemeSettingView.h"
#include "saveDlg.h"

using namespace std;

extern Lng *lng;

mgrui::mgrui() : ZKbMainWidget()
{
	curTab = -1;
	appdir = getAppDir();
	
	sLngCfg = NULL;
	mgrCfg = new ZConfig(appdir+"/settings.ini");
	//lng = new Lng();
	initSettingLng();
	
	QRect rect = ZGlobal::getContentR();
	//QRect subRect=ZGlobal::getSubContentR();
	
	setAppTitle("Rokr Mgr");
	
	tabWidget = new ZNavTabWidget(this);//, 0, (ZSkinService::WidgetClsID)63);
	setContentWidget(tabWidget);
	tabWidget->stopNextWhenKeyRepeat(FALSE);	

	mgrListBox = new ZListBox("%I%M", tabWidget);
	mgrListBox->enableMarquee(ZListBox::LISTITEM_REGION_A, true);
    mgrListBox->enableMarquee(ZListBox::LISTITEM_REGION_B, true);
	
	phSkinListBox = new ZListBox("%I%M", tabWidget);
	phSkinListBox->enableMarquee(ZListBox::LISTITEM_REGION_A, true);
    phSkinListBox->enableMarquee(ZListBox::LISTITEM_REGION_B, true);
	
	sdSkinListBox = new ZListBox("%I%M", tabWidget);
	sdSkinListBox->enableMarquee(ZListBox::LISTITEM_REGION_A, true);
    sdSkinListBox->enableMarquee(ZListBox::LISTITEM_REGION_B, true);	

	
	QPixmap imgTab;	
	imgTab.load(appdir+"/img/tab0.png");	tabWidget->addTab(mgrListBox,QIconSet(imgTab), "");
	imgTab.load(appdir+"/img/tab1.png");	tabWidget->addTab(phSkinListBox,QIconSet(imgTab), "");
	imgTab.load(appdir+"/img/tab2.png");	tabWidget->addTab(sdSkinListBox,QIconSet(imgTab), "");
	
	
	softKey = new ZSoftKey("CST_2A", this, this);
	setSoftKey(softKey);	
    softKey->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"),
	                               tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
	softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK", "Back"));

	menu = new ZOptionsMenu(rect, this, 0, 0, (ZSkinService::WidgetClsID)55);

	softKey->setClickedSlot( ZSoftKey::RIGHT, this ,SLOT( slotQuit() ) );
	softKey->setOptMenu(ZSoftKey::LEFT, menu);
	
	connect(mgrListBox, SIGNAL( selected(int) ), this, SLOT( obj_click(int) ) );
	// need debug
//	connect(phSkinListBox, SIGNAL( selected(int) ), this, SLOT( obj_click(int) ) );	
//	connect(sdSkinListBox, SIGNAL( selected(int) ), this, SLOT( obj_click(int) ) );
	
	//initTabs();
		
	QTimer::singleShot(100, this, SLOT( initTabs() ));
	startTimer(300);
}

mgrui::~mgrui()
{
	
	phSkinList.setAutoDelete(TRUE);
	phSkinList.clear();	
	sdSkinList.setAutoDelete(TRUE);
	sdSkinList.clear();	
	
	if( mgrCfg != NULL ) {
		delete mgrCfg;
		mgrCfg = NULL;
	}	
	if( sLngCfg != NULL ) {
		delete sLngCfg;
		sLngCfg = NULL;
	}	
}
void mgrui::slotQuit()
{
	qApp->quit();
}
void mgrui::initTabs()
{
	QString origin_name = getAppTitle();
	setAppTitle(ctr("Refreshing...."));
	
	buildMgrList();
	
	buildPhSkinList();
	phSkinListBox->clear();
	append2_skin_ui(phSkinListBox, phSkinList);
	
	buildSdSkinList();
	sdSkinListBox->clear();
	append2_skin_ui(sdSkinListBox, sdSkinList);
	
	switchTab(0);
	
	setAppTitle(origin_name);
}

void mgrui::buildMgrList()
{
	mgrListBox->clear();
	
	ZConfig cfg(appdir+"/settings.ini");
	
	int i, tNum;
    tNum = cfg.readNumEntry("LIST", "Items", 1);
	QPixmap pm;
	
	ZSettingItem *pItem = NULL;
	
	for(i=1;i<=tNum;i++)
	{
		printf("==== build item %d =====\n", i);
		pItem = new ZSettingItem(mgrListBox, QString("%I%M") );
		pItem->appendSubItem(1, sctr( cfg.readEntry( "LIST", "Option"+QString::number(i), "") ), false, SETTINGITEM_REGION_A );
		pItem->appendSubItem(1, sctr( cfg.readEntry( "LIST", "Option"+QString::number(i)+"b", "") ), false, SETTINGITEM_REGION_B );
		//pItem->setPixmap(0, pm);		
		//icon = appdir+cfg.readEntry( "LIST", "Icon"+QString::number(i)+"b", "");
		pm = QPixmap(appdir+cfg.readEntry( "LIST", "Icon"+QString::number(i), "") );
		QImage img = pm.convertToImage();
		img = img.smoothScale(48, 48);
		pm.convertFromImage(img);
		pItem->setPixmap(0, pm);	
		
		mgrListBox->insertItem(pItem);
	}
}

void mgrui::buildPhSkinList()
{
	cout<<"======= buildPhSkinList() ======"<<endl;
	
	QStringList entries;
	QStringList::ConstIterator p;
	
	struct skinObj *obj = NULL;

	phSkinList.setAutoDelete(TRUE);
	phSkinList.clear();	
	
	QDir skinDir( QString(PH_SKIN_DIR) );
	
	if (skinDir.isReadable())
	{
		entries = skinDir.entryList();
		entries.sort();
		p = entries.begin();
		for (p = entries.begin(); p != entries.end(); ++p ) 
		{
			cout<<"cur dir is "<<*p<<endl;
				
			//mark = 0;
			if(*p == "." || *p == "..")  continue;
		
			obj = new skinObj; 
			obj->skinDir = *p;
			cout<<"chm dir "<<CHM_DIR<<endl;
			#ifdef VE66
			ZConfig cfg( QString("%1/%2.phm").arg(CHM_DIR).arg(*p) );
			obj->chmName = *p+".phm";
			#else
			ZConfig cfg( QString("%1/%2.chm").arg(CHM_DIR).arg(*p) );
			obj->chmName = *p+".chm";	
			#endif
			cout<<"cur chm is "<<obj->chmName<<endl;
			
			obj->skinName = cfg.readEntry("THEME_CONFIG_TABLE", "ThemeName", "unKnown" );			
			obj->skinAuthor = cfg.readEntry("THEME_PROP_TABLE", "CopyRight", "unKnown" );
			obj->skinWall = cfg.readEntry("THEME_CONFIG_TABLE", "WallPaper", "" );
			obj->isInPH = true;
			
			phSkinList.append(obj);	
		}
	}
}

void mgrui::buildSdSkinList()
{
	QStringList entries;
	QStringList::ConstIterator p;
	
	struct skinObj *obj = NULL;
	
	sdSkinList.setAutoDelete(TRUE);
	sdSkinList.clear();	
	
	QDir skinDir( QString(SD_SKIN_DIR) );
	
	if (skinDir.isReadable())
	{
		entries = skinDir.entryList();
		entries.sort();
		p = entries.begin();
		for (p = entries.begin(); p != entries.end(); ++p ) 
		{
			//mark = 0;
			if(*p == "." || *p == "..")  continue;
			
			obj = new skinObj; 
			obj->skinDir = *p;
			#ifdef VE66
			ZConfig cfg( QString("%1/%2.phm").arg(CHM_DIR).arg(*p) );
			obj->chmName = *p+".phm";
			#else
			ZConfig cfg( QString("%1/%2.chm").arg(CHM_DIR).arg(*p) );
			obj->chmName = *p+".chm";
			#endif
			obj->skinName = cfg.readEntry("THEME_CONFIG_TABLE", "ThemeName", "unKnown" );
			obj->skinAuthor = cfg.readEntry("THEME_PROP_TABLE", "CopyRight", "unKnown" );
			obj->skinWall = cfg.readEntry("THEME_CONFIG_TABLE", "WallPaper", "" );
			obj->isInPH = false;
			
			sdSkinList.append(obj);	
		}
	}
}

void mgrui::append2_skin_ui(ZListBox *target, QList<struct skinObj> objList)
{
	struct skinObj *obj = objList.first();
	ZSettingItem *pItem = NULL;
	QPixmap pm;
	while(obj != NULL)
	{	
		pItem = new ZSettingItem(target);//, QString("%I%M") );
		pItem->appendSubItem(1, obj->skinName, SETTINGITEM_REGION_A );
		if(obj->isInPH == true)
			pItem->appendSubItem(1, obj->skinAuthor+ctr("，Phone，")+obj->skinDir,false, SETTINGITEM_REGION_B );
		else
			pItem->appendSubItem(1, obj->skinAuthor+ctr("，MMCA2，")+obj->skinDir, false, SETTINGITEM_REGION_B );
	
		if( QFile::exists( obj->skinWall ) )
			pm = QPixmap( obj->skinWall );
		else
			pm = QPixmap( QString("%1/img/skin.png").arg(appdir) );
			
		QImage img = pm.convertToImage();
		img = img.smoothScale(48, 48);
		pm.convertFromImage(img);
		pItem->setPixmap(0, pm);	
		
		target->insertItem(pItem);
		
		obj = objList.next();
	}
}

void mgrui::timerEvent(QTimerEvent *e)
{
	int tabIndex = tabWidget->currentPageIndex();
	if (tabIndex != curTab)
	{
		printf("tabIndex switch %d -> %d\n", curTab, tabIndex);
		curTab = tabIndex;
		switchTab(curTab);
	}
	ZKbMainWidget::timerEvent(e);
}

void mgrui::switchTab(int index)
{
	menu->clear();
	tabWidget->setCurrentPage(index);	
	switch (index)
	{
		case MGR_TAB:
			mgrListBox->setFocus();
			menu->insertItem(lng->tr("FT_RUN"), NULL, this, SLOT( slotMgrRun() ), true, false, false, 0, 0);
			menu->insertItem(lng->tr("FT_ABOUT"), NULL, this, SLOT( slotAbout() ), true, false, false, 1, 1);			
			
			break;
		case PH_SKIN_TAB:
			phSkinListBox->setFocus();
			menu->insertItem(lng->tr("FT_PACK_THEME"), NULL, this, SLOT( slotBackupSkin() ), true, false, false, 0, 0);			
			menu->insertItem(lng->tr("FT_MOVE_THEME"), NULL, this, SLOT( slotMoveSkin() ), true, false, false, 1, 1);			
			menu->insertItem(lng->tr("FT_DELETE_THEME"), NULL, this, SLOT( slotDelSkin() ), true, false, false, 2, 2);
			menu->insertItem(lng->tr("FT_SET_THEME"), NULL, this, SLOT( slotSetSkin() ), true, false, false, 3, 3);	
			menu->insertItem(lng->tr("FT_OPEN_THEME_SETTING"), NULL, this, SLOT(slotOpenSkinSetting() ), true, false, false, 4, 4);	
						
			break;
		case SD_SKIN_TAB:	
			sdSkinListBox->setFocus();
			menu->insertItem(lng->tr("FT_PACK_THEME"), NULL, this, SLOT( slotBackupSkin() ), true, false, false, 0, 0);			
			menu->insertItem(lng->tr("FT_MOVE_THEME"), NULL, this, SLOT( slotMoveSkin() ), true, false, false, 1, 1);			
			menu->insertItem(lng->tr("FT_DELETE_THEME"), NULL, this, SLOT( slotDelSkin() ), true, false, false, 2, 2);			
			menu->insertItem(lng->tr("FT_SET_THEME"), NULL, this, SLOT( slotSetSkin() ), true, false, false, 3, 3);
			menu->insertItem(lng->tr("FT_OPEN_THEME_SETTING"), NULL, this, SLOT(slotOpenSkinSetting() ), true, false, false, 4, 4);	
			break;
		default:
			break;	
	}
}

void mgrui::obj_click(int index)
{
	int tabIndex = tabWidget->currentPageIndex();
	printf("Debug : obj click, cur tab %d \n", tabIndex);
	
	if(tabIndex == MGR_TAB)
	{
		index++;
		printf("mgr obj click %d\n", index);
		
		ZConfig cfg(appdir+"/settings.ini");
		
		QString exec = cfg.readEntry( QString("LIST"), QString("Exec")+QString::number(index), "");
		
		cout<<QString("exec %1/%2 &").arg(appdir).arg(exec)<<endl;
		
		system( QString("exec %1/%2 &").arg(appdir).arg(exec) );
	}
	else if(tabIndex == PH_SKIN_TAB || tabIndex == SD_SKIN_TAB)
	{
		struct skinObj *curObj = NULL;
		if (tabIndex == PH_SKIN_TAB)
			curObj = phSkinList.at( phSkinListBox->currentItem() );
		else
			curObj = sdSkinList.at( sdSkinListBox->currentItem() );
		
		if(curObj == NULL)
			return;
			
		int ret = showQ(lng->tr("FT_USE_THEME"), lng->tr("FT_CONFIRM_TO_USE")+ctr(curObj->skinName)+ctr("？") );
		if( ret != 1) 
		{
			delete curObj;
			curObj = NULL;
			return;	
		}
		ZConfig cfg(EZX_THEME);
		if (tabIndex == PH_SKIN_TAB)
		{
			cfg.writeEntry("THEME_GROUP_LOG", "CurrentSkin", QString("%1/%2").arg(PH_SKIN_DIR).arg(curObj->skinDir) );
			cfg.writeEntry("THEME_GROUP_LOG", "CurrentTheme", QString("%1/%2").arg(PH_SKIN_DIR).arg(curObj->chmName) );
		}
		else
		{
			cfg.writeEntry("THEME_GROUP_LOG", "CurrentSkin", QString("%1/%2").arg(SD_SKIN_DIR).arg(curObj->skinDir) );
			cfg.writeEntry("THEME_GROUP_LOG", "CurrentTheme", QString("%1/%2").arg(SD_SKIN_DIR).arg(curObj->chmName) );		
		}	
		cfg.flush();
		QCopChannel::send("EZX/System", "setOneEnv()");
		QCopChannel::send("EZX/System", "applyStyle()");
		QCopChannel::send("EZX/System", "KillingPolicy(int)");		
		
		system("/usr/SYSqtapp/systemsetup/themesetup -remount");
	}
	else
		return;	
}

void mgrui::slotMgrRun()
{
	int i = mgrListBox->currentItem();
	printf("cur item number %d\n", i);
	
	i++;
	
	ZConfig cfg(appdir+"/settings.ini");
	
	QString exec = cfg.readEntry( QString("LIST"), QString("Exec")+QString::number(i), "");
	
	cout<<QString("exec %1/%2 &").arg(appdir).arg(exec)<<endl;
	
	system( QString("exec %1/%2 &").arg(appdir).arg(exec) );	
}

void mgrui::slotAbout()
{
	showQ( ctr("Rokr Mgr"), ctr("Rokr Mgr \nUpdate 2010/12/03 \nwanggjghost(泪の单翼天使) \nAll rights reserved \n\nwww.591fan.com\n41245110@qq.com\n"), 2);
}

void mgrui::slotBackupSkin()
{
	struct skinObj *curObj = NULL;
//	bool mark;
	
	if (curTab == PH_SKIN_TAB)
	{
		curObj = phSkinList.at( phSkinListBox->currentItem() );
//		mark = true;
	}
	else
	{
		curObj = sdSkinList.at( sdSkinListBox->currentItem() );
//		mark = false;
	}	

	QString title = lng->tr("FT_SAVE_THEME");
	QString name = ctr(curObj->skinName);
	
	saveDlg *sdlg = new saveDlg(title, name);
	sdlg->exec();
	int ret = sdlg->checkedIndex;
	if( ret == -1 ) {
		delete sdlg;
		sdlg = NULL;
		return;
	}
	QString newName = sdlg->newName;
	delete sdlg;
	sdlg = NULL;	
	
	char buf[1000];
	
	switch(ret) {
		case 0:			
			sprintf(buf, "'%s/7z' a -y '%s/%s.mgs' '%s/%s'", P7Z_PATH, 
				SKIN_FILE, (const char*)curObj->skinDir.local8Bit(), PH_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );
			break;
		case 1:
			sprintf(buf, "'%s/7z' a -y '%s/%s.mgs' '%s/%s'", P7Z_PATH, 
				SKIN_FILE, (const char*)curObj->skinDir.local8Bit(), SD_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );	
			break;
		default :
			break;	
	}
	
/*	int ret = showQ(lng->tr("FT_SAVE_THEME"), lng->tr("FT_CONFIRM_TO_SAVE")+ctr(curObj->skinName)+ctr("？") );
	if( ret != 1)
		return;
		
	char buf[1000];
	
	if(mark == true)
	{
		sprintf(buf, "'%s/7z' a -y '%s/%s.mgs' '%s/%s'", P7Z_PATH, 
		SKIN_FILE, (const char*)curObj->skinDir.local8Bit(), PH_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );
	}
	else
	{
		sprintf(buf, "'%s/7z' a -y '%s/%s.mgs' '%s/%s'", P7Z_PATH, 
		SKIN_FILE, (const char*)curObj->skinDir.local8Bit(), SD_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );	
	}*/
	
	QString text = lng->tr("POP_PLEASE_WAIT");
	deathDlg *execDlg = new deathDlg(title, text, buf);
	execDlg->exec();
	delete execDlg;
	execDlg = NULL;
}

void mgrui::slotMoveSkin()
{
	struct skinObj *curObj = NULL;
	bool mark;
	QString info;//, dest;
	
	if (curTab == PH_SKIN_TAB)
	{
		curObj = phSkinList.at( phSkinListBox->currentItem() );
		mark = true;
		//info = lng->tr("”手机内存移动到第三分区？");
		//dest = lng->tr("")
	}
	else
	{
		curObj = sdSkinList.at( sdSkinListBox->currentItem() );
		mark = false;
		//info = lng->tr("”第三分区移动到手机内存？");
	}	
	QString text = lng->tr("FT_CONFIRM_TO_MOVE");
	text += ctr(curObj->skinName);
	text += lng->tr("?\n");
	if(mark)
		text += lng->tr("FT_PHONE")+ctr("\n↓↓↓↓↓↓↓↓↓\n")+lng->tr("FT_PART2");
	else	
		text += lng->tr("FT_PART2")+ctr("\n↓↓↓↓↓↓↓↓↓\n")+lng->tr("FT_PHONE");
	
	
	int ret = showQ(lng->tr("FT_MOVE_THEME"), text, 1);
	if( ret != 1)
		return;	

	char buf[1000];
	
	if(mark) 
	{
		sprintf(buf, "mv -f '%s/%s' '%s/%s'", PH_SKIN_DIR, (const char*)curObj->skinDir.local8Bit(),
					SD_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );
	}
	else
	{
		sprintf(buf, "mv -f '%s/%s' '%s/%s'", SD_SKIN_DIR, (const char*)curObj->skinDir.local8Bit(),
					PH_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );
	}
	
	QString title = lng->tr("FT_MOVE_THEME");
	QString subtitle = lng->tr("POP_PLEASE_WAIT");
	deathDlg *execDlg = new deathDlg(title, subtitle, buf);
	execDlg->exec();
	delete execDlg;
	execDlg = NULL;
	
	ZConfig cfg( QString("%1/%2").arg( QString(CHM_DIR) ).arg( curObj->chmName ) );
	
	if(mark == true)
		cfg.writeEntry("THEME_CONFIG_TABLE", "Skin", QString(SD_SKIN_DIR)+curObj->skinDir );
	else
		cfg.writeEntry("THEME_CONFIG_TABLE", "Skin", QString(PH_SKIN_DIR)+curObj->skinDir );
	cfg.flush();	
	
	QTimer::singleShot(100, this, SLOT( initTabs() ));	
}

void mgrui::slotDelSkin()
{
	struct skinObj *curObj = NULL;
	bool mark;
	
	if (curTab == PH_SKIN_TAB)
	{
		curObj = phSkinList.at( phSkinListBox->currentItem() );
		mark = true;
	}
	else
	{
		curObj = sdSkinList.at( sdSkinListBox->currentItem() );
		mark = false;
	}	
		
	int ret = showQ(lng->tr("FT_DELETE_THEM"), lng->tr("FT_CONFIRM_DELETE")+ctr(curObj->skinName)+ctr("？") );
	if( ret != 1)
		return;	

	char buf[1000];
	
	if(mark)
		sprintf(buf, "rm -rf '%s/%s'", PH_SKIN_DIR, (const char*)curObj->skinDir.local8Bit() );
	else
		sprintf(buf, "rm -rf '%s/%s'", SD_SKIN_DIR, (const char*)curObj->skinDir.local8Bit());
	
	QString title = lng->tr("FT_DELETE_THEME");
	QString text = lng->tr("POP_PLEASE_WAIT");
	deathDlg *execDlg = new deathDlg(title, text, buf);
	execDlg->exec();
	delete execDlg;
	execDlg = NULL;		
	
	QTimer::singleShot(100, this, SLOT( initTabs() ));	
}

void mgrui::slotSetSkin()
{
	struct skinObj *curObj = NULL;
	
	if (curTab == PH_SKIN_TAB) 
		curObj = phSkinList.at( phSkinListBox->currentItem() );
	else 
		curObj = sdSkinList.at( sdSkinListBox->currentItem() );
	
	QString themeChmFile = QString("%1/%2").arg(CHM_DIR).arg(curObj->chmName);
	
	cout<<"theme chm file  "<<themeChmFile<<endl;
	
	
	
	ThemeSettingView *tsv = new ThemeSettingView(themeChmFile);
	tsv->exec();
	delete tsv;
	tsv = NULL;
	
	QTimer::singleShot(100, this, SLOT( initTabs() ));	
}
void mgrui::slotOpenSkinSetting()
{
	AM_LauncherClient::launchAppObject( QString("a34ef25d-d791-4aee-943d-db5db70c6220") );
}
void mgrui::initSettingLng()
{
	QString appDir = QString(qApp->argv()[0]);
    int i = appDir.findRev("/");
    appDir.remove(i+1, appDir.length()-1);
	
	ZConfig cfg("/ezxlocal/download/appwrite/setup/ezx_system.cfg");
	QString lngStr = cfg.readEntry("SYS_SYSTEM_SET", "LanguageType", "");
	QString lngFile = QString("%1/settings_%3.lng").arg(appDir).arg(lngStr);
	std::cout<<"setting lng file "<<lngFile<<std::endl;
	if( !QFile::exists( lngFile ) )
		lngFile = QString("%1/settings_zh-cn.lng").arg(appDir);	
	
	std::cout<<"setting lng file "<<lngFile<<std::endl;
	sLngCfg = new ZConfig(lngFile);


}
QString mgrui::sctr( QString inputLng )
{
	QString tmp = QString::null;
	tmp = sLngCfg->readEntry("LNG", inputLng, "");
	if(tmp == "") {
		tmp = inputLng;
		cout<<inputLng<<" = "<<endl;
	}	
	return tmp; 
}



