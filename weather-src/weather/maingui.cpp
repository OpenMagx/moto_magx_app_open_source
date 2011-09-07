/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#include "maingui.h"
#include "code.h"
#include <ZConfig.h>
#include <ZKeyDef.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtimer.h>
#include <ZSingleSelectDlg.h>
#include <ZSingleCaptureDlg.h>
#include <ZMessageDlg.h>
#include <qdir.h>
#include <unistd.h>
#include <AM_AppRegistry.h>
#include <ZNoticeDlg.h>
#include <iostream>
using namespace std;

MainGui::MainGui(QWidget* parent, const char* name, WFlags f):ZKbMainWidget(parent, name, f),canvas(640, 240),curpage(0),freshframe(0),freshing(false),showsetup(false),showwp(false),panel(0)
{
	setFullScreenMode(true);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(stopMove()));
	freshtimer = new QTimer(this);
	connect(freshtimer, SIGNAL(timeout()), this, SLOT(freshicon()));
	connect(this, SIGNAL(freshWallpaper()), this, SLOT(slotFreshWallpaper()));
	ZConfig setupconf(SETUPPATH);
	cityid = setupconf.readEntry("SETUP", "cityid");
	skin = setupconf.readEntry("SETUP", "skin");
	
	
	loadSkinConfig();
	loadInfoConfig();
	canvas.setAdvancePeriod(10);
	cv = new QCanvasView(&canvas, this);
    cv->setHScrollBarMode(QScrollView::AlwaysOff);
    cv->setVScrollBarMode(QScrollView::AlwaysOff);
    cv->setFrameStyle(QFrame::NoFrame);
    setContentWidget(cv);	
	
	qs_bottom = new QCanvasSprite(&pix_bottom, &canvas);

	qs_center1 = new QCanvasSprite(&pix_center1, &canvas);
	qs_center2 = new QCanvasSprite(&pix_center2, &canvas);
	qs_left = new QCanvasSprite(&pix_left, &canvas);
	qs_right = new QCanvasSprite(&pix_right, &canvas);
	qs_icon1 = new QCanvasSprite(&pix_bweather, &canvas);
	qs_icon2 = new QCanvasSprite(&pix_sweather, &canvas);
	qs_icon3 = new QCanvasSprite(&pix_sweather, &canvas);
	qs_icon4 = new QCanvasSprite(&pix_sweather, &canvas);	
	//qs_none = new QCanvasSprite(&pix_none, &canvas);	
	qs_refresh = new QCanvasSprite(&pix_refresh, &canvas);
	qs_refresh->setSequence(&pix_refresh);
	qs_refresh->move((320-(qs_refresh->boundingRect()).width())/2, (240-(qs_refresh->boundingRect()).height())/2);
	qs_setup = new QCanvasSprite(&pix_setup, &canvas);
	qs_setup->setSequence(&pix_setup);
	qs_setup->move((320-(qs_setup->boundingRect()).width())/2, (240-(qs_setup->boundingRect()).height())/2);
		
	qt_error = new QCanvasText(&canvas);
	qt_error->move(0, 200);
	qt_error->setFont(QFont("AMCSL",40,QFont::Bold));
	qt_error->setColor(red);
	qt_city = new QCanvasText(&canvas);
	qt_temp1 = new QCanvasText(&canvas);
	qt_weather1 = new QCanvasText(&canvas);
	qt_time1 = new QCanvasText(&canvas);
	qt_wind1 = new QCanvasText(&canvas);
	qt_uv = new QCanvasText(&canvas);
	qt_temp2 = new QCanvasText(&canvas);
	qt_weather2 = new QCanvasText(&canvas);
	qt_temp3 = new QCanvasText(&canvas);
	qt_weather3 = new QCanvasText(&canvas);
	qt_temp4 = new QCanvasText(&canvas);
	qt_weather4 = new QCanvasText(&canvas);
	

	qs_bottom->setZ(1);
	qs_center1->setZ(2);
	qs_icon1->setZ(3);
	qs_icon2->setZ(3);
	qs_icon3->setZ(3);
	qs_icon4->setZ(3);
	qs_left->setZ(3);
	qs_right->setZ(3);
	qt_city->setZ(3);
	qt_temp1->setZ(3);
	qt_time1->setZ(3);
	qt_weather1->setZ(3);
	qt_wind1->setZ(3);
	qt_uv->setZ(3);
	qt_temp2->setZ(3);
	qt_temp3->setZ(3);
	qt_temp4->setZ(3);
	qt_weather2->setZ(3);
	qt_weather3->setZ(3);
	qt_weather4->setZ(3);
	qs_refresh->setZ(10);
	qt_error->setZ(20);

	qs_setup->setZ(20);
	

	creatUi();
	qs_bottom->show();
	qs_center1->show();
	qs_center2->show();
	qs_left->show();
	qs_right->show();
	qs_icon1->show();
	qs_icon2->show();
	qs_icon3->show();
	qs_icon4->show();
	
	
	qt_wind1->show();
	qt_city->show();
	qt_temp1->show();
	qt_weather1->show();
	qt_time1->show();
	qt_uv->show();
	
	qt_temp2->show();
	qt_weather2->show();
	qt_temp3->show();
	qt_weather3->show();
	qt_temp4->show();
	qt_weather4->show();
	
	
}
MainGui::~MainGui()
{
	delete qs_center1;
	delete timer;
	delete freshtimer;
	delete cv;
	delete qs_bottom;
	delete qs_center1;
	delete qs_center2;
	delete qs_left;
	delete qs_right;
	delete qs_icon1;
	delete qs_icon2;
	delete qs_icon3;
	delete qs_icon4;
	delete qs_refresh;
	delete qs_setup;
	delete qt_city;
	delete qt_temp1;
	delete qt_weather1;
	delete qt_time1;
	delete qt_temp2;
	delete qt_weather2;
	delete qt_temp3;
	delete qt_weather3;
	delete qt_temp4;
	delete qt_weather4;
	delete qt_error;
	delete qt_wind1;
	delete qt_uv;
}

