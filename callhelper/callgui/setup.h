/****************************************
callhelper for E8 EM30
callgui
Version: 1.1   2010.3.10
Author:  slbear    <25828761@qq.com>
*****************************************/
#ifndef SETUP_H_
#define SETUP_H_
#include <ZListBox.h>
#include <ZConfig.h>
#include <qcopchannel_qws.h>
#include <unistd.h>
#include <ZMainWidget.h>
#include <ZSingleCaptureDlg.h>
#include <AM_AppRegistry.h>
#include <qstringlist.h>
#include <ZConfig.h>

class Setup : public ZListBox
{
Q_OBJECT
public:
    Setup(QWidget*);
    ~Setup();
public:
    ZSingleCaptureDlg* numberDlg;
private:
    bool autorun;
    QString autorunstate;
    QUuid daemonID;
    bool status;
    //bool allowgo;
    ZConfig *conf;
    ZConfig *sysreg;
	ZSettingItem *state;
	//ZSettingItem *allowgoout;
	bool bool_showno;
	ZSettingItem *showno;
	ZSettingItem *search;
    ZSettingItem* reg;
	bool switchcallrecord;
	ZSettingItem* callrecord;
	ZSettingItem* ipedit;
private:
    void loadConfig();
    QString strcut(QString&);
    void writeAppRegistry();
	void showSearch();
	void showState();
	void showAllowgo();
	void showShowno();
	void showCallRecord();
	void showAutorun();
	void showIpEdit();
	QStringList iplist;

private slots:
    void slotSelect(int);
};

#endif

