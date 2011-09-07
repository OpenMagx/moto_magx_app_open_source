/****************************************
callhelper for E8 EM30
calldaemon
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#include "calldaemon.h"
#include "myapplication.h"
#include <qtranslator.h>
#include "code.h"

int main(int argc, char *argv[])
{
    MyApplication *app = new MyApplication(argc, argv);
    if(QCopChannel::isRegistered("/EZX/CALL_ASSISTANT"))
    {
        exit(1);
    }
	QTranslator* translator=new QTranslator(0);
	translator->load("callhelper.qm", getAppDir());
	app->installTranslator(translator);
    CallDaemon *daemon = new CallDaemon();
    app->exec();
    delete daemon;
    delete app;
}