void MainGui::creatUi()
{
	canvas.setBackgroundPixmap(pix_background);
	qs_bottom->move(p_bottom.x(), p_bottom.y());
	qs_center1->move(p_center1.x(), p_center1.y());
	qs_center2->move(p_center2.x()+320, p_center2.y());
	qs_left->move(p_left.x(), p_left.y());
	qs_right->move(p_right.x(), p_right.y());
	qs_icon1->move(p_icon1.x(), p_icon1.y());
	qs_icon1->setFrame(img1);
	
	
	qt_city->setText(city);
	qt_temp1->setText(temp1);
	qt_weather1->setText(weather1);
	qt_time1->setText(time1);
	qt_wind1->setText(wind1);
	qt_uv->setText(uv);
	qt_city->move(p_city.x(), p_city.y());
	qt_temp1->move(p_temp1.x(), p_temp1.y());
	qt_weather1->move(p_weather1.x(), p_weather1.y());
	qt_time1->move(p_time1.x(), p_time1.y());
	qt_wind1->move(p_wind1.x(), p_wind1.y());
	qt_uv->move(p_uv.x(), p_uv.y());
	
	
	qs_icon2->move(p_icon2.x()+320, p_icon2.y());
	qs_icon2->setFrame(img2);
	qs_icon3->move(p_icon3.x()+320, p_icon3.y());
	qs_icon3->setFrame(img3);
	qs_icon4->move(p_icon4.x()+320, p_icon4.y());
	qs_icon4->setFrame(img4);
	
	qt_temp2->setText(temp2);
	qt_temp3->setText(temp3);
	qt_temp4->setText(temp4);
	qt_weather2->setText(weather2);
	qt_weather3->setText(weather3);
	qt_weather4->setText(weather4);
	
	
	qt_temp2->move(p_time2.x()+320, p_time2.y());
	qt_temp3->move(p_time3.x()+320, p_time3.y());
	qt_temp4->move(p_time4.x()+320, p_time4.y());
	qt_weather2->move(p_weather2.x()+320, p_weather2.y());
	qt_weather3->move(p_weather3.x()+320, p_weather3.y());
	qt_weather4->move(p_weather4.x()+320, p_weather4.y());
	
	qt_city->setFont(QFont("AMCSL",size_city,QFont::Bold));
	qt_city->setColor(co_city);
	qt_temp1->setFont(QFont("AMCSL",size_temp1,QFont::Bold));
	qt_temp1->setColor(co_temp1);
	qt_weather1->setFont(QFont("AMCSL",size_weather1,QFont::Normal));
	qt_weather1->setColor(co_weather1);
	qt_wind1->setFont(QFont("AMCSL",size_weather1,QFont::Normal));
	qt_wind1->setColor(co_weather1);
	qt_time1->setFont(QFont("AMCSL",size_panel1,QFont::Normal));
	qt_time1->setColor(co_panel1);
	qt_uv->setFont(QFont("AMCSL",size_panel1,QFont::Normal));
	qt_uv->setColor(co_panel1);
	
	qt_temp2->setFont(QFont("AMCSL",size_panel2,QFont::Bold));
	qt_temp3->setFont(QFont("AMCSL",size_panel2,QFont::Bold));
	qt_temp4->setFont(QFont("AMCSL",size_panel2,QFont::Bold));
	qt_weather2->setFont(QFont("AMCSL",size_panel2,QFont::Bold));
	qt_weather3->setFont(QFont("AMCSL",size_panel2,QFont::Bold));
	qt_weather4->setFont(QFont("AMCSL",size_panel2,QFont::Bold));
	
	qt_temp2->setColor(co_panel2);
	qt_temp3->setColor(co_panel2);
	qt_temp4->setColor(co_panel2);
	qt_weather2->setColor(co_panel2);
	qt_weather3->setColor(co_panel2);
	qt_weather4->setColor(co_panel2);
	curpage = 0;
	
}

