#ifndef APPLISTBOX_H
#define APPLISTBOX_H


#include <RES_ICON_Reader.h>

#include <qstring.h>

#include "ZTaskItem.h"
#include "myDef.h"
#include "source.h"

#include "ZIconView.h"
	

class appListBox : public ZIconView
{
    Q_OBJECT
	
public :
    
	appListBox(ITEMTYPE t = ITEM_FAV_OBJ);//, const QString& type = QString::null, QWidget *parent = 0, const char *name = 0, WFlags f = 0,
            //int initCount = 20, int initStep = 10,
            //const ZSkinService::WidgetClsID clsId = ZSkinService::clsZIconView1);
			
	~appListBox();
	void setDB(QString file);
	
	void bulidAppList();

private:
	void buildJavaList();

private:	
	RES_ICON_Reader iconReader;
    ITEMTYPE iType;
	ITEMMODE mMode;
	
	QString mMgxMenuListStr;
	QString mMenuId;
	QString mAppDir;
	QString mConfigFile;
	QString existsMgxListStr;

	bool mIsSD;	
	bool openMenuState;
	
	ZConfig *mDBConfig;
	//ZConfig *mMenuConfig;
};

#endif //APPLISTBOX_H


