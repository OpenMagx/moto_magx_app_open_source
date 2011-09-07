/****************************************
callhelper for E8 EM30
callgui
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include <ZApplication.h>
#include <qtranslator.h>
#include "callgui.h"
#include "code.h"

int main(int argc, char** argv)
{
    ZApplication *a = new ZApplication(argc, argv);
	QTranslator* translator=new QTranslator(0);
	translator->load("callhelper.qm", getAppDir());
	a->installTranslator(translator);
    Callgui *gui = new Callgui();
    a->showMainWidget(gui);
	int i =  a->exec();
    delete gui;
	delete a;
	return i;
}