void MainGui::loadSkinConfig()
{

	ZConfig skinconf(getAppDir()+"skins/"+skin+"/skin.ini");
	pix_background.load(getAppDir()+"skins/"+skin+"/panel/background.png");
	pix_bottom.readPixmaps(getAppDir()+"skins/"+skin+"/panel/bottom.png");
	p_bottom.setX(skinconf.readUIntEntry("panel1", "bottombar_x"));
	p_bottom.setY(skinconf.readUIntEntry("panel1", "bottombar_y"));
	pix_center1.readPixmaps(getAppDir()+"skins/"+skin+"/panel/center1.png");
	p_center1.setX(skinconf.readUIntEntry("panel1", "center1_x"));
	p_center1.setY(skinconf.readUIntEntry("panel1", "center1_y"));
	
	pix_center2.readPixmaps(getAppDir()+"skins/"+skin+"/panel/center2.png");
	p_center2.setX(skinconf.readUIntEntry("panel2", "center2_x"));
	p_center2.setY(skinconf.readUIntEntry("panel2", "center2_y"));
	
	pix_left.readPixmaps(getAppDir()+"skins/"+skin+"/panel/left.png");
	pix_right.readPixmaps(getAppDir()+"skins/"+skin+"/panel/right.png");
	p_left.setX(skinconf.readUIntEntry("panel1", "left_x"));
	p_left.setY(skinconf.readUIntEntry("panel1", "left_y"));
	p_right.setX(skinconf.readUIntEntry("panel1", "right_x"));
	p_right.setY(skinconf.readUIntEntry("panel1", "right_y"));
	
	
	QString s0 = "b0001.png";
    s0.replace(QRegExp("0001"),"%1");
	pix_bweather.readPixmaps(getAppDir()+"weathericon/"+skinconf.readEntry("panel1", "weathericon")+"/bigicon/"+s0, 32);
	
	s0 = "s0001.png";
	s0.replace(QRegExp("0001"),"%1");
	pix_sweather.readPixmaps(getAppDir()+"weathericon/"+skinconf.readEntry("panel1", "weathericon")+"/smallicon/"+s0, 32);
	
	s0 = "fresh0001.png";
	s0.replace(QRegExp("0001"),"%1");
	pix_refresh.readPixmaps(getAppDir()+"skins/"+skin+"/panel/"+s0, 4);	
	
	s0 = "setup0001.png";
	s0.replace(QRegExp("0001"),"%1");
	pix_setup.readPixmaps(getAppDir()+"skins/"+skin+"/panel/"+s0, 7);	
	
	
	
	p_icon1.setX(skinconf.readUIntEntry("panel1", "icon1_x"));
	p_icon1.setY(skinconf.readUIntEntry("panel1", "icon1_y"));
	p_icon2.setX(skinconf.readUIntEntry("panel2", "icon2_x"));
	p_icon2.setY(skinconf.readUIntEntry("panel2", "icon2_y"));
	p_icon3.setX(skinconf.readUIntEntry("panel2", "icon3_x"));
	p_icon3.setY(skinconf.readUIntEntry("panel2", "icon3_y"));
	p_icon4.setX(skinconf.readUIntEntry("panel2", "icon4_x"));
	p_icon4.setY(skinconf.readUIntEntry("panel2", "icon4_y"));
	
	p_city.setX(skinconf.readUIntEntry("panel1", "city_x"));
	p_city.setY(skinconf.readUIntEntry("panel1", "city_y"));
	
	p_temp1.setX(skinconf.readUIntEntry("panel1", "temp1_x"));
	p_temp1.setY(skinconf.readUIntEntry("panel1", "temp1_y"));
	p_weather1.setX(skinconf.readUIntEntry("panel1", "weather1_x"));
	p_weather1.setY(skinconf.readUIntEntry("panel1", "weather1_y"));
	p_time1.setX(skinconf.readUIntEntry("panel1", "time1_x"));
	p_time1.setY(skinconf.readUIntEntry("panel1", "time1_y"));
	p_wind1.setX(skinconf.readUIntEntry("panel1", "wind1_x"));
	p_wind1.setY(skinconf.readUIntEntry("panel1", "wind1_y"));
	p_uv.setX(skinconf.readUIntEntry("panel1", "uv_x"));
	p_uv.setY(skinconf.readUIntEntry("panel1", "uv_y"));
	
	p_time2.setX(skinconf.readUIntEntry("panel2", "time2_x"));
	p_time2.setY(skinconf.readUIntEntry("panel2", "time2_y"));
	p_time3.setX(skinconf.readUIntEntry("panel2", "time3_x"));
	p_time3.setY(skinconf.readUIntEntry("panel2", "time3_y"));
	p_time4.setX(skinconf.readUIntEntry("panel2", "time4_x"));
	p_time4.setY(skinconf.readUIntEntry("panel2", "time4_y"));
	
	p_weather2.setX(skinconf.readUIntEntry("panel2", "weather2_x"));
	p_weather2.setY(skinconf.readUIntEntry("panel2", "weather2_y"));
	p_weather3.setX(skinconf.readUIntEntry("panel2", "weather3_x"));
	p_weather3.setY(skinconf.readUIntEntry("panel2", "weather3_y"));
	p_weather4.setX(skinconf.readUIntEntry("panel2", "weather4_x"));
	p_weather4.setY(skinconf.readUIntEntry("panel2", "weather4_y"));
	
	size_city = skinconf.readUIntEntry("panel1", "city_size");
	co_city .setRgb(skinconf.readUIntEntry("panel1", "city_R"), skinconf.readUIntEntry("panel1", "city_G"), skinconf.readUIntEntry("panel1", "city_B"));
	size_temp1 = skinconf.readUIntEntry("panel1", "temp1_size");
	co_temp1.setRgb(skinconf.readUIntEntry("panel1", "temp1_R"), skinconf.readUIntEntry("panel1", "temp1_G"), skinconf.readUIntEntry("panel1", "temp1_B"));
	size_panel1 =  skinconf.readUIntEntry("panel1", "panel1_size");
	co_panel1.setRgb(skinconf.readUIntEntry("panel1", "panel1_R"), skinconf.readUIntEntry("panel1", "panel1_G"), skinconf.readUIntEntry("panel1", "panel1_B"));
	size_weather1 =  skinconf.readUIntEntry("panel1", "weather1_size");
	co_weather1.setRgb(skinconf.readUIntEntry("panel1", "weather1_R"), skinconf.readUIntEntry("panel1", "weather1_G"), skinconf.readUIntEntry("panel1", "weather1_B"));
	
	size_panel2 = skinconf.readUIntEntry("panel2", "panel2_size");
	co_panel2.setRgb(skinconf.readUIntEntry("panel2", "panel2_R"), skinconf.readUIntEntry("panel2", "panel2_G"), skinconf.readUIntEntry("panel2", "panel2_B"));
	
}

