#ifndef SAVEDLG_H
#define SAVEDLG_H


#include <ZPopup.h>
#include <ZLineEdit.h>
#include <ZGroupBox.h>
#include <ZComboBox.h>
#include <ZSoftKey.h>

#include <qstring.h>
#include <qstringlist.h>
#include "lng.h"

class saveDlg : public ZPopup
{
	Q_OBJECT
public:
	saveDlg(QString title = QString::null, QString name = QString::null );
	~saveDlg();
	int checkedIndex; // -1->reject, 0->phone, 1->sd card
	QString newName; 
	
private:
	#ifndef ZN5
	int oldMode;
	#endif
	bool CardExist;
	ZGroupBox *editGroupBox;
	ZLineEdit *lineEdit;
	ZGroupBox *pathGroupBox;
	ZComboBox *pathBox;
	//Lng *lng;

private slots:
	void ok();
	void cancel();
};
#endif

