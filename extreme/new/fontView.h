
#ifndef FONTVIEW_H
#define FONTVIEW_H

#include <ZApplication.h>
#include <ZFormContainer.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>

#include <qfontmanager_qws.h>
#include <qfontdatabase.h>
#include <qfontfactoryttf_qws.h>

#include "BaseDlg.h"
#include "lng.h"
#include "myDef.h"
#include "UtilsTools.h"


class fontView: public MyBaseDlg 
{
    Q_OBJECT

public :	
	fontView( QString _fontPath );
	~fontView();
	
	void buildDlg();
	
protected:
	bool  eventFilter( QObject *, QEvent * );  
//protected:
//	QString size2string(unsigned long size);
	
public slots:
	void fontTest();
	void fontBind();
	//#ifdef REPLACE_FONT
	//void fontReplace();
	//#else
	void fontFlash();

	//#endif
	void about();
	void slotUsage();

private:
	QFont fOrg;
	QFont fNew;
	
	ZFormContainer *form;
	ZSoftKey *softKey;
	ZOptionsMenu *menu;
	Lng *lng;
	
	QString fontPath;
	QString fontName;
	QString appDir;
	int mFontSize;
	
	//int showQ(const QString &title, const QString &text, int type = 0);
	//void showNotify(const QString &title, const QString &text, int type = 0, int time = 1);
	//QString ctr(const char*ChineseString);

};
#endif //fontView_H


