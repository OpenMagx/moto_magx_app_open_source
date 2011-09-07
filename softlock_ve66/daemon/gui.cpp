/*
ZN5 keylock2
2010-5-8
written by 夏日清泉（Justin.Z）
Email : xiariqingquan@vip.qq.com
*/

#include "gui.h"
#include <qcopchannel_qws.h>
#include <time.h>
#include <qtextcodec.h>
#include <qwmatrix.h>
#include <qrect.h>
#include <qfile.h>
#include <iostream>

QString softLock::ctr(const char*ChineseString)
{
	QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString/*.latin1()*/);
	//return gbk_codec->fromUnicode(ChineseString);
}

//void softLock::GetDayOf(Date &tdate,QString &strLuner);

softLock::softLock():ZKbMainWidget(0, "softLock", 0)
{
	path = QString(qApp->argv()[0]);
    int i = path.findRev("/");
    path.remove(i+1,path.length()-1);
    //return tmp;
	//std::cout<<"path "<<path<<std::endl;
	//setMorphMode((MORPHING_MODE_E)3,3);
	
	isLock = false;
	isFstBtnEffective = false;
	isLcdOn = true;
	isCalling = false;
	//isEndKey = false;
	missedCall = false;
	missedMsg = false;
	
	oldSignalLevel = -1;
	oldBatteryLevel = -1;
	
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	Date tdate;
	tdate.year=timeinfo->tm_year+1900;
	tdate.month=timeinfo->tm_mon+1;
	tdate.day=timeinfo->tm_mday;	
	
	setFullScreenMode(true, true);

	init();
	
	//lcd->getBackLightValue(oldLCD);
	
	//QCopChannel * LCDCH;
    //LCDCH = new QCopChannel(QCString(SYSTEM_CHANNEL), this);
    //connect(LCDCH,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT (soltMessage(const QCString &,const QByteArray &)));
	
	/*QCopChannel * inComingCallCH;
    inComingCallCH = new QCopChannel(QCString("/EZX/PHONE/INCOMING_CALL"), this);
    connect(inComingCallCH,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT (soltMessage(const QCString &,const QByteArray &)));
	
	QCopChannel * outComingCallCH;
    outComingCallCH = new QCopChannel(QCString("/EZX/PHONE/OUTGOING_CALL"), this);
    connect(outComingCallCH,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT (soltMessage(const QCString &,const QByteArray &)));
*/
	QCopChannel *lockhnl = new QCopChannel("/EZX/vLock",this); 
	connect(lockhnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(soltMessage(const QCString &,const QByteArray &))); 
   	
	QCopChannel *systemchnl = new QCopChannel("EZX/System",this); 
	connect(systemchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(soltMessage(const QCString &,const QByteArray &))); 
   
    QCopChannel *incomchnl = new QCopChannel("/EZX/PHONE/INCOMING_CALL",this); 
    connect(incomchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(soltMessage(const QCString &,const QByteArray &)));
    
	QCopChannel *outgoingchnl = new QCopChannel("/EZX/PHONE/OUTGOING_CALL",this); 
    connect(outgoingchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(soltMessage(const QCString &,const QByteArray &)));
    
	QCopChannel *callchnl = new QCopChannel("/EZX/recentcall",this); 
	connect(callchnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(soltMessage(const QCString &,const QByteArray &))); 

	QCopChannel *messagechnl = new QCopChannel("msgctr_eng__msgapi_sms__client_broadcast_listen_chnl_name",this); 
	connect(messagechnl,SIGNAL(received(const QCString &,const QByteArray &)),this,SLOT(soltMessage(const QCString &,const QByteArray &))); 

	startTimer(1000);	
}
softLock::~softLock()
{

}

