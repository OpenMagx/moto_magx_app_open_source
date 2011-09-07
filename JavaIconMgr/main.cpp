/******************************
Java Mgr
by wanggjghost(¿·§Œµ•“ÌÃÏ π)

www.591fan.cn
41245110@qq.com

please keep author information if you redistribute this program

**********************************/


#include <ZApplication.h>
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>

#include <qdatetime.h>
#include <qtranslator.h>
#include <qtextcodec.h>

#include "megabox.h"
#include "source.h"
#include "lng.h"
#include "myDef.h"

megabox *gui;
ZApplication *app;
Lng *lng;

int main(int argc, char** argv)
{
	app = new ZApplication(argc,argv);

	lng = new Lng();
	gui = new megabox(NULL, NULL);

	app->setMainWidget(gui);
	gui->show();

	int ret = app->exec();
		
	delete gui;
	gui = NULL;

	delete lng;
	lng = NULL;

	delete app;
	app = NULL;
	
	return ret;
}

