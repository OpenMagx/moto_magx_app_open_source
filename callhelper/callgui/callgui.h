/****************************************
callhelper for E8 EM30
callgui
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef CALLGUI_H_
#define CALLGUI_H_

#include <ZNavTabWidget.h>
#include <ZKbMainWidget.h>
#include <ZOptionsMenu.h>
#include <ZSoftKey.h>
#include "setup.h"
#include <RES_ICON_Reader.h>

class Callgui : public ZKbMainWidget
{
Q_OBJECT
public:
    Callgui();
    //~Callgui();
private:

private:
	RES_ICON_Reader iconReader;
    ZNavTabWidget* znt;
    ZSoftKey* zsk;
    ZOptionsMenu* zom;
    Setup* tab1;
private slots:
    void slotSetArea(QWidget*);
    void slotSetZom(QWidget*);
	void slotAbout();

};
#endif

