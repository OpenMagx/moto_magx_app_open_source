#ifndef ROKRMGR_H
#define ROKRMGR_H


#include <ZNavTabWidget.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZConfig.h>
#include <ZOptionsMenu.h>

#include <RES_ICON_Reader.h>

#include "myDef.h"
//#include "lng.h"

struct skinObj
{
	QString skinDir;
	QString skinName;
	QString chmName;
	QString skinAuthor;
	QString skinWall;
	bool isInPH;
	//bool isEChm;
};

class mgrui : public ZKbMainWidget
{
	Q_OBJECT

public:
	mgrui();
	~mgrui();
	
	void buildMgrList();
	void buildPhSkinList();
	void buildSdSkinList();
	
	void append2_skin_ui(ZListBox *target, QList<struct skinObj> objList);

	void timerEvent(QTimerEvent *e);
	
	void switchTab(int index);
	

	
public slots:
	void initTabs();	
	void slotQuit();
	
	void obj_click(int index);
	
	void slotMgrRun();
	void slotAbout();
	void slotBackupSkin();
	void slotMoveSkin();
	void slotDelSkin();
	void slotSetSkin();
	void slotOpenSkinSetting();
	
	
private:
	void initSettingLng();
	
	QString sctr( QString inputLng );
	
	ZNavTabWidget *tabWidget;	
	ZListBox *mgrListBox;
	ZListBox *phSkinListBox;
	ZListBox *sdSkinListBox;
	ZSoftKey *softKey;
	ZOptionsMenu *menu;
	
	//Lng *lng;
	
	RES_ICON_Reader iconReader;
	
	ZConfig *mgrCfg;
	ZConfig *sLngCfg;
	
	QList<struct skinObj> phSkinList;
	QList<struct skinObj> sdSkinList;
	
	QString appdir;
	
	int curTab;

};

#endif // ROKRMGR_H

