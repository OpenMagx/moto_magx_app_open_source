#include <ZApplication.h>

class MyApplication:public ZApplication
{
    Q_OBJECT
    public:
        MyApplication(int argc, char*argv[]):ZApplication(argc,argv)
        {
        }
    public slots:
        virtual void slotShutdown(){}
        virtual void slotQuickQuit(){}
};
