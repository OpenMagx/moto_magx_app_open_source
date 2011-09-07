#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H


#include <ZSoftKey.h>
#include <ZApplication.h>
#include <stdio.h>
#include <ZPopup.h>
#include <RES_ICON_Reader.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qtimer.h>
#include <time.h>

#include <ZKbMainWidget.h>
#include <ZScrollPanel.h>
#include <ZNavTabWidget.h>
#include <ZListBox.h>
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>
#include <ZListBox.h>
#include <ZOptionsMenu.h>
#include <ZSoftKey.h>
#include <qstring.h>
#include <RES_ICON_Reader.h>
#include <qdir.h>
//#include <SETUP_UTIL.h>

extern "C" int UTIL_GetBatteryLevel(); 
extern "C" int UTIL_GetSignalQuality(); 
extern "C" bool UTIL_GetPhoneInCall(); 

//extern "C" void LM_setupBklightBrightness(int);

#define KEY_NOTIFY		"请按右软件键解锁"

typedef struct tagDate		//日期格式
{
  int day;
  int month;
  int year;
}Date,*PDate;

class softLock : public ZKbMainWidget
{
	Q_OBJECT
public: 
	softLock();
	~softLock();
	
	QPixmap nowScreen;
	
	//QTimer *delayLockTimer;
	
	struct tm * timeinfo;

	int oldTime;
	int nowTime;
	
	//int comTime();
	void init();
	void drawAnalog(QPainter &p);
	void drawDigital(QPainter &p);
	void drawDate(QPainter &p);
	void drawLunar(QPainter &p);
	void drawNotify(QPainter &p);
	void drawBackground(QPainter &p);
	void drawWeek(QPainter &p);
	void drawBattery(QPainter &p);
	void drawSignal(QPainter &p);
	void drawMissCall(QPainter &p);
	void drawNewMSG(QPainter &p);	
	
	void GetDayOf(Date &tdate,QString &strLuner);
	QString ctr(const char*ChineseString);
		
protected:
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void timerEvent(QTimerEvent* e);
	virtual void paintEvent(QPaintEvent * pe);

private slots:
	//void midKeyTimeOut();
	//void ensKeyTimeOut();
	void slotUnlockKeyTimeOut();
	void soltMessage( const QCString &msg, const QByteArray &data );

private:
	
	QString path;	//文件路径
	QString skin;
	QString skinCfg;
	int lockTime;
	int keyTimeOut;
	int firstKey;
	int secondKey;
	
	bool isLock;	//是否加锁
	bool isFstBtnEffective;
	bool isLcdOn;
	bool missedCall;
	bool missedMsg;
	bool isCalling;
	//bool isEndKey;


	//SETUP_Utility *lcd;
	
	QString skinName;
	QString author;
	QString skinPath;
//Background
	bool useDefault;
	QPixmap backIMG;
	QPixmap centerIMG;
	QString layout;
//Analog                half
	bool analogShow;
	QPixmap analogBackIMG;
	QPixmap analogCenterIMG;
	QPixmap analogSecIMG;
	QPixmap analogMinIMG;
	QPixmap analogHourIMG;
	bool analogSecShow;
	int analogLeft;
	int analogTop;
//Digital              ok
	bool digitalShow;
	QPixmap digitalFontIMG;
	bool digitalSecShow;
	int DHLeft;
	int DHTop;
	int HMLeft;
	int HMTop;
	int DMLeft;
	int DMTop;
	int MSLeft;
	int MSTop;
	int DSLeft;
	int DSTop;
//Week                ok
	bool weekShow;
	QPixmap weekResIMG;
	int weekLeft;
	int weekTop;
//[Date]             ok
	bool dateShow;
	QPixmap dateFontIMG;
	bool dateYearShow;
	int yearLeft;
	int yearTop;
	int YMLeft;
	int YMTop;
	int mouLeft;
	int mouTop;
	int MDLeft;
	int MDTop;
	int dayLeft;
	int dayTop;
//[Lunar]           ok
	bool lunarShow;
	int lunarFontSize;
	long lunarFontColor;
	int lunarLeft;
	int lunarTop;
//[Battery]           ok
	bool batteryShow;
	bool batteryUseDefault;
	QPixmap batteryLevel[4];
	int batteryLeft;
	int batteryTop;
	
	int oldBatteryLevel;
//[Signal]              ok
	bool signalShow;
	bool signalUseDefault;
	QPixmap signalLevel[6];
	int signalLeft;
	int signalTop;
	
	int oldSignalLevel;
//[Notify]            ok
	bool notifyShow;
	QPixmap notifyLockIMG;
	QPixmap notifyUnlockIMG;
	int notifyLeft;
	int notifyTop;

//[MissCall]
	bool callShow;
	QPixmap callIMG;
	int callLeft;
	int callTop;
//[NewMSG]
	bool MSGShow;
	QPixmap MSGIMG;
	int MSGLeft;
	int MSGTop;
	
//Time Out
	
	//ZConfig* config;	

};



#endif 
