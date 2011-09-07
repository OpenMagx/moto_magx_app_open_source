#ifndef MEGABOX_H
#define MEGABOX_H

#include <ZKbMainWidget.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <RES_ICON_Reader.h>


#include <qdatetime.h>
#include <qtimer.h>
#include <iostream>

#include "appListBox.h"
#include "myDef.h"

class megabox : public ZKbMainWidget
{
	Q_OBJECT

public:
	megabox(QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
	~megabox();
    void createWindow(QWidget* parent);
	void creatSoftKey(QWidget* parent);
    void initTabs(); // need mod
	
	void fileModCore(QString title = QString::null, QString text = QString::null, 
					 QString cmdStr1 = QString::null, QString cmdStr2 = QString::null,
					 FILE_MOD_TYPE type = FILE_OTHER, bool isShowProcess = true);

protected:					 
	
public slots:
	//void obj_click(int index);
	void obj_click( ZIconViewItem *obj);
	
	void slotQuit();
	void slotAbout();
	
	void app_props();	
	
	void mpkg_rename();
	void mpkg_refresh();	
	void java_back_up();
	void java_set_profile();
	void mpkg_remove();	
		
private slots:

	
private :
	appListBox *mpkgListbox;
	
	ZSoftKey *softKey;
	ZOptionsMenu *menu_left;
	ZOptionsMenu *menu_mgr;	
	
	RES_ICON_Reader iconReader;
};
#endif