void MainGui::loadInfoConfig()
{	
	ZConfig infoconf(INFOPATH);
	citylist.clear();
	infoconf.getGroupsKeyList(citylist);
	img1 = infoconf.readUIntEntry(cityid, "img1");
	img2 = infoconf.readUIntEntry(cityid, "img3");
	img3 = infoconf.readUIntEntry(cityid, "img5");
	img4 = infoconf.readUIntEntry(cityid, "img7");	
	
	city = infoconf.readEntry(cityid, "city");
	temp1 = infoconf.readEntry(cityid, "temp1");
	weather1 = infoconf.readEntry(cityid, "weather1", QString::fromUtf8("没有天气内容\n请设置城市并更新"));
	wind1 = infoconf.readEntry(cityid, "wind1");
	time1 = infoconf.readEntry(cityid, "date_y", QString::fromUtf8("侧键刷新\n左软键弹出设置菜单"))+"\n"+infoconf.readEntry(cityid, "date");
	uv = QString::fromUtf8("舒适度：")+infoconf.readEntry(cityid, "index_co")+"\n"+QString::fromUtf8("紫外线强度：")+infoconf.readEntry(cityid, "index_uv");
	
	temp2 = QString::fromUtf8("明天    ")+infoconf.readEntry(cityid, "wind2");
	weather2 = infoconf.readEntry(cityid, "temp2")+"   "+infoconf.readEntry(cityid, "weather2");
	temp3 = QString::fromUtf8("后天    ")+infoconf.readEntry(cityid, "wind3");
	weather3 = infoconf.readEntry(cityid, "temp3")+"   "+infoconf.readEntry(cityid, "weather3");
	temp4 = QString::fromUtf8("大后天 ")+infoconf.readEntry(cityid, "wind3");
	weather4 = infoconf.readEntry(cityid, "temp4")+"   "+infoconf.readEntry(cityid, "weather4");
}

void MainGui::keyPressEvent(QKeyEvent *e)
{
	QCanvasItemList list = canvas.allItems();
	switch(e->key())
	{
		case KEYCODE_LSK:
			if(showwp)
			{
				ZConfig conf(SETUPPATH);
				if(panel==1)
				{
					int i = qs_wppanel->x();
					int j = qs_wppanel->y();
					conf.writeEntry("WP", "panel_x", i);
					conf.writeEntry("WP", "panel_y", j);
				}
				else if(panel==2)
				{
					int i = qs_wppanel->x();
					int j = qs_wppanel->y();
					conf.writeEntry("WP", "alarmpanel_x", i);
					conf.writeEntry("WP", "alarmpanel_y", j);					
				}
				conf.flush();
				delete qs_wppanel;
				showwp = false;
				emit freshWallpaper();
			}
			else
			{
				qs_setup->show();
				showsetup = true;
			}
			break;
		case KEYCODE_RSK:
			if(showwp)
			{
				delete qs_wppanel;
				showwp = false;
			}
			else
			{
				qs_setup->hide();
				showsetup = false;
			}
			break;
		case KEYCODE_LEFT:
			if(showwp)
			{
				qs_wppanel->moveBy(-5, 0);
			}
			else if(showsetup)
			{
				if(qs_setup->frame()==0)
				qs_setup->setFrame(6);
				else
				qs_setup->setFrame((qs_setup->frame())-1);
			}
			else if(curpage==1 && !freshing)
			{
				for(QCanvasItemList::Iterator it = list.begin(); it!=list.end(); ++it)
				{
					(*it)->setVelocity(10, 0);
					QTimer::singleShot(500, this, SLOT(sTime()));
				}
				curpage=0;
			}
			break;
		case KEYCODE_RIGHT:
			if(showwp)
			{
				qs_wppanel->moveBy(5, 0);
			}
			else if(showsetup)
			{
				if(qs_setup->frame()==6)
				qs_setup->setFrame(0);
				else
				qs_setup->setFrame((qs_setup->frame())+1);
			}
			else if(curpage==0 && !freshing)
			{
				for(QCanvasItemList::Iterator it = list.begin(); it!=list.end(); ++it)
				{
					(*it)->setVelocity(-10, 0);
					QTimer::singleShot(500, this, SLOT(sTime()));
				}
				curpage=1;
			}
			break;
		case KEYCODE_UP:
			if(showwp)
			{
				qs_wppanel->moveBy(0, -5);
			}
			else if(curpage==0 && !freshing && !showsetup)
			{
				unsigned int i = citylist.findIndex(cityid);
				if(i==0)
				cityid = citylist.last();
				else
				cityid = citylist[i-1];
				loadInfoConfig();
				creatUi();
			}
			break;
		case KEYCODE_DOWN:
			if(showwp)
			{
				qs_wppanel->moveBy(0, 5);
			}
			else if(curpage==0 && !freshing && !showsetup)
			{
				unsigned int i = citylist.findIndex(cityid);
				if(i==citylist.count()-1)
				cityid = citylist.first();
				else
				cityid = citylist[i+1];
				loadInfoConfig();
				creatUi();
			}
			break;
		case KEYCODE_CENTER_SELECT:
			if(showsetup)
			{
				slotSetup();
			}
			break;
		case KEYCODE_SIDE_SELECT:
			if(!freshing && !showsetup && !showwp)
			refresh();
			break;
		case KEYCODE_END:
			qApp->quit();
			break;
	}
}

void MainGui::sTime()
{
	timer->start(10);
}

void MainGui::stopMove()
{
	if(((p_left.x())-(qs_left->x()))>=320 || ((p_left.x())<=(qs_left->x())))
	{

		QCanvasItemList list = canvas.allItems();
		for(QCanvasItemList::Iterator it = list.begin(); it!=list.end(); ++it)
		{
			(*it)->setVelocity(0, 0);
		}
		timer->stop();
	}
}

