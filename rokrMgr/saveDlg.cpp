
#include <qdir.h>

#include "saveDlg.h"
#include "lng.h"
#include "myDef.h"

extern Lng *lng;

saveDlg :: saveDlg(QString title, QString name) : ZPopup()
{
//	lng = new Lng();
	#ifndef ZN5
	oldMode = getMorphMode();
	setMorphMode(3);
	#endif
	CardExist = false;
	checkedIndex = -1;	
	QDir dir;
	//if ( dir.exists( QString(SD_MPKGBOX) ) )
	//	CardExist = true;	
		
	if( !dir.exists( QString(SKIN_FILE) ) )
		dir.mkdir( QString(SKIN_FILE) );
	//if( !dir.exists( QString(PH_MGX_FILE) ) )	
	//	dir.mkdir( QString(PH_MGX_FILE) );
		
	//ZConfig cfg(MGX_OBJ_PATH);
   // QString path = cfg.readEntry( gname, "Directory", "");	
	//QString oldName = cfg.readEntry( gname, "Name", "");	
		
	//this->enableAia(true);
	this->setTitle(title);
	this->setInstructText(name);
	this->setTitleIcon("action_required_pop.bmp");

	editGroupBox = new ZGroupBox(lng->tr("FT_SAVENAME"), this);

	lineEdit = new ZLineEdit(name, editGroupBox, 0, (ZSkinService::WidgetClsID)39);
	lineEdit->selectAll();
	lineEdit->resize(300, 40);

	this->insertChild(editGroupBox);

	pathGroupBox = new ZGroupBox(lng->tr("FT_SAVEPATH"), this);

	pathBox = new ZComboBox(pathGroupBox);
	pathBox->insertItem(lng->tr("FT_PHONE"), 0);
	if (CardExist) pathBox->insertItem(lng->tr("FT_MMCA1"), 1);
	pathBox->resize(300, 40);

	this->insertChild(pathGroupBox);

	ZSoftKey *softKey = this->getSoftKey();
	softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OK", "Ok"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
	softKey->setClickedSlot(ZSoftKey::LEFT, this, SLOT(ok()));
	softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT(cancel()));
}

saveDlg::~saveDlg()
{
	#ifndef ZN5
	setMorphMode(oldMode);
	#endif
//	delete lng;
//	lng = NULL;
}
void saveDlg::ok()
{
	checkedIndex = pathBox->currentItem();
	newName = lineEdit->text();
	newName = newName.simplifyWhiteSpace();
	if (newName == "") checkedIndex=-1;
 	reject();
}
void saveDlg::cancel()
{
	checkedIndex=-1;
	newName="";
	reject();
}

