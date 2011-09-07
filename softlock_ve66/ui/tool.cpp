#include "tool.h"

QString ctr(const char *ChineseString)
{
    QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString);
}
/*
void showNotify(QString title, QString text, int dismissTime)  //msecond
{
    ZNoticeDlg *noticeDlg = new ZNoticeDlg((ZNoticeDlg::Type)1, text, "");
    noticeDlg->setTitle(title);
    noticeDlg->setAutoDismissTime(dismissTime);
    noticeDlg->exec();
}
*/
QString getAppDir()
{
    QString tmp = QString(qApp->argv()[0]);
    int i = tmp.findRev("/");
    tmp.remove(i+1,tmp.length()-1);
    return tmp;
}
/*
QString createUUID() 
{
    srand(time(NULL));
    int data[16];
    QString uuid = "";

    for (int i = 0; i < 16; ++i) {
        data[i] = rand() % 255;
    }

    data[0] &= 0x0;
    data[0] |= 0xff;
    data[15] &= 0x0;
    data[15] |= 0xff;

    for (int i = 0; i < 4; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
    uuid += "-";
    for (int i = 4; i < 6; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
    uuid += "-";
    for (int i = 6; i < 8; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
    uuid += "-";
    for (int i = 8; i < 10; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }
    uuid += "-";
    for (int i = 10; i < 16; ++i) {
        if (data[i] < 16)
            uuid += "0";
        uuid += QString::number(data[i],16);
    }

    return uuid;
}
*/


