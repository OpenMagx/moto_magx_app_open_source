
#include <ZApplication.h>
#include "rokrmgr.h"
#include "lng.h"

Lng *lng;

int main(int argc, char *argv[])
{
	ZApplication app(argc, argv);
	
	lng = new Lng();
	mgrui *ui = new mgrui();
	app.setMainWidget(ui);
	ui->show();
	
	int ret = app.exec();
	
	delete lng;
	lng = NULL;
	delete ui;
	ui = NULL;
	return ret;
}




