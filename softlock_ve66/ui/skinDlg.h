#ifndef SKINDLG_H
#define SKINDLG_H

#include <ZPopup.h>
#include <RES_ICON_Reader.h>
#include <ZSoftKey.h>
#include <ZListBox.h>
#include <ZGlobal.h>
//#include <ZOptionsMenu.h>
//#include <ZApplication.h>
//#include <ZKbMainWidget.h>

//#include "tool.h"
#include "tool.h"

struct skinObj
{
	QString author;
	QString name;
	QString dir;
};


class skinDlg : public ZPopup 
{
	Q_OBJECT
	
public:
	skinDlg();
	~skinDlg();
	
	//QString ctr(const char *ChineseString);
	//QString getAppDir();
	void initList();	
	
protected:
	void bulidSkinList();
	void append2_ui(ZListBox *target, QList<struct skinObj> list);	
	
private slots:
	void slotQuit();
	void itemSelected(int index);	

private:	
	RES_ICON_Reader iconReader;

	ZListBox *listBox;
    ZSoftKey *softKey;
	
	QList<struct skinObj> objList;	
	
	QString appDir;
	
};

#endif //SKINDLG_H