void MainGui::refresh()
{
	freshing = true;
	qs_refresh->show();
	freshtimer->start(500);
	data = new GetData(cityid);
	data->setCityid(cityid);
	if(data->init())
	{
		connect(data, SIGNAL(success()), this, SLOT(slotFresh()));
		connect(data, SIGNAL(signalError(int)), this, SLOT(slotDataError(int)));
	}
	else
	{
	slotDataError(4);
	}
	QTimer::singleShot(60000, this, SLOT(slotTimeOut()));
}

void MainGui::slotFresh()
{
	freshing = false;
	freshtimer->stop();
	qs_refresh->hide();
	delete data;
	loadInfoConfig();
	creatUi();
	emit freshWallpaper();
}

void MainGui::slotDataError(int value)
{
	freshing = false;
	freshtimer->stop();
	qs_refresh->hide();
	QString errstr;
	delete data;
	switch(value)
	{
		case 0:
		errstr = QString::fromUtf8("错误：未找到服务器");
		break;
		case 1:
		errstr = QString::fromUtf8("错误：服务器拒绝");
		break;
		case 2:
		errstr = QString::fromUtf8("错误：读取套接字失败");
		break;
		case 3:
		errstr = QString::fromUtf8("错误：套接字初始化失败");
		break;
		case 4:
		errstr = QString::fromUtf8("错误：打开连接失败");
		break;
		case 5:
		errstr = QString::fromUtf8("错误：读取数据失败");
		break;
		case 6:
		errstr = QString::fromUtf8("错误：连接超时"); 
	}
	qt_error->setText(errstr);
	qt_error->show();
	QTimer::singleShot(5000, this, SLOT(slotHideErrinfo()));
}
void MainGui::freshicon()
{
	qs_refresh->setFrame(freshframe++);
	if(freshframe==4)
	freshframe =0;
}

void MainGui::slotTimeOut()
{
	if(freshing)
	slotDataError(6);
}
void MainGui::slotHideErrinfo()
{
	qt_error->hide();
}

