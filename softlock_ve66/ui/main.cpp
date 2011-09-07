
#include "lockUI.h"
#include <ZApplication.h>
//#include <stdlib.h>
//#include <qtextcodec.h>
//#include <qdatetime.h>
//#include <iostream>

int main(int argc, char *argv[])
{
	//QString path=argv[0];
	ZApplication app(argc, argv);
	
	LockUI *ui = new LockUI();
	int ret = ui->exec();
	delete ui;
	return ret;
}



