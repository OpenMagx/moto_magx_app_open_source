/******************************
Java Mgr
by wanggjghost(¿·§Œµ•“ÌÃÏ π)

www.591fan.cn
41245110@qq.com

please keep author information if you redistribute this program

**********************************/
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>
#include <ZListBox.h>
#include <ZLabel.h>
#include <ZPopup.h>
#include <ZGlobal.h>
#include <ZSingleCaptureDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZConfig.h>
#include <AM_UidDef.h>

#include <qfile.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qtextcodec.h>
#include <qcopchannel_qws.h>
#include <qtextstream.h>

#include "ZTaskItem.h"
#include "source.h"
#include "megabox.h"
#include "deathDlg.h"
#include "lng.h"

extern Lng *lng;

megabox :: megabox( QWidget* parent, const char*, WFlags ) 
         : ZKbMainWidget(ZHeader::MAINDISPLAY_HEADER, 0, "megabox", WType_TopLevel/* | WStyle_StaysOnTop*/)
{
	createWindow(this);	
	creatSoftKey(this);
	initTabs();

}

void megabox ::createWindow(QWidget* parent)
{

    setAppTitle( QString(APP_TITLE) );

	mpkgListbox = new appListBox(ITEM_JAVA_OBJ);//, "%I%M", parent, 0);
	mpkgListbox->enableMarquee(true);
	//mpkgListbox->enableMarquee(ZListBox::LISTITEM_REGION_A, true);
   // mpkgListbox->enableMarquee(ZListBox::LISTITEM_REGION_B, true);

	this->setContentWidget(mpkgListbox);
	
	//connect(mpkgListbox, SIGNAL( itemSelected(int) ), parent, SLOT(obj_click(int)));
	connect(mpkgListbox, SIGNAL( clicked(ZIconViewItem *) ), parent, SLOT( obj_click(ZIconViewItem *) ) );

}

megabox::~megabox()
{
	
} 

void megabox::creatSoftKey(QWidget* parent)
{
	QRect rect=ZGlobal::getContentR();
	QRect subRect=ZGlobal::getSubContentR();
	
	/*********************** softkeys and menus ***********************/	
	
	softKey = new ZSoftKey("CST_2A", parent, parent);
	this->setSoftKey(softKey);	
    softKey->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"),
	                               tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
	softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK", "Back"));

 	menu_mgr = new ZOptionsMenu(rect, parent, 0, 0, (ZSkinService::WidgetClsID)55);		
	menu_mgr->insertItem(lng->tr("FT_BACKUP"), NULL, this, SLOT( java_back_up() ), true, false, false, 0, 0);
	menu_mgr->insertItem(lng->tr("FT_DELETE"), NULL, this, SLOT( mpkg_remove() ), true, false, false, 1, 1);
	menu_mgr->insertItem(lng->tr("FT_SET_PROFILE"), NULL, this, SLOT( java_set_profile() ), true, false, false, 2, 2);	
	
	menu_left = new ZOptionsMenu(rect, parent, 0, 0, (ZSkinService::WidgetClsID)55);	
	menu_left->insertItem(lng->tr("FT_PROPS"), NULL, this, SLOT( app_props() ), true, false, false, 0, 0);
	menu_left->insertItem(lng->tr("FT_RENAME"), NULL, this, SLOT( mpkg_rename() ), true, false, false, 1, 1);
	menu_left->insertItem(lng->tr("FT_MANAGER"), menu_mgr, NULL, true, 2, 2, false, false, false );
	menu_left->insertSeparator(4, 4); 
	menu_left->insertItem(lng->tr("FT_ABOUT"), NULL, this, SLOT( slotAbout() ), true, false, false, 5, 5);
	menu_left->insertSeparator(6, 6);
	menu_left->insertItem(lng->tr("FT_QUIT"), NULL, this, SLOT(slotQuit()), true, false, false, 7, 7);	
	
	
	softKey->setOptMenu(ZSoftKey::LEFT, menu_left);	
	softKey->setClickedSlot( ZSoftKey::RIGHT, parent, SLOT ( slotQuit() ) );
}

void megabox::initTabs() 
{
	QTimer::singleShot( 100, this, SLOT( mpkg_refresh() ) );	
	qApp->processEvents();		
}