void softLock::init()
{
	//printf("== init cfg ===\n");
	QString cfgFile = path+"config.cfg";
	//config = new ZConfig(cfgFile,true);
	ZConfig gCfg(cfgFile);
	skin=gCfg.readEntry("General","Skin");
	lockTime=gCfg.readNumEntry("General","LockTime");
	keyTimeOut=gCfg.readNumEntry("General","KeyTimeOut");
	firstKey=gCfg.readNumEntry("General","FirstKey");
	secondKey=gCfg.readNumEntry("General","SecondKey");
	//delete config;

	
	skinPath = path+"skin/"+skin+"/";
	//printf("\nskinFile:"+skinPath+"\n");
	//config = new ZConfig(skinPath+"skin.cfg");
	ZConfig config(skinPath+"skin.cfg");
	
	//std::cout<<"skin cfg "<<skinPath+"skin.cfg"<<std::endl;
	//QString tmp = config.readEntry("Background","BackIMG", "aa");
	//std::cout<<"bg file "<<tmp<<std::endl;
	
	backIMG.load(skinPath+config.readEntry("Background","BackIMG"));
	centerIMG.load(skinPath+config.readEntry("Background","MidIMG"));
	
	//Analog
	analogShow=config.readBoolEntry("Analog","Show");
	if(analogShow)
	{
		analogBackIMG.load(skinPath+config.readEntry("Analog","BackIMG"));
		analogCenterIMG.load(skinPath+config.readEntry("Analog","CenterIMG"));
		
		analogMinIMG.load(skinPath+config.readEntry("Analog","MinIMG"));
		analogHourIMG.load(skinPath+config.readEntry("Analog","HourIMG"));
		analogSecShow=config.readBoolEntry("Analog","SecShow");
		if(analogSecShow)
		{
			analogSecIMG.load(skinPath+config.readEntry("Analog","SecIMG"));
		}
		analogLeft=config.readNumEntry("Analog","Left");
		analogTop=config.readNumEntry("Analog","Top");
	}
	
	//Digital
	digitalShow=config.readBoolEntry("Digital","Show");
	if(digitalShow)
	{
		digitalFontIMG.load(skinPath+config.readEntry("Digital","FontIMG"));
		digitalSecShow=config.readBoolEntry("Digital","SecShow");
		
		DHLeft=config.readNumEntry("Digital","HourLeft");
		DHTop=config.readNumEntry("Digital","HourTop");
		HMLeft=config.readNumEntry("Digital","Colon0Left");
		HMTop=config.readNumEntry("Digital","colon0Top");
		DMLeft=config.readNumEntry("Digital","MinLeft");
		DMTop=config.readNumEntry("Digital","MinTop");
		MSLeft=config.readNumEntry("Digital","Colon1Left");
		MSTop=config.readNumEntry("Digital","colon1Top");
		DSLeft=config.readNumEntry("Digital","SecLeft");
		DSTop=config.readNumEntry("Digital","SecTop");
	}
	
	//Week
	weekShow=config.readBoolEntry("Week","Show");
	if(weekShow)
	{
		weekResIMG.load(skinPath+config.readEntry("Week","ResIMG"));
		weekLeft=config.readNumEntry("Week","Left");
		weekTop=config.readNumEntry("Week","Top");
	}
	
	//[Date]
	dateShow=config.readBoolEntry("Date","Show");
	if(dateShow)
	{
		dateFontIMG.load(skinPath+config.readEntry("Date","FontIMG"));
		dateYearShow=config.readBoolEntry("Date","YearShow");
		yearLeft=config.readNumEntry("Date","YearLeft");
		yearTop=config.readNumEntry("Date","YearTop");
		YMLeft=config.readNumEntry("Date","YMLeft");
		YMTop=config.readNumEntry("Date","YMTop");
		mouLeft=config.readNumEntry("Date","MouLeft");
		mouTop=config.readNumEntry("Date","MouTop");
		MDLeft=config.readNumEntry("Date","MDLeft");
		MDTop=config.readNumEntry("Date","MDTop");
		dayLeft=config.readNumEntry("Date","DayLeft");
		dayTop=config.readNumEntry("Date","DayTop");
	}
	
	//[Lunar]
	lunarShow=config.readBoolEntry("Lunar","Show");
	if(lunarShow)
	{
		lunarFontSize=config.readNumEntry("Lunar","FontSize");
		lunarFontColor=config.readEntry("Lunar","FontColor").toLong();
		lunarLeft=config.readNumEntry("Lunar","Left");
		lunarTop=config.readNumEntry("Lunar","Top");
	}
	
	//[Battery]
	batteryShow=config.readBoolEntry("Battery","Show");
	if(batteryShow)
	{
		batteryUseDefault=config.readBoolEntry("Battery","UseDefault");
		batteryLeft=config.readNumEntry("Battery","Left");
		batteryTop=config.readNumEntry("Battery","Top");
		batteryLevel[0].load(skinPath+"b0.png");
		batteryLevel[1].load(skinPath+"b1.png");
		batteryLevel[2].load(skinPath+"b2.png");
		batteryLevel[3].load(skinPath+"b3.png");
	}
	
	//UTIL_GetSignalQuality
	//[Signal]
	signalShow=config.readBoolEntry("Signal","Show");
	if(signalShow)
	{
		signalUseDefault=config.readBoolEntry("Signal","UseDefault");
		signalLeft=config.readNumEntry("Signal","Left");
		signalTop=config.readNumEntry("Signal","Top");
		signalLevel[0].load(skinPath+"s0.png");
		signalLevel[1].load(skinPath+"s1.png");
		signalLevel[2].load(skinPath+"s2.png");
		signalLevel[3].load(skinPath+"s3.png");
		signalLevel[4].load(skinPath+"s4.png");
		signalLevel[5].load(skinPath+"s5.png");
	}
	
	//[Notify]
	notifyShow=config.readBoolEntry("Notify","Show");
	if(notifyShow)
	{
		notifyLockIMG.load(skinPath+config.readEntry("Notify","LockIMG"));
		notifyUnlockIMG.load(skinPath+config.readEntry("Notify","UnlockIMG"));
		notifyLeft=config.readNumEntry("Notify","Left");
		notifyTop=config.readNumEntry("Notify","Top");
	}

//[MissCall]
	callShow=config.readBoolEntry("MissCall","Show");
	if(callShow)
	{
		callIMG.load(skinPath+config.readEntry("MissCall","IMG"));
		callLeft=config.readNumEntry("MissCall","Left");
		callTop=config.readNumEntry("MissCall","Top");
	}
	
//[NewMSG]
	MSGShow=config.readBoolEntry("NewMSG","Show");
	if(callShow)
	{
		MSGIMG.load(skinPath+config.readEntry("NewMSG","IMG"));
		MSGLeft=config.readNumEntry("NewMSG","Left");
		MSGTop=config.readNumEntry("NewMSG","Top");
	}
}

