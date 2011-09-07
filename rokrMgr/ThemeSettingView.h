#ifndef THEMESETTINGVIEW_H
#define THEMESETTINGVIEW_H

#include <ZFormContainer.h>
#include <ZNavTabWidget.h>
#include <ZLineEdit.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZLabel.h>
#include <ZPressButton.h>

#include <qpixmap.h>

//#include "lng.h"
#include "BaseDlg.h"

class ThemeSettingView : public MyBaseDlg 
{
    Q_OBJECT

public :
	ThemeSettingView( QString themeChmFile);
	~ThemeSettingView();
	void creatWindow();
	void creatSoftKey();
	
protected :
	void loadCfg();
	QString extractName(QString name);
	
private slots:
	void slotSave();
	void slotQuit();
	void slotItemClicked(int index);
	void flushWindow();
	void slotNameBtChanged();
	
private :
	void creatNameArea();
	void creatListBoxArea();
	//Lng *lng;
	ZFormContainer *form;	
	ZLabel *label;
	//ZLineEdit *lineEdit;	
	ZListBox *listBox;
	ZSoftKey *softKey;
	ZPressButton *nameButton;
	
	QPixmap pm;
	
	QString mChmName;
	QString mOrgThemeName;
	QString mNewThemeName;
	QString mOrgRing;
	QString mNewRing;
	QString mOrgMsg;
	QString mNewMsg;
	QString mOrgAlarm;
	QString mNewAlarm;
	QString mOrgWall;
	QString mNewWall;
	QString mOrgScreen;
	QString mNewScreen;
	QString mOrgPowerOn;
	QString mNewPowerOn;
	QString mOrgPowerOff;
	QString mNewPowerOff;


};

#endif


