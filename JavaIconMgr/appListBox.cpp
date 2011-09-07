/******************************
Java Mgr
by wanggjghost(泪の单翼天使)

www.591fan.cn
41245110@qq.com

please keep author information if you redistribute this program

**********************************/


#include <ZConfig.h>
#include <qstringlist.h>
#include <qdir.h>
#include <qfile.h>

#include "appListBox.h"
#include "lng.h"
#include "source.h"


extern Lng *lng;


appListBox::appListBox(ITEMTYPE t)//, const QString& type, QWidget *parent, const char *name, WFlags f,
            //int initCount, int initStep,
            //const ZSkinService::WidgetClsID clsId)
            : ZIconView()//type, parent, name, 0, 0, 20, 10, ZSkinService::clsZIconView1)
{
	iType = t;
	mMode = NORMAL;
	openMenuState = false;
	mIsSD = false;
	
	mDBConfig = NULL;
	//mMenuConfig = NULL;
	
	mMgxMenuListStr = QString::null;
	existsMgxListStr = QString::null;		
	mMenuId = QString::null;
	mConfigFile	= QString::null;
	
	mAppDir = getAppDir();
}			

appListBox::~appListBox()
{

	if( mDBConfig != NULL ) {	
		delete mDBConfig;
		mDBConfig = NULL;
	}
}

void appListBox::setDB(QString file)
{
	switch(iType)
	{
		case ITEM_JAVA_OBJ :
		case ITEM_MPKG_OBJ :
			if( file == QString(PHONE_INSTALL_DB) )
				mIsSD = false;
			else
				mIsSD = true;				
			break;			
		case ITEM_FAV_OBJ :	
			break;
		case ITEM_MGX_OBJ :
			break;
		default :
			break;
	}
	if( mDBConfig == NULL ) {
		mDBConfig = new ZConfig(file);	
	} else {
		delete mDBConfig;
		mDBConfig = new ZConfig(file);
	}	
}
void appListBox::bulidAppList()
{
	switch(iType)
	{
		case ITEM_JAVA_OBJ :
			buildJavaList();
			break;
		default :
			break;
	}
}

void appListBox::buildJavaList()
{
  	if( mDBConfig == NULL )
		return;  
	
	QString uid = QString::null;
	QString name = QString::null;
	QString iconPath = QString::null;
	bool isSD = mIsSD;
	
	
	QStringList grouplist;
	QStringList::ConstIterator p;
	
	//ZConfig mDBConfig(mConfigFile);		
	mDBConfig->getGroupsKeyList(grouplist);	
	
	for (p = grouplist.begin(); p != grouplist.end(); ++p ) 
	{	
		uid = *p;
		if( (mDBConfig->readEntry(uid, "AppType", "")).toInt() != 1) continue;
			
		ZTaskItem* pItem = NULL;
		QString dir;
				
		name = mDBConfig->readEntry(uid, "Name", "");
		dir = mDBConfig->readEntry(uid, "Directory", ""); 
		iconPath = /*dir + "/" + */mDBConfig->readEntry(uid, "Icon", "");
		if( !QFile::exists(iconPath) )
			iconPath = dir + "/" + mDBConfig->readEntry(uid, "BigIcon", "");
		
		pItem = new ZTaskItem ( this );//, QString ( "%I%M" ) );
		
		pItem->setText( name );	
		pItem->setType(ITEM_JAVA_OBJ);	
		pItem->setGname(uid);	
		pItem->setPath(isSD);
		
		QPixmap icon;
		if ( QFile::exists( iconPath ) )  {
			icon = QPixmap(iconPath);			
		} else 
		{		
			if  ( QFile::exists( QString("%1/%2").arg(dir).arg(iconPath) ) ) 
				icon = QPixmap( QString("%1/%2").arg(dir).arg(iconPath) );
			else 
				icon = iconReader.getIcon(iconPath);
		}	

		QImage img = icon.convertToImage();
		img = img.smoothScale(ICON_BIG); 
		icon.convertFromImage(img);
		pItem->setPixmap(icon);

		/*QString text2 = QString::null;	    

		if( isSD )	
			text2 = lng->tr("FT_MMCA1");
		else	
			text2 = lng->tr("FT_PHONE");*/
			
		//text2 += ctr("，")+mDBConfig->readEntry(uid, "Vendor", "unKnown")+ctr("，")+mDBConfig->readEntry(uid, "Version", "unKnown");
	  
		//pItem->appendSubItem(1, name, false, SETTINGITEM_REGION_A);
		//pItem->appendSubItem(1, text2, false, SETTINGITEM_REGION_B);
		
		this->insertItem(pItem);
	}
	//this->sort();
}