void softLock::timerEvent(QTimerEvent* e)
{
	if(isLock == true && isLcdOn == true && isCalling == false)
		update();
}

void softLock::keyReleaseEvent(QKeyEvent *event)
{
	//printf("key release %d\n", event->key());
	if(event->key() == 4152) // 左软键
	{
		if(isFstBtnEffective == false)
		{
			isFstBtnEffective = true;
			update();
			QTimer::singleShot(5000, this, SLOT( slotUnlockKeyTimeOut() ) );	
		}
	}
	if(event->key() == 4154) // 右软键
	{
		if(isFstBtnEffective == true)
		{
			hide();
			isLock = false;
			isFstBtnEffective = false;
			//isLcdOn = true;
			//isCalling = false;
			//isEndKey = false;
			missedCall = false;
			missedMsg = false;	
		}
	}
	/*if(event->key()==secondKey)
	{
		if(isFstBtnEffective)
		{
			isLock=false;
			missedCall=false;
			missedMsg=false;
			isFstBtnEffective=false;
			hide();
		}
	}
	if (event->key()==firstKey)
	{
		printf("first key active\n");
			isFstBtnEffective=true;
			update();
			QTimer::singleShot(keyTimeOut, this, SLOT(midKeyTimeOut()));
	}
	if(event->key()==65286)//open camera shell
	{

		isLock=false;
		missedCall=false;
		missedMsg=false;
		hide();
		ZKbMainWidget::keyPressEvent(event);
	}*/
}
void softLock::slotUnlockKeyTimeOut()
{
	isFstBtnEffective = false;
	update();
}
/*
void softLock::midKeyTimeOut()
{
	isFstBtnEffective=false;

	update();
}
void softLock::ensKeyTimeOut()
{
	isEndKey=false;
}
*/

