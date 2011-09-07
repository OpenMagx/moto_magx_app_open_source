#ifndef SHOWPIC_H
#define SHOWPIC_H

#include <ZApplication.h>
#include <ZKbMainWidget.h>
#include <ZSoftKey.h>
#include <qpixmap.h>
#include <qstring.h>


#include "BaseDlg.h"
#include "myDef.h"

class showPic : public MyBaseDlg 
{
	Q_OBJECT
	
public :
	showPic(QString &fileName);
	~showPic() {};

private slots:
	void paintEvent( QPaintEvent *);
	void slotQuit();
	void keyPressEvent(QKeyEvent* k);
private:
	QString mFileName;
	QImage img_bg;
	ZSoftKey *softKey;
	
};
#endif // font_View