void MainGui::slotSetup()
{
	qs_setup->hide();
	showsetup = false;
	int i = qs_setup->frame();
	if(i==0)
	{
	QStringList list;
	list = QString::fromUtf8("添加城市");
	list += QString::fromUtf8("删除城市");
	ZSingleSelectDlg *dlg= new ZSingleSelectDlg(QString::fromUtf8("城市设置"), NULL);
	dlg->addItemsList(list);
	if(dlg->exec()==ZPopup::Accepted)
	{
		int j = dlg->getCheckedItemIndex();
		if(j==0)
		{
		QString newcity;
		QString citys = QString::fromUtf8("北京:101010100朝阳:101010300顺义:101010400怀柔:101010500通州:101010600昌平:101010700延庆:101010800丰台:101010900石景山:101011000大兴:101011100房山:101011200密云:101011300门头沟:101011400平谷:101011500八达岭:101011600佛爷顶:101011700汤河口:101011800密云上甸子:101011900斋堂:101012000霞云岭:101012100北京城区:101012200海淀:101010200天津:101030100宝坻:101030300东丽:101030400西青:101030500北辰:101030600蓟县:101031400汉沽:101030800静海:101030900津南:101031000塘沽:101031100大港:101031200武清:101030200宁河:101030700上海:101020100宝山:101020300嘉定:101020500南汇:101020600浦东:101021300青浦:101020800松江:101020900奉贤:101021000崇明:101021100徐家汇:101021200闵行:101020200金山:101020700石家庄:101090101张家口:101090301承德:101090402唐山:101090501秦皇岛:101091101沧州:101090701衡水:101090801邢台:101090901邯郸:101091001保定:101090201廊坊:101090601郑州:101180101新乡:101180301许昌:101180401平顶山:101180501信阳:101180601南阳:101180701开封:101180801洛阳:101180901商丘:101181001焦作:101181101鹤壁:101181201濮阳:101181301周口:101181401漯河:101181501驻马店:101181601三门峡:101181701济源:101181801安阳:101180201合肥:101220101芜湖:101220301淮南:101220401马鞍山:101220501安庆:101220601宿州:101220701阜阳:101220801亳州:101220901黄山:101221001滁州:101221101淮北:101221201铜陵:101221301宣城:101221401六安:101221501巢湖:101221601池州:101221701蚌埠:101220201杭州:101210101舟山:101211101湖州:101210201嘉兴:101210301金华:101210901绍兴:101210501台州:101210601温州:101210701丽水:101210801衢州:101211001宁波:101210401重庆:101040100合川:101040300南川:101040400江津:101040500万盛:101040600渝北:101040700北碚:101040800巴南:101040900长寿:101041000黔江:101041100万州天城:101041200万州龙宝:101041300涪陵:101041400开县:101041500城口:101041600云阳:101041700巫溪:101041800奉节:101041900巫山:101042000潼南:101042100垫江:101042200梁平:101042300忠县:101042400石柱:101042500大足:101042600荣昌:101042700铜梁:101042800璧山:101042900丰都:101043000武隆:101043100彭水:101043200綦江:101043300酉阳:101043400秀山:101043600沙坪坝:101043700永川:101040200福州:101230101泉州:101230501漳州:101230601龙岩:101230701晋江:101230509南平:101230901厦门:101230201宁德:101230301莆田:101230401三明:101230801兰州:101160101平凉:101160301庆阳:101160401武威:101160501金昌:101160601嘉峪关:101161401酒泉:101160801天水:101160901武都:101161001临夏:101161101合作:101161201白银:101161301定西:101160201张掖:101160701广州:101280101惠州:101280301梅州:101280401汕头:101280501深圳:101280601珠海:101280701佛山:101280800肇庆:101280901湛江:101281001江门:101281101河源:101281201清远:101281301云浮:101281401潮州:101281501东莞:101281601中山:101281701阳江:101281801揭阳:101281901茂名:101282001汕尾:101282101韶关:101280201南宁:101300101柳州:101300301来宾:101300401桂林:101300501梧州:101300601防城港:101301401贵港:101300801玉林:101300901百色:101301001钦州:101301101河池:101301201北海:101301301崇左:101300201贺州:101300701贵阳:101260101安顺:101260301都匀:101260401兴义:101260906铜仁:101260601毕节:101260701六盘水:101260801遵义:101260201凯里:101260501昆明:101290101红河:101290301文山:101290601玉溪:101290701楚雄:101290801普洱:101290901昭通:101291001临沧:101291101怒江:101291201香格里拉:101291301丽江:101291401德宏:101291501景洪:101291601大理:101290201曲靖:101290401保山:101290501呼和浩特:101080101乌海:101080301集宁:101080401通辽:101080501阿拉善左旗:101081201鄂尔多斯:101080701临河:101080801锡林浩特:101080901呼伦贝尔:101081000乌兰浩特:101081101包头:101080201赤峰:101080601南昌:101240101上饶:101240301抚州:101240401宜春:101240501鹰潭:101241101赣州:101240701景德镇:101240801萍乡:101240901新余:101241001九江:101240201吉安:101240601武汉:101200101黄冈:101200501荆州:101200801宜昌:101200901恩施:101201001十堰:101201101神农架:101201201随州:101201301荆门:101201401天门:101201501仙桃:101201601潜江:101201701襄樊:101200201鄂州:101200301孝感:101200401黄石:101200601咸宁:101200701成都:101270101自贡:101270301绵阳:101270401南充:101270501达州:101270601遂宁:101270701广安:101270801巴中:101270901泸州:101271001宜宾:101271101内江:101271201资阳:101271301乐山:101271401眉山:101271501凉山:101271601雅安:101271701甘孜:101271801阿坝:101271901德阳:101272001广元:101272101攀枝花:101270201银川:101170101中卫:101170501固原:101170401石嘴山:101170201吴忠:101170301西宁:101150101黄南:101150301海北:101150801果洛:101150501玉树:101150601海西:101150701海东:101150201海南:101150401济南:101120101潍坊:101120601临沂:101120901菏泽:101121001滨州:101121101东营:101121201威海:101121301枣庄:101121401日照:101121501莱芜:101121601聊城:101121701青岛:101120201淄博:101120301德州:101120401烟台:101120501济宁:101120701泰安:101120801西安:101110101延安:101110300榆林:101110401铜川:101111001商洛:101110601安康:101110701汉中:101110801宝鸡:101110901咸阳:101110200渭南:101110501太原:101100101临汾:101100701运城:101100801朔州:101100901忻州:101101001长治:101100501大同:101100201阳泉:101100301晋中:101100401晋城:101100601吕梁:101101100乌鲁木齐:101130101石河子:101130301昌吉:101130401吐鲁番:101130501库尔勒:101130601阿拉尔:101130701阿克苏:101130801喀什:101130901伊宁:101131001塔城:101131101哈密:101131201和田:101131301阿勒泰:101131401阿图什:101131501博乐:101131601克拉玛依:101130201拉萨:101140101山南:101140301阿里:101140701昌都:101140501那曲:101140601日喀则:101140201林芝:101140401台北县:101340101高雄:101340201台中:101340401海口:101310101三亚:101310201东方:101310202临高:101310203澄迈:101310204儋州:101310205昌江:101310206白沙:101310207琼中:101310208定安:101310209屯昌:101310210琼海:101310211文昌:101310212保亭:101310214万宁:101310215陵水:101310216西沙:101310217南沙岛:101310220乐东:101310221五指山:101310222琼山:101310102长沙:101250101株洲:101250301衡阳:101250401郴州:101250501常德:101250601益阳:101250700娄底:101250801邵阳:101250901岳阳:101251001张家界:101251101怀化:101251201黔阳:101251301永州:101251401吉首:101251501湘潭:101250201南京:101190101镇江:101190301苏州:101190401南通:101190501扬州:101190601宿迁:101191301徐州:101190801淮安:101190901连云港:101191001常州:101191101泰州:101191201无锡:101190201盐城:101190701哈尔滨:101050101牡丹江:101050301佳木斯:101050401绥化:101050501黑河:101050601双鸭山:101051301伊春:101050801大庆:101050901七台河:101051002鸡西:101051101鹤岗:101051201齐齐哈尔:101050201大兴安岭:101050701长春:101060101延吉:101060301四平:101060401白山:101060901白城:101060601辽源:101060701松原:101060801吉林:101060201通化:101060501沈阳:101070101鞍山:101070301抚顺:101070401本溪:101070501丹东:101070601葫芦岛:101071401营口:101070801阜新:101070901辽阳:101071001铁岭:101071101朝阳:101071201盘锦:101071301大连:101070201锦州:101070701");
		ZSingleCaptureDlg *cdlg = new ZSingleCaptureDlg(QString::fromUtf8("请输入城市名或者城市编码"), QString::fromUtf8("比如：北京 或 101010100\n设置的城市为当前桌面显示城市"),ZSingleCaptureDlg::TypeLineEdit,NULL,"A", true, 0, 0);
		if(cdlg->exec())
		newcity = cdlg->getResultText();
		delete cdlg;
		if(newcity.startsWith("10"))
		{
			cityid = city;
			ZConfig *newcityconf = new ZConfig(SETUPPATH);
			newcityconf->writeEntry("SETUP", "cityid", cityid);
			newcityconf->flush();
			delete newcityconf;
			loadInfoConfig();
			creatUi();
		}
		else
		{
			int pos = citys.find(newcity);
			if(pos!=-1)
			{
				int pos1 = citys.find(':', pos);
				cityid = citys.mid(pos1+1, 9);
				ZConfig *newcityconf = new ZConfig(SETUPPATH);
				newcityconf->writeEntry("SETUP", "cityid", cityid);
				newcityconf->flush();
				delete newcityconf;
				loadInfoConfig();
				creatUi();
			}
			else
			{
			ZMessageDlg *mdlg = new ZMessageDlg(QString::fromUtf8("错误"),QString::fromUtf8("未查到相应的城市代码\n请登陆m.weather.com.cn\n在搜索栏中输入自己的城市\n得到的网址的后面一堆数字即为城市代码"),ZMessageDlg::TypeOK);
			if(mdlg->exec())
			delete mdlg;
			}
		}
		}
		else
		{
			QStringList clist;
			ZConfig conf(INFOPATH);
			for(QStringList::Iterator it= citylist.begin(); it!=citylist.end(); ++it)
			clist += conf.readEntry(*it, "city");
			ZSingleSelectDlg *dlg2 = new ZSingleSelectDlg(QString::fromUtf8("请选择要删除的城市"), NULL);
			dlg2->addItemsList(clist);
			if(dlg2->exec()==ZPopup::Accepted)
			{
				int i = dlg2->getCheckedItemIndex();
				conf.clearGroup(citylist[i]);
				conf.flush();
				loadInfoConfig();
			}
			delete dlg2;
		}
		delete dlg;
	}
	}
	else if(i==1)
	{
		QDir dir(getAppDir()+"skins/");
		QStringList slist = dir.entryList(QDir::Dirs);
		slist.remove(".");
		slist.remove("..");
		ZSingleSelectDlg *sdlg = new ZSingleSelectDlg(QString::fromUtf8("选择主题"),NULL);
		sdlg->addItemsList(slist);
		if(sdlg->exec()==ZPopup::Accepted)
		{
			int j = sdlg->getCheckedItemIndex();
			QString s = slist[j];
			if(s!=skin)
			{
				ZConfig conf(SETUPPATH);
				conf.writeEntry("SETUP", "skin", s);
				conf.flush();
				skin = s;
				loadSkinConfig();
				creatUi();
			}
		}	
		delete sdlg;
	}
	else if(i==2)
	{
		QStringList list = QString::fromUtf8("天气显示");
		list += QString::fromUtf8("日程提醒");
		ZSingleSelectDlg *sdlg = new ZSingleSelectDlg(QString::fromUtf8("请选择"),QString::fromUtf8("设置是否在桌面显示下列菜单"));
		sdlg->addItemsList(list);
		if(sdlg->exec()==ZPopup::Accepted)
		{
			int i = sdlg->getCheckedItemIndex();
			if(i==0)
			{
				ZConfig conf(SETUPPATH);
				bool showweather = conf.readBoolEntry("SETUP", "showweather");
				if(showweather)
				{
					ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("显示天气"), QString::fromUtf8("桌面显示天气已经开启是否关闭？"), ZMessageDlg::TypeChoose);
					if(dlg->exec()==ZPopup::Accepted)
					{
						conf.writeEntry("SETUP", "showweather", false);
						conf.flush();
					}
					delete dlg;
				}
				else
				{
					ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("显示天气"), QString::fromUtf8("桌面显示天气未开启是否开启？"), ZMessageDlg::TypeChoose);
					if(dlg->exec()==ZPopup::Accepted)
					{
						conf.writeEntry("SETUP", "showweather", true);
						conf.flush();
					}
					delete dlg;
				}
				emit freshWallpaper();
			}
			else
			{
				ZConfig conf(SETUPPATH);
				bool showwpalarm = conf.readBoolEntry("SETUP", "showwpalarm");
				if(showwpalarm)
				{
					ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("日程提醒"), QString::fromUtf8("桌面显示日程提醒已经开启是否关闭？"), ZMessageDlg::TypeChoose);
					if(dlg->exec()==ZPopup::Accepted)
					{
						conf.writeEntry("SETUP", "showwpalarm", false);
						conf.flush();
					}
					delete dlg;
				}
				else
				{
					ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("日程提醒"), QString::fromUtf8("桌面显示日程提醒未开启是否开启？"), ZMessageDlg::TypeChoose);
					if(dlg->exec()==ZPopup::Accepted)
					{
						conf.writeEntry("SETUP", "showwpalarm", true);
						conf.flush();
					}
					delete dlg;
				}
				emit freshWallpaper();
				
			}
		}
	}
	else if(i==3)
	{
		QStringList list = QString::fromUtf8("天气显示坐标");
		list += QString::fromUtf8("日程提醒坐标");
		ZSingleSelectDlg *sdlg = new ZSingleSelectDlg(QString::fromUtf8("请选择"),QString::fromUtf8("方向键移动面板的位置\n左软键确定 右软键取消"));
		sdlg->addItemsList(list);
		if(sdlg->exec()==ZPopup::Accepted)
		{
			int i = sdlg->getCheckedItemIndex();
			if(i==0)
			{
				pix_wppanel.readPixmaps(getAppDir()+"skins/"+skin+"/wp/wpweather.png");
				qs_wppanel = new QCanvasSprite(&pix_wppanel, &canvas);
				ZConfig conf(SETUPPATH);
				qs_wppanel->move(conf.readUIntEntry("WP", "panel_x"),conf.readUIntEntry("WP", "panel_y"));
				qs_wppanel->setZ(100);
				qs_wppanel->show();
				panel = 1;
				showwp = true;
			}
			else
			{
				pix_wppanel.readPixmaps(getAppDir()+"skins/"+skin+"/wp/wpalarm.png");
				qs_wppanel = new QCanvasSprite(&pix_wppanel, &canvas);
				ZConfig conf(SETUPPATH);
				qs_wppanel->move(conf.readUIntEntry("WP", "alarmpanel_x"),conf.readUIntEntry("WP", "alarmpanel_y"));
				qs_wppanel->setZ(100);
				qs_wppanel->show();
				panel = 2;
				showwp = true;
			}
		}
	}
	else if(i==4)
	{
		ZSingleCaptureDlg *cdlg = new ZSingleCaptureDlg(QString::fromUtf8("请输入日程提醒"), QString::fromUtf8("日程提醒将显示在桌面"),ZSingleCaptureDlg::TypeLineEdit,NULL,"A", true, 0, 0);
		if(cdlg->exec())
		{
		QString alarmtext = cdlg->getResultText();
		ZConfig conf(SETUPPATH);
		conf.writeEntry("WP", "text", alarmtext);
		conf.flush();
		}
		emit freshWallpaper();
	}
	else if(i==5)
	{
		ZMessageDlg *mdlg = new ZMessageDlg(QString::fromUtf8("关于"),QString::fromUtf8("天气秀1.0\n 作者:slbear\n感谢蜜蜂和jaydd的测试和主题\n侧键刷新 左软键呼出设置菜单\n上下键切换已浏览的城市"),ZMessageDlg::TypeOK);
		if(mdlg->exec())
		delete mdlg;
	}
	else if(i==6)
	{
		ZConfig *sysreg = new ZConfig("/ezxlocal/download/appwrite/am/InstalledDB",true);
		QUuid daemonID(0xd30fb72b,0xd284,0x4ca0,0x8b,0x00,0xe5,0xee,0x2f,0x3b,0xb7,0xf1);
		bool autorun = false;
		AM_AppRegistry *regtmp3 = new AM_AppRegistry(NULL);
		regtmp3->init();
		regtmp3->isAutoStartEnabled(daemonID,autorun);
		delete regtmp3;
		if(autorun)
		{
			ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("桌面显示开机自启动"), QString::fromUtf8("自启动已经启用，是否关闭自启动？"),ZMessageDlg::TypeChoose);
			if(dlg->exec()==ZPopup::Accepted)
			{
				AM_AppRegistry *regtmp2 = new AM_AppRegistry(NULL);
				regtmp2->init();
				regtmp2->setAutoStartEnabled(daemonID,false);
				ZMessageDlg *mdlg = new ZMessageDlg(QString::fromUtf8("桌面显示开机自启动"), QString::fromUtf8("自启动已关闭"),ZMessageDlg::TypeOK);
				if(mdlg->exec())
				delete mdlg;
			}
			delete dlg;
		
		}
		else
		{
			ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("桌面显示开机自启动"), QString::fromUtf8("自启动未启用，是否开始自启动？"),ZMessageDlg::TypeChoose);
			if(dlg->exec()==ZPopup::Accepted)
			{
				QString qsID = daemonID.toString();
				QString tmp = qsID;
				qsID.remove(0,1);
				qsID.remove(36,37);
				sysreg->writeEntry(qsID,"AniIcon","");
				sysreg->writeEntry(qsID,"AppID",tmp);
				sysreg->writeEntry(qsID,"AppType",0);
				sysreg->writeEntry(qsID,"Args","");
				sysreg->writeEntry(qsID,"Attribute",2);
				sysreg->writeEntry(qsID,"BigIcon","");
				sysreg->writeEntry(qsID,"Daemon",0);
				sysreg->writeEntry(qsID,"Directory",getAppDir());
				sysreg->writeEntry(qsID,"ExecId","weatherwp");
				sysreg->writeEntry(qsID,"GroupID","root");
				sysreg->writeEntry(qsID,"Icon","");
				sysreg->writeEntry(qsID,"LockEnabled",1);
				sysreg->writeEntry(qsID,"Name","weathershow");
				sysreg->writeEntry(qsID,"NameResourceId","");
				sysreg->writeEntry(qsID,"ObjectType",2);
				sysreg->writeEntry(qsID,"SVGIcon","");
				sysreg->writeEntry(qsID,"SimpleIcon","");
				sysreg->writeEntry(qsID,"UserID","root");
				AM_AppRegistry *regtmp2 = new AM_AppRegistry(NULL);
				regtmp2->init();
				regtmp2->setAutoStartEnabled(daemonID,true);
				delete regtmp2;
				ZMessageDlg *mdlg = new ZMessageDlg(QString::fromUtf8("桌面显示开机自启动"), QString::fromUtf8("已开启自启动"),ZMessageDlg::TypeOK);
				if(mdlg->exec())
				delete mdlg;
			}
		delete dlg;	
		}
	
		delete sysreg;
	}
}

void MainGui::slotFreshWallpaper()
{
	ZMessageDlg *dlg = new ZMessageDlg(QString::fromUtf8("刷新桌面"), QString::fromUtf8("是否刷新桌面？"),ZMessageDlg::TypeChoose);
	if(dlg->exec()==ZPopup::Accepted)
	{
		ZNoticeDlg *ndlg = new ZNoticeDlg(ZNoticeDlg::Information, "", QString::fromUtf8("刷新中，请等待..."));
		ndlg->setAutoDismissTime(5000);
		ndlg->exec();
		sleep(2);
		system(getAppDir()+"weatherwp");
	}
	delete dlg;
}