void softLock::soltMessage( const QCString &msg, const QByteArray &data )
{
	//std::cout<<"msg is "<<msg<<std::endl;
	if(msg == "reloadConfig()")
	{
		init();
	}
	if(msg == "Quit()")	
	{
		qApp->quit();
	}
	if(msg == "sliderOpened")
	{
		hide();
		isLock = false;
		isFstBtnEffective = false;
		isLcdOn = true;
		isCalling = false;
		//isEndKey = false;
		missedCall = false;
		missedMsg = false;		
	}
	if(msg == "sliderClosed")
	{
		isLock = true;
		show();
		update();
	}	

	if(msg=="ON"||msg=="MO")
	{
		hide();		
		isCalling = true;
	}
	if(msg=="OFF"||msg=="ENDED")
	{
		isCalling = false;
		if(isLock == true)
		{
			show();
			update();
		}
	}
	if(msg == "LCDOn" || msg == "DPL_BKLGT_DIMMED"/* || msg = "DPL_BKLGT_RESTORED"*/)
	{
		isLcdOn = true;
		if(isLock == true)
			update();
	}
	if(msg == "LCDOff")
	{
		isLcdOn = false;	
	}
	//if(msg == "LCDOn")
	//{
		//printf("\nLCDOn\n");
		//isLcdOn == true;
		//if(isLock == true)
		//	update();
		
		/*time_t rawtime;
		nowTime=time(&rawtime);
		if(nowTime-oldTime<lockTime && isLock==false)//QTimer does not work well when lcd off,so I have to use this 
		{
			hide();
			
		}
		else if(isLcdOn==false)
		{

			isLock=true;
		}

		if(isLock && !UTIL_GetPhoneInCall())
			show();
		isLcdOn=true;*/

	//}
	//if(msg == "LCDOff")
	//{
	//	printf("\nLCDOff\n");
	//	isLcdOn = false;

		/*time_t rawtime;
		oldTime=time(&rawtime);

		if(!UTIL_GetPhoneInCall())
		{
			system("echo `pidof kvm`>>/tmp/iskvm.txt");
			QFile file("/tmp/iskvm.txt");
			file.open( IO_ReadOnly );
			
			if(file.size()<3)
			{
				show();
				printf("\nshow()\n");
			}
			file.close();
			system("rm -f /tmp/iskvm.txt");

		}*/
		
	//}
	//if(msg=="ReturnToIdle(int)")
	//{
		/*isLock = false;
		isFstBtnEffective = false;
		isLcdOn = true;
		isCalling = false;
		isEndKey = false;
		missedCall = false;
		missedMsg = false;	
		hide();*/
		/*if(isEndKey)
		{
			show();
			isLock=true;
			isEndKey=false;
		}
		else
		{
			isEndKey=true;
			QTimer::singleShot(500, this, SLOT(ensKeyTimeOut()));
		}*/
		
		
	//}
	if(msg == "RECENTCALL_MSG_2") 
	{ 
		if(isLock)
		{
			missedCall = true; 
			update(); 
		}
	}
	if(msg=="MSGAPI_SMS__MSG__IND_OF_INCOMING_MSG__INSMS_RECID") 
    { 
		if(isLock)
		{
			missedMsg = true; 
			update(); 
		}
    } 
}

void softLock::paintEvent(QPaintEvent * pe)
{
	nowScreen=backIMG;
	QPainter p(&nowScreen);
	p.begin(&nowScreen);	
	
	drawBackground(p);
	
	if(analogShow)
		drawAnalog(p);
	if(digitalShow)
		drawDigital(p);
	if(dateShow)
		drawDate(p);
	if(lunarShow)
		drawLunar(p);
	if(notifyShow)
		drawNotify(p);
	if(weekShow)
		drawWeek(p);
	if(batteryShow)
		drawBattery(p);
	if(signalShow)
		drawSignal(p);
	if(callShow)
		drawMissCall(p);
	if(MSGShow)
		drawNewMSG(p);

	p.end();
	
	bitBlt(this,0,0,&nowScreen,0); 

	QWidget::paintEvent( pe);
}

