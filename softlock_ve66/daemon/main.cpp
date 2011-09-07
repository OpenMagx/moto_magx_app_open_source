
#include "gui.h"
#include "myapplication.h"
//#include <stdlib.h>
//#include <qtextcodec.h>
//#include <qdatetime.h>
//#include <iostream>

int main(int argc, char *argv[])
{
	//QString path=argv[0];
	MyApplication app(argc, argv);
    if(QCopChannel::isRegistered("/EZX/vLock"))
    {
        exit(1);
    }	
	softLock *gui = new softLock();
	app.setMainWidget(gui);
	//gui->show();
	int ret=app.exec();
	delete gui;
	//delete app;
	return ret;
}