void megabox::obj_click(ZIconViewItem *obj)
{
	//ZTaskItem* pItem = NULL;
	bool runJavaInMult = true;
	
	//pItem= (ZTaskItem*)mpkgListbox->item(index); 
	ZTaskItem* pItem = (ZTaskItem*)obj;
	

	loadJava(pItem->getGname(), pItem->isSD(), runJavaInMult);	

	qApp->processEvents();	
	
	slotQuit();
}

void megabox::slotQuit()
{
	qApp->quit();
} 

void megabox::fileModCore(QString title, QString text, QString cmdStr1, QString cmdStr2, FILE_MOD_TYPE type, bool isShowProcess)
{
	char exec_buf[1000];	
	switch ( type ) {
		case FILE_PASTE :
			sprintf(exec_buf, "cp -fR '%s' '%s'", (const char*)cmdStr1.local8Bit(), (const char*)cmdStr2.local8Bit() );
			break;
		case FILE_MOVE :
			sprintf(exec_buf, "mv -f '%s' '%s'", (const char*)cmdStr1.local8Bit(), (const char*)cmdStr2.local8Bit() );
			break;
		case FILE_DELETE :
			sprintf(exec_buf, "rm -rf '%s'", (const char*)cmdStr1.local8Bit() );
			break;
		default :
			return;	
	}	
	deathDlg *execDlg = new deathDlg(title, text, exec_buf);
	execDlg->exec();
	delete execDlg; 
	execDlg = NULL;	
	
	qApp->processEvents();		
}	
				  
/*******************************************************************************/

void megabox::mpkg_refresh()
{
    QString origin_name = getAppTitle();
	setAppTitle(lng->tr("FT_REFRESHING")); 	
	
	mpkgListbox->clear();
	mpkgListbox->setDB( QString(PHONE_INSTALL_DB) );
	mpkgListbox->bulidAppList();
	mpkgListbox->setDB( QString(SD_INSTALL_DB) );
	mpkgListbox->bulidAppList();	

	setAppTitle(origin_name);	
}

void megabox::app_props()
{
	//int index=-1;
	
	ZTaskItem* pItem = NULL;

	//index = mpkgListbox->currentItem();
	//if(index == -1) 
	//	return;	
	pItem= (ZTaskItem*)mpkgListbox->currentItem();//(ZTaskItem*)mpkgListbox->item(index);	

	if (pItem == NULL) 
		return;
	
    ZConfig *cfg = NULL;
	QString text = QString::null;
	QString uid = pItem->getGname();
	
	if( pItem->isSD() ) 
		cfg = new ZConfig(SD_INSTALL_DB);
	else
		cfg = new ZConfig(PHONE_INSTALL_DB); 

	QString dir = cfg->readEntry(uid, "Directory", "");
	unsigned int size = getDirSize( (const char*)dir.local8Bit() );	
	
	text += lng->tr("PROP_NAME");
	text += cfg->readEntry(uid, "Name", "")+"\n";
	text += lng->tr("PROP_PATH");
	text += cfg->readEntry(uid, "Directory", "")+"\n";
	text += lng->tr("PROP_TYPE");
	text += cfg->readEntry(uid, "AppType", "")+"\n";
	text += lng->tr("PROP_SIZE");
	text += size2string(size)+"\n";
	text += lng->tr("PROP_VERSION");
	text += cfg->readEntry(uid, "Version", "")+"\n";	
	text += lng->tr("PROP_AUTHOR");
	text += cfg->readEntry(uid, "Vendor", "")+"\n";
	text += lng->tr("PROP_COMMENT")+"\n";	
	text += cfg->readEntry(uid, "Comment", "")+"\n";	
	delete cfg;
	cfg = NULL;
	
	showQ(lng->tr("FT_PROPS"), text, 2);
}

