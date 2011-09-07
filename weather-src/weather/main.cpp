/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#include <ZApplication.h>
#include "maingui.h"
#include "getdata.h"

int main(int argc, char** argv)
{
	ZApplication *a =new ZApplication(argc, argv);
	MainGui *gui = new MainGui();
	a->showMainWidget(gui);
	//QCanvas *canvas = new QCanvas(320, 240);
	//GetData *b = new GetData(canvas,"101160401", 0);
	//b->show();
	int i = a->exec();
	//delete gui;
	delete a;
	return i;
}