void softLock::drawAnalog(QPainter &p)
{
	p.drawPixmap(analogLeft,analogTop,analogBackIMG);
	
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	
	QWMatrix h;                         // transformation matrix

	h.rotate( (float)(timeinfo->tm_hour%12)*30+(float)(timeinfo->tm_min%60)*0.25);
	//printf("\nrotate:%f",(float)(timeinfo->tm_hour%12)*15.0+(float)(timeinfo->tm_min%60)*0.25);
	QPixmap hour = analogHourIMG.xForm( h );  
	p.drawPixmap((analogBackIMG.width()-hour.width())/2+analogLeft,(analogBackIMG.height()-hour.height())/2+analogTop,hour);

	QWMatrix m;                         // transformation matrix

	m.rotate( (float)(timeinfo->tm_min%60)*6.0);
	
	QPixmap min = analogMinIMG.xForm( m );  
	p.drawPixmap((analogBackIMG.width()-min.width())/2+analogLeft,(analogBackIMG.height()-min.height())/2+analogTop,min);

	if(analogSecShow)
	{
		QWMatrix s;                         // transformation matrix

		s.rotate( (float)(timeinfo->tm_sec%60)*6.0);
	
		QPixmap sec = analogSecIMG.xForm( s );  
		p.drawPixmap((analogBackIMG.width()-sec.width())/2+analogLeft,(analogBackIMG.height()-sec.height())/2+analogTop,sec);
	}
}