void megabox::mpkg_rename()
{
	//int index=-1;
	
	ZTaskItem* pItem = NULL;

	//index = mpkgListbox->currentItem();
	//if(index == -1) 
	//	return;	
	pItem= (ZTaskItem*)mpkgListbox->currentItem();//(ZTaskItem*)mpkgListbox->item(index);	

	if (pItem == NULL) 
		return;

	ZConfig *cfg = NULL;
	if( pItem->isSD() ) 
		cfg = new ZConfig(SD_INSTALL_DB);
	else 
		cfg = new ZConfig(PHONE_INSTALL_DB);

	QString uid = pItem->getGname(); 
	QString fileName = cfg->readEntry(uid, "Name", "");
	if (fileName == "") {
		delete cfg;
		return;	
	}
	ZSingleCaptureDlg* dlg = new ZSingleCaptureDlg(
	    lng->tr("FT_RENAME"), lng->tr("FT_CUR_NAME")+fileName,
	    (ZSingleCaptureDlg::CaptureDlgType)0, NULL, "ZSingleCaptureDlg", true, 0, 0);
	ZLineEdit *line = dlg->getLineEdit();
	line->setText(fileName);
	int ret=dlg->exec();
	
	QString newName = QString::null;
	if (ret == 1)  {
		newName = dlg->getResultText().stripWhiteSpace();//).local8Bit();
		delete dlg;
	} else 
	{
		delete dlg;
		return;
	}

	if( !isValidFileName(newName) ) {
		showQ(lng->tr("FT_ERR0R"), lng->tr("FT_INVALID"), 2);
		return;
	}

	cfg->writeEntry(uid, "Name", newName);
	cfg->flush();
	delete cfg;

	mpkg_refresh();	
}
void megabox::java_set_profile()
{
	//int index=-1;
	
	ZTaskItem* pItem = NULL;

	//index = mpkgListbox->currentItem();
	//if(index == -1) 
	//	return;	
	pItem= (ZTaskItem*)mpkgListbox->currentItem();//(ZTaskItem*)mpkgListbox->item(index);	

	if (pItem == NULL) 
		return;	

	ZConfig *regCfg = NULL;
	if( pItem->isSD() ) 
		regCfg = new ZConfig(SD_INSTALL_DB);
	else 
		regCfg = new ZConfig(PHONE_INSTALL_DB);
	
	QString destUid = pItem->getGname();
	QString path = regCfg->readEntry(destUid, "Directory", "");
	delete regCfg;
	regCfg = NULL;
	
	QString profile = QString::null;
		
	QDir pdir(JAVA_NET_PROFILE_PATH);
	QStringList plist = pdir.entryList(QDir::Files);
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("FT_SET_PROFILE"),NULL);
	dlg->addItemsList(plist);
	if(dlg->exec() == ZPopup::Accepted)  {
		int i = dlg->getCheckedItemIndex();
		profile = plist[i].local8Bit();	
		delete dlg;		
	} else
	{
		delete dlg;
		return;
	}
	QString file = QString("%1/registry.txt").arg(path);
	QString key = QString("Connection-Profile");
	QString type = QString(":");
	if( !setLineConfig(file, key, type, profile) )
		qDebug("============= set java profile error =============");	
}

void megabox::java_back_up()
{
	//int index=-1;
	
	ZTaskItem* pItem = NULL;

	//index = mpkgListbox->currentItem();
	//if(index == -1) 
	//	return;	
	pItem= (ZTaskItem*)mpkgListbox->currentItem();//(ZTaskItem*)mpkgListbox->item(index);	

	if (pItem == NULL) 
		return;

	ZConfig *regCfg = NULL;
	if( pItem->isSD() ) regCfg = new ZConfig(SD_INSTALL_DB);
	else regCfg = new ZConfig(PHONE_INSTALL_DB);
	
	QString destUid = pItem->getGname();
	
	QString name = regCfg->readEntry(destUid, "Name", "");
	QString path = regCfg->readEntry(destUid, "Directory", "");
	QString text(lng->tr("FT_CONFIRM_BACKUP")+"\n"+name+"\n"+path+"\n");

	int ret = showQ(lng->tr("FT_BACKUP"), text, 1);
	if (ret != 1)  {
	    delete regCfg;
		return;
	}
	
	QDir dir;
	if( !dir.exists( SD_BACKUP_DIR ) )
		dir.mkdir( SD_BACKUP_DIR );
	if( !dir.exists( PHONE_BACKUP_DIR ) )	
		dir.mkdir( PHONE_BACKUP_DIR );
	
	QString fromPath, destName;
	
	QFile file(path+"/registry.txt");
    if ( file.open( IO_ReadOnly ) ) 
    {
        QTextStream stream( &file );
        QString line;
        while ( !stream.atEnd() ) 
		{
            line = stream.readLine();	
			if( line.find("Jar-Path:") > -1 ) {
				fromPath = line.replace("Jar-Path:", "");
				fromPath = fromPath.stripWhiteSpace();
				break;
			}	
		}
	}
	
	destName = fromPath;
	destName = destName.remove(0, destName.findRev("/")+1 );
	
	QString title = "";
	text = lng->tr("POP_PLEASE_WAIT"); 

	if(pItem->isSD() == true) 
		fileModCore(title, text, fromPath, QString("%1/%2").arg(SD_BACKUP_DIR).arg(destName), FILE_PASTE );
	else
		fileModCore(title, text, fromPath, QString("%1/%2").arg(PHONE_BACKUP_DIR).arg(destName), FILE_PASTE);
}

