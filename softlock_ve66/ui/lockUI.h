#ifndef LOCKUI_H
#define LOCKUI_H


#include <ZPopup.h>
#include <ZSoftKey.h>
#include <ZListBox.h>
#include <ZListBoxItem.h>
#include <RES_ICON_Reader.h>

#include "tool.h"

#define AUTORUN_FILE "/ezxlocal/download/mystuff/unKnown/S60SoftLock"
#define ABOUT_TEXT "         <Soft Lock>\n\nLock_daemon by 夏日清泉(Justin.Z)\n\nLock UI by wanggjghost(泪の单翼天使)\n\nVE66/EM35 port and modify  by wanggjghost(泪の单翼天使)\n\nwww.591moto.cn首发\n\n"

class LockUI : public ZPopup
{
    Q_OBJECT

public :
	LockUI(QWidget *parent = 0);
	~LockUI(){};
	
	//QString ctr(const char *ChineseString);
	//QString getAppDir();
	
	void buildListItem();
	
	void getThemeInfo(QString &info);

private slots:
	void slotItemClicked(int index);
	void slotAbout();
	void slotQuit();

private:
    RES_ICON_Reader iconReader;
    ZListBox *listBox;
	ZListBoxItem * listBoxItem[3];	
    ZSoftKey *softKey;
	
    bool isRun;
    bool isAutorun; 
	
	QString onoffString;
    QString autorunString;
	
	QString themeInfo;

};


#endif //LOCKUI_H 


