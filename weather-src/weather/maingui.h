/**********************************************************************************************************************************
weathershow for E8 EM30
version : 1.0   2010.3.10
Auther  : slbear <25828761@qq.com>
***********************************************************************************************************************************/
#ifndef _MAINGUI_H_
#define _MAINGUI_H_
#include <ZKbMainWidget.h>
#include <qpixmap.h>
#include <qcanvas.h>
#include <qpoint.h>
#include <qtimer.h>
#include "getdata.h"

class MainGui: public ZKbMainWidget
{
Q_OBJECT
signals:
	void freshWallpaper();
public:
	MainGui(QWidget* parent = 0, const char* name = 0, WFlags f = 0);
	~MainGui();
	void keyPressEvent(QKeyEvent *e);
private:
	QCanvas* canvas() const
	{ return cnv; } //QCanvas canvas;
	QCanvasView *cv;
	QPixmap pix_background;
	QCanvasPixmapArray pix_bottom;
	QPoint p_bottom;
	QCanvasPixmapArray pix_center1;
	QPoint p_center1;
	QCanvasPixmapArray pix_center2;
	QPoint p_center2;
	
	QCanvasPixmapArray pix_left;
	QCanvasPixmapArray pix_right;
	QPoint p_left;
	QPoint p_right;
	
	QCanvasPixmapArray pix_bweather;
	QCanvasPixmapArray pix_sweather;
	QCanvasPixmapArray pix_refresh;
	QCanvasPixmapArray pix_setup;
	QCanvasPixmapArray pix_wppanel;
	//QCanvasPixmapArray pix_wpalarm;
	
	QPoint p_icon1;
	QPoint p_icon2;
	QPoint p_icon3;
	QPoint p_icon4;
	
	QPoint p_city;
	QPoint p_temp1;
	QPoint p_weather1;
	QPoint p_time1;
	QPoint p_wind1;
	QPoint p_uv;
	
	QPoint p_time2;
	QPoint p_time3;
	QPoint p_time4;
	
	QPoint p_weather2;
	QPoint p_weather3;
	QPoint p_weather4;
	
	QString city;
	QString wind1;
	QString uv;
	QString weather1;
	QString weather2;
	QString weather3;
	QString weather4;
	QString time1;
	QString temp1;
	QString temp2;
	QString temp3;
	QString temp4;
	int img1;
	int img2;
	int img3;
	int img4;
	//QCanvasSprite* qs_none;
	QCanvasSprite* qs_bottom;
	QCanvasSprite* qs_center1;
	QCanvasSprite* qs_center2;
	QCanvasSprite* qs_left;
	QCanvasSprite* qs_right;
	QCanvasSprite* qs_refresh;
	QCanvasSprite* qs_setup;
	
	QCanvasSprite* qs_icon1;
	QCanvasSprite* qs_icon2;
	QCanvasSprite* qs_icon3;
	QCanvasSprite* qs_icon4;
	QCanvasSprite* qs_wppanel;
	
	
	QCanvasText* qt_city;
	QCanvasText* qt_temp1;
	QCanvasText* qt_weather1;
	QCanvasText* qt_time1;
	QCanvasText* qt_wind1;
	QCanvasText* qt_uv;
	
	QCanvasText* qt_temp2;
	QCanvasText* qt_weather2;
	QCanvasText* qt_temp3;
	QCanvasText* qt_weather3;
	QCanvasText* qt_temp4;
	QCanvasText* qt_weather4;
	QCanvasText* qt_error;
	
	
	int size_city;
	QColor co_city;
	int size_weather1;
	QColor co_weather1;
	QTimer* timer;
	int size_temp1;
	int size_panel1;
	QColor co_temp1;
	QColor co_panel1;
	int size_panel2;
	QColor co_panel2;
	int curpage;  //-1 0 1
	GetData *data;
	QString cityid;
	QTimer* freshtimer;
	int freshframe;
	bool freshing;
	bool showsetup;
	bool showwp;
	QString skin;
	QStringList citylist;
	int panel;
	
private:
	void loadSkinConfig();
	void loadInfoConfig();
	void creatUi();
	void refresh();
	void slotSetup();
private slots:
	void stopMove();
	void sTime();
	void freshicon();
	void slotTimeOut();
	void slotHideErrinfo();
	void slotFreshWallpaper();
public slots:
	void slotFresh();
	void slotDataError(int);
};
#endif
