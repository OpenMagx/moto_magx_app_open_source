#ifndef ICONSET_H
#define ICONSET_H

#include <ZPopup.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <RES_ICON_Reader.h>
#include <ZKbMainWidget.h>

#include <ZApplication.h>
#include <ZFormContainer.h>
#include <ZScrollPanel.h>
#include <ZScrollView.h>
#include <ZSoftKey.h>
#include <ZLabel.h>
#include <ZListBox.h>
#include <ZOptionsMenu.h>
#include <ZIconView.h>

#include "BaseDlg.h"
#include "UtilsTools.h"
#include "lng.h"

#define DATA_FILE "iconData.list"
#define KEY_LEFT              0x1012
#define KEY_RIGHT             0x1014
#define KEY_CENTER            0x1004

class iconSet : public MyBaseDlg
{	
	Q_OBJECT

public:
	iconSet();//QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
	~iconSet();
	
	QString getIconItemName();
	
	void creatWindow();
	void creatSoftKey();

	void showIconList(const QStringList &iconDataList);
	
private slots:
	void creatData1();
	void creatData2();
	void creatData3();
	void creatData4();
	void creatData5();
	
	void slotQuit();
	void slotAbout();
	
	void slotClicked();
	
protected:
	bool eventFilter( QObject *, QEvent * );	
	
private:
	ZIconView *iconView;
	ZOptionsMenu *menu;
	RES_ICON_Reader iconReader;
	
	QString m_appDir;
	QString m_iconItemName;

	//Lng *lng;
};
#endif // folderList



