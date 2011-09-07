
#ifndef PROGRESSDLG
#define PROGRESSDLG
#define QT_THREAD_SUPPORT

#include <ZPopup.h>
#include <ZMeter.h>
#include <ZMeterModule.h>
#include <ZSoftKey.h>

#include <qthread.h>
#include <qtimer.h>

#include <iostream>

class progressCmd : public QThread
{
public :
	progressCmd(const char* cmd);
	~progressCmd();
	bool isFinish();
	int getRet();
	QString getResultText();
	QString getCmd();
	
protected :
	virtual void run();

private :
	bool m_finishState;
	char command[1024];
	int m_ret;
	QString m_resultStr;
	QString m_cmd;
};

class progressDlg : public ZPopup
{
	Q_OBJECT
	
public :
	progressDlg(QString &title, QString &text, const char* cmd, bool isShowPopInfo = false, int dlgType = 1); //0 DIALOG , 1  NOTICE 
	~progressDlg();
	int ret;
private slots:
	void slotTimerEvent();
	void slotDlgOver();
	void slotQuit();
	void slotHide();
	
private :
//	RES_ICON_Reader iconReader;
	
	progressCmd *m_progressCmd;
	QTimer *timer;
	
	ZMeterModule *m_md;
	ZMeter *m_mt;
	
	bool popInfoState;
	bool m_hideState;
	int m_dlgType;
//	QString m_cmd;
	
	int m_step;
};


#endif