void softLock::drawDigital(QPainter &p)
{
	//printf("\ndraw digital\n");
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
		
	p.drawPixmap(DHLeft,DHTop,digitalFontIMG,0,timeinfo->tm_hour/10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
		
	p.drawPixmap(DHLeft+digitalFontIMG.width(),DHTop,digitalFontIMG,0,timeinfo->tm_hour%10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
	
	p.drawPixmap(HMLeft,HMTop,digitalFontIMG,0,10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
	
	p.drawPixmap(DMLeft,DMTop,digitalFontIMG,0,timeinfo->tm_min/10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
		
	p.drawPixmap(DMLeft+digitalFontIMG.width(),DMTop,digitalFontIMG,0,timeinfo->tm_min%10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
	
	if(digitalSecShow)
	{
		p.drawPixmap(MSLeft,MSTop,digitalFontIMG,0,10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
	
		p.drawPixmap(DSLeft,DSTop,digitalFontIMG,0,timeinfo->tm_sec/10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
		
		p.drawPixmap(DSLeft+digitalFontIMG.width(),DSTop,digitalFontIMG,0,timeinfo->tm_sec%10*digitalFontIMG.height()/11,digitalFontIMG.width(),digitalFontIMG.height()/11);
	}	
}


void softLock::drawDate(QPainter &p)
{
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	Date tdate;
	tdate.year=timeinfo->tm_year+1900;
	tdate.month=timeinfo->tm_mon+1;
	tdate.day=timeinfo->tm_mday;
	
	int yearshow=0;

	if(dateYearShow)
	{
		p.drawPixmap(yearLeft,yearTop,dateFontIMG,0,tdate.year/1000*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		p.drawPixmap(yearLeft+dateFontIMG.width(),yearTop,dateFontIMG,0,tdate.year%1000/100*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		p.drawPixmap(yearLeft+dateFontIMG.width()*2,yearTop,dateFontIMG,0,tdate.year%100/10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		p.drawPixmap(yearLeft+dateFontIMG.width()*3,yearTop,dateFontIMG,0,tdate.year%10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		
		p.drawPixmap(YMLeft,YMTop,dateFontIMG,0,10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		yearshow=5;
	}
	
	p.drawPixmap(mouLeft,mouTop,dateFontIMG,0,tdate.month/10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		
	p.drawPixmap(mouLeft+dateFontIMG.width(),mouTop,dateFontIMG,0,tdate.month%10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		
	p.drawPixmap(MDLeft,MDTop,dateFontIMG,0,10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
	
	p.drawPixmap(dayLeft,dayTop,dateFontIMG,0,tdate.day/10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
		
	p.drawPixmap(dayLeft+dateFontIMG.width(),dayTop,dateFontIMG,0,tdate.day%10*dateFontIMG.height()/11,dateFontIMG.width(),dateFontIMG.height()/11);
}

void softLock::drawLunar(QPainter &p)
{
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	Date tdate;
	tdate.year=timeinfo->tm_year+1900;
	tdate.month=timeinfo->tm_mon+1;
	tdate.day=timeinfo->tm_mday;
	
	/*static*/ QString nltemp;
	GetDayOf(tdate,nltemp);
	//std::cout<<"nltemp "<<nltemp<<std::endl;
	//std::cout<<"nltemp2 "<<nltemp.utf8()<<std::endl;
	//std::cout<<"nltemp3 "<<ctr(nltemp)<<std::endl;
	
	//std::cout<<"nltemp4 "<<ctr(nltemp).latin1()<<std::endl;
	
	QFont f("AMCSL",lunarFontSize);	//设置字体大小
	p.setFont(f);
	QPen pen(lunarFontColor,1);
	p.setPen(pen);

	p.drawText(lunarLeft,lunarTop, nltemp);

}

void softLock::drawNotify(QPainter &p)
{
	if(isFstBtnEffective)
		p.drawPixmap(notifyLeft,notifyTop,notifyUnlockIMG);
	else
		p.drawPixmap(notifyLeft,notifyTop,notifyLockIMG);
	
}

void softLock::drawMissCall(QPainter &p)
{

	if(missedCall)
		p.drawPixmap(callLeft,callTop,callIMG);
}
void softLock::drawNewMSG(QPainter &p)
{
	if(missedMsg)
		p.drawPixmap(MSGLeft,MSGTop,MSGIMG);
}

void softLock::drawBackground(QPainter &p)
{
	p.drawPixmap(0,0,centerIMG);
}
void softLock::drawWeek(QPainter &p)
{
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	
	p.drawPixmap(weekLeft,weekTop,weekResIMG,0,weekResIMG.height()/7*timeinfo->tm_wday,weekResIMG.width(),weekResIMG.height()/7);
}

void softLock::drawBattery(QPainter &p)
{
	if(oldBatteryLevel!=UTIL_GetBatteryLevel())
		oldBatteryLevel=UTIL_GetBatteryLevel();

	int batNum;
	if(oldBatteryLevel>=3)
	{
		batNum=oldBatteryLevel-2;
	}
	else
	{
		batNum=oldBatteryLevel/2;
	}
	if(batteryUseDefault)
	{
		char icon[50];
		sprintf(icon,"batt_level_%d_idle10.g",batNum);
		RES_ICON_Reader iconReaderBat;
		//batteryLevel = iconReaderBat.getIcon(icon);
		p.drawPixmap(batteryLeft, batteryTop, iconReaderBat.getIcon(icon));
	}
	else
	{
		//sprintf(icon,"Level%d",batNum);
		//batteryLevel.load(skinPath+config->readEntry("Battery",icon));
		p.drawPixmap(batteryLeft, batteryTop, batteryLevel[batNum]);
	}	
}

void softLock::drawSignal(QPainter &p)
{
	if(oldSignalLevel!=UTIL_GetSignalQuality())
		oldSignalLevel = UTIL_GetSignalQuality();
	
	if(signalUseDefault)
	{
		char icon[50];
		sprintf(icon,"signal_%d_idle1.g",oldSignalLevel);
		RES_ICON_Reader iconReader;
		//signalLevel=iconReader.getIcon(icon);
		p.drawPixmap(signalLeft, signalTop, iconReader.getIcon(icon));
	}
	else
	{
		//sprintf(icon,"Level%d",oldSignalLevel);
		//signalLevel.load(skinPath+config->readEntry("Signal",icon));
		p.drawPixmap(signalLeft, signalTop, signalLevel[oldSignalLevel]);

	}
	//p.drawPixmap(signalLeft,signalTop,signalLevel);
}




void softLock::GetDayOf(Date &tdate,QString &strLuner) 
{ 
/*天干名称*/ 
const char *cTianGan[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"}; 
/*地支名称*/ 
const char *cDiZhi[] = {"子","丑","寅","卯","辰","巳","午", 
"未","申","酉","戌","亥"}; 
/*属相名称*/ 
const char *cShuXiang[] = {"鼠","牛","虎","兔","龙","蛇", 
"马","羊","猴","鸡","狗","猪"}; 
/*农历日期名*/ 
const char *cDayName[] = {"*","初一","初二","初三","初四","初五", 
"初六","初七","初八","初九","初十", 
"十一","十二","十三","十四","十五", 
"十六","十七","十八","十九","二十", 
"廿一","廿二","廿三","廿四","廿五", 
"廿六","廿七","廿八","廿九","三十"}; 
/*农历月份名*/ 
const char *cMonName[] = {"*","正","二","三","四","五","六", 
"七","八","九","十","十一","腊"}; 

/*公历每月前面的天数*/ 
const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334}; 
/*农历数据*/ 
const int wNongliData[100] = 
{2635,333387,1701,1748,267701,694,2391,133423,1175,396438 
,3402,3749,331177,1453,694,201326,2350,465197,3221,3402 
,400202,2901,1386,267611,605,2349,137515,2709,464533,1738 
,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762 
,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413 
,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395 
,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031 
,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222 
,268949,3402,3493,133973,1386,464219,605,2349,334123,2709 
,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877}; 
static int wCurYear,wCurMonth,wCurDay; 
static int nTheDate,nIsEnd,m,k,n,i,nBit; 
//char szNongli[30], szNongliDay[10],szShuXiang[10]; 
/*---取当前公历年、月、日-- -*/ 
wCurYear = tdate.year; 
wCurMonth = tdate.month; 
wCurDay = tdate.day;
/*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/ 
nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd 
[wCurMonth - 1] - 38; 
if((!(wCurYear % 4)) && (wCurMonth > 2)) 
nTheDate = nTheDate + 1; 

/*--计算农历天干、地支、月、日---*/ 
nIsEnd = 0; 
m = 0; 
while(nIsEnd != 1) 
{ 
	if(wNongliData[m] < 4095) 
		k = 11; 
	else 
		k = 12; 
	n = k; 
	while(n>=0) 
	{ 
		//获取wNongliData(m)的第n个二进制位的值 
		nBit = wNongliData[m]; 
		for(i=1;i<n+1;i++) 
		nBit = nBit/2; 

		nBit = nBit % 2; 

		if (nTheDate <= (29 + nBit)) 
		{ 
			nIsEnd = 1; 
			break; 
		} 

		nTheDate = nTheDate - 29 - nBit; 
		n = n - 1; 
	} 
	if(nIsEnd) 
		break; 
	m = m + 1; 
} 
wCurYear = 1921 + m; 
wCurMonth = k - n + 1; 
wCurDay = nTheDate; 
if (k == 12) 
{ 
	if (wCurMonth == wNongliData[m] / 65536 + 1) 
		wCurMonth = 1 - wCurMonth; 
	else if (wCurMonth > wNongliData[m] / 65536 + 1) 
		wCurMonth = wCurMonth - 1; 
} 

/*--生成农历天干、地支、属相 ==> wNongli--*/ 

strLuner =  ctr( cShuXiang[((wCurYear - 4) % 60) % 12] );
strLuner          +=  ctr("\(");
strLuner          += ctr( cTianGan[((wCurYear - 4) % 60) % 10] );
strLuner          += ctr( cDiZhi[((wCurYear - 4) % 60) % 12] );
strLuner          += ctr( ")年" );

/*--生成农历月、日 ==> wNongliDay--*/ 
if (wCurMonth < 1)
{
 	strLuner = strLuner +  ctr( "闰" )
         	+  ctr( cMonName[-1 * wCurMonth] );
}
else
{
	strLuner = strLuner +  ctr( cMonName[wCurMonth] );
}
strLuner = strLuner +  ctr( "月" )
           +  ctr( cDayName[wCurDay] );

} 