void megabox::mpkg_remove()
{
	//int index=-1;
	
	ZTaskItem* pItem = NULL;

	//index = mpkgListbox->currentItem();
	//if(index == -1) 
	//	return;	
	pItem= (ZTaskItem*)mpkgListbox->currentItem();//(ZTaskItem*)mpkgListbox->item(index);	

	if (pItem == NULL) 
		return;

	ZConfig *regCfg = NULL;
	QString indexFile = QString::null;
		
	if( pItem->isSD() ) { 
		regCfg = new ZConfig(SD_INSTALL_DB);
		indexFile = QString("/mmc/mmca1/.system/java_%1/JAMInfo/index").arg( getIMEI() );//usrIMEI);

	} else 
	{
		regCfg = new ZConfig(PHONE_INSTALL_DB);
		indexFile = QString("/ezxlocal/download/mystuff/.system/java/JAMInfo/index");	
	}	
	QString destUid = pItem->getGname(); 
	QString execMark = regCfg->readEntry(destUid, "ExecId", "");

	QString text;
	text += lng->tr("FT_CONFIRM_DELETE")+"\n";
	text += lng->tr("PROP_NAME")+regCfg->readEntry(destUid, "Name", "")+"\n";
	text += lng->tr("PROP_PATH")+regCfg->readEntry(destUid, "Directory", "")+"\n";	
	
	int ret = showQ(lng->tr("FT_DELETE"), text, 1);

	if (ret != 1) {
	    delete regCfg;
		return;
	}
	
	QString itemStr = QString::null;
	QString destMenuUid = QString::null;
	
	QStringList grouplist;
	QStringList::ConstIterator p;

	ZConfig *sdMenu = NULL;
	ZConfig *menuCfg = NULL;
	if ( pItem->isSD() )  
		sdMenu = new ZConfig(SD_MENU_CFG);//, false);
    else 
		delete sdMenu;

	system( QString("rm -rf %1").arg(regCfg->readEntry(destUid, "Directory", "")) );	
	/******** clear reg information in reg file ******/
	regCfg->clearGroup(destUid);
	regCfg->flush();	
	delete regCfg;
	
	/*****  clear reg information in menu tree ******/
	
	menuCfg = new ZConfig(MENU_TREE);
	menuCfg->getGroupsKeyList(grouplist);
	for (p = grouplist.begin(); p != grouplist.end(); ++p ) {
        QString tmpItem = menuCfg->readEntry(*p, "Items", "");
		if(tmpItem.find(destUid) > -1) 	{
			itemStr = tmpItem;
			destMenuUid = *p;
			break;	
		}
    }	
	
	if( !itemStr.endsWith(";") )
		itemStr += ";";		
	itemStr = itemStr.replace(destUid+";", "");
	
	menuCfg->writeEntry(destMenuUid, "Items", itemStr);
	menuCfg->flush();	
	delete menuCfg;	
	
	if(sdMenu != NULL) // for sd menu cfg
	{
	    sdMenu->clearGroup(destUid);
	    sdMenu->flush();	
		delete sdMenu;
    }	
	// delete file in java index file
	QString deleteMark = execMark+"||";
	if( ! deleteKeyLine(indexFile, deleteMark) )
		qDebug("======= delete java index info error =========\n");		

	mpkg_refresh();
	
	showNotify(lng->tr("POP_OK_TITLE"), lng->tr("POP_OK_TEXT"), 1, 2);
	#ifdef VE66
	system("kill `pidof xp` >/dev/null 2>&1");	
	#else	
	system("kill `pidof flowplayer` >/dev/null 2>&1");	
	#endif	
}

void megabox::slotAbout()
{
	QString info = ctr(TITLE);
	info += ctr(BUILD);
	info += ctr(AUTHOR);
	info += ctr(info1);
	info += ctr(info2);
	
	showQ( ctr(APP_TITLE), info, 2);
}






