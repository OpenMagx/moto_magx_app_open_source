#include <ZApplication.h>
#include <ZConfig.h>
#include <ZSeparator.h>
#include <ZSoftKey.h>
#include <ZLabel.h>
#include <ZListBoxItem.h>
#include <ZSingleCaptureDlg.h>

#include <qfile.h>

#include <iostream>

#include "ThemeSettingView.h"
#include "mediaBrowser.h"
#include "lng.h"

using namespace std;

extern Lng *lng;

ThemeSettingView::ThemeSettingView( QString themeChmFile):MyBaseDlg()
{
	mChmName = themeChmFile;
	listBox = NULL;
	
	//lng = new Lng();
	loadCfg();
	
	this->setMainWidgetTitle("Theme Setting");

	form = new ZFormContainer(this, 0, ZSkinService::clsZFormContainer);
	this->setContentWidget(form);	
	
	creatWindow();
	creatSoftKey();

	connect(listBox, SIGNAL( selected ( int ) ), this, SLOT( slotItemClicked(int) ) );	
	
}

ThemeSettingView::~ThemeSettingView()
{
}

void ThemeSettingView::creatWindow()
{
	cout<<"creat window "<<endl;
	
	creatNameArea();
	creatListBoxArea();	
}
void ThemeSettingView::creatSoftKey()
{
	cout<<"creat softkey "<<endl;
	
	softKey = new ZSoftKey("CST_2A", this, this);
	this->setSoftKey(softKey);
	softKey->setText(ZSoftKey::LEFT,  lng->tr("FT_SAVE"));
    softKey->setText(ZSoftKey::RIGHT, lng->tr("FT_BACK"));
	softKey->setClickedSlot(ZSoftKey::LEFT, this ,SLOT(  slotSave() ));
	softKey->setClickedSlot(ZSoftKey::RIGHT, this ,SLOT( slotQuit() ));
}
void ThemeSettingView::slotItemClicked(int index)
{
    printf("===== itme cliked %d\n =====", index);
	if(index == 0 || index == 1 || index == 2)
	{
		MediaBrowser *mbr = new MediaBrowser(MediaBrowser::TYPE_AUDIO);
		mbr->exec();
		if ( !mbr->isCancel ) {
			switch (index ) {
				case 0 :
					mNewRing = mbr->getSelectedFile();
					break;
				case 1 :
					mNewMsg = mbr->getSelectedFile();
					break;
				case 2 :
					mNewAlarm = mbr->getSelectedFile();
					break;
				default :
					break;			
			}
			delete mbr;
			mbr = NULL;	
		} else {
			delete mbr;
			mbr = NULL;		
		}	
	}
    if( index == 3 || index == 4 || index == 5 || index == 6) { //wall
		MediaBrowser *mbr = new MediaBrowser(MediaBrowser::TYPE_IMG);
		mbr->exec();
		if ( !mbr->isCancel ) {
			switch (index ) {
				case 3 :
					mNewWall = mbr->getSelectedFile();
					break;
				case 4 :
					mNewScreen = mbr->getSelectedFile();
					break;
				case 5 :
					mNewPowerOn = mbr->getSelectedFile();
					break;
				case 6:
					mNewPowerOff = mbr->getSelectedFile();
					break;
				default :
					break;			
			}
			delete mbr;
			mbr = NULL;	
		} else {
			delete mbr;
			mbr = NULL;		
		}		
	}
	
	flushWindow();	
}

void ThemeSettingView::slotSave()
{
	ZConfig cfg(mChmName);
	//mNewThemeName = lineEdit->text();
	cfg.writeEntry("THEME_CONFIG_TABLE", "ThemeName", mNewThemeName);
	cfg.writeEntry("THEME_CONFIG_TABLE", "CallAlertLine1", mNewRing);
	cfg.writeEntry("THEME_CONFIG_TABLE", "MsgAlert", mNewMsg);
	cfg.writeEntry("THEME_CONFIG_TABLE", "CalendarAlarm", mNewAlarm);
	cfg.writeEntry("THEME_CONFIG_TABLE", "WallPaper", mNewWall);
	cfg.writeEntry("THEME_CONFIG_TABLE", "ScreenSaver", mNewScreen);
	cfg.writeEntry("THEME_CONFIG_TABLE", "PowerOnScreen", mNewPowerOn);
	cfg.writeEntry("THEME_CONFIG_TABLE", "PowerOffScreen", mNewPowerOff);
	cfg.flush();
	MyBaseDlg::reject();
}
void ThemeSettingView::slotQuit()
{
	MyBaseDlg::reject();
}
void ThemeSettingView::flushWindow()
{
	listBox->clear();
	//form->removeChild(label);
	//form->removeChild(lineEdit);
	//form->removeChild(listBox);
	//creatWindow();
	//listBox->setFocus();
	creatListBoxArea();
	//form->setFocus();
	
}
void ThemeSettingView::creatNameArea()
{
	label = new ZLabel(lng->tr("FT_THEMENAME"), form, "ZLabel" , 0, (ZSkinService::WidgetClsID)4);
	label->setAutoResize(true);
	form->addChild(label);
	
	/*lineEdit = new ZLineEdit(form);	
	lineEdit->setTitlePosition(ZLineEdit::TitleLeft);
	lineEdit->setText(mNewThemeName);*/
	nameButton = new ZPressButton(mNewThemeName, form);
	form->addChild(nameButton);
	
	connect(nameButton, SIGNAL(clicked()), this, SLOT(slotNameBtChanged()));
}
void ThemeSettingView::slotNameBtChanged()
{
	QString title = lng->tr("FT_SET_THEME");
	QString text = QString("%1 : %2").arg(lng->tr("FT_THEMENAME")).arg(mNewThemeName);
	
	ZSingleCaptureDlg *dlg = new ZSingleCaptureDlg(title, text,
	    (ZSingleCaptureDlg::CaptureDlgType)0, NULL, "ZSingleCaptureDlg", true, 0, 0);	
		
	if( dlg->exec() == ZPopup::Accepted )  {
		mNewThemeName = dlg->getResultText().stripWhiteSpace();
		delete dlg;
		dlg = NULL;	
		
		nameButton->setText(mNewThemeName);
	} else {
		delete dlg;
		dlg = NULL;		
	}		
}
void ThemeSettingView::creatListBoxArea()
{
	if( listBox == NULL ) {
		listBox = new ZListBox("%I%M",this);
		listBox->enableMarquee(ZListBox::LISTITEM_REGION_A, true);
		listBox->enableMarquee(ZListBox::LISTITEM_REGION_B, true);	
		//this->insertChild(listBox);
		//this->setContentWidget(listBox);
		form->addChild(listBox);
	}
    ZListBoxItem *listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_RING"));
	listBoxItem->appendSubItem(1, extractName( mNewRing ));	
	listBox->insertItem(listBoxItem);	
	
	listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_MSG"));
	listBoxItem->appendSubItem(1, extractName( mNewMsg ));	
	listBox->insertItem(listBoxItem);	
	
	listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_ALARM"));
	listBoxItem->appendSubItem(1, extractName( mNewAlarm ));	
	listBox->insertItem(listBoxItem);	

	QFile file;
	
	listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_WALL"));
	if( file.exists(mNewWall) ) {	
		pm.load(mNewWall);
		QImage img = pm.convertToImage();
		img = img.smoothScale(48, 48);
		pm.convertFromImage(img);
		listBoxItem->setPixmap(0, pm);
		listBoxItem->appendSubItem(1, extractName( mNewWall ));
	}
	else {
		listBoxItem->appendSubItem(1, lng->tr("FT_NULL") );
	}	
	listBox->insertItem(listBoxItem);	
	
	listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_SCREENSAVE"));
	if( file.exists(mNewScreen) ) {	
		pm.load(mNewScreen);
		QImage img = pm.convertToImage();
		img = img.smoothScale(48, 48);
		pm.convertFromImage(img);
		listBoxItem->setPixmap(0, pm);
		listBoxItem->appendSubItem(1, extractName( mNewScreen ));
	}
	else {
		listBoxItem->appendSubItem(1, lng->tr("FT_NULL") );
	}	
	listBox->insertItem(listBoxItem);		
	
	listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_POWERON"));
	if( file.exists(mNewPowerOn) ) {	
		pm.load(mNewPowerOn);
		QImage img = pm.convertToImage();
		img = img.smoothScale(48, 48);
		pm.convertFromImage(img);
		listBoxItem->setPixmap(0, pm);
		listBoxItem->appendSubItem(1, extractName( mNewPowerOn ));
	}
	else {
		listBoxItem->appendSubItem(1, lng->tr("FT_NULL") );
	}	
	listBox->insertItem(listBoxItem);

	listBoxItem = new ZListBoxItem(listBox);
	listBoxItem->appendSubItem(1, lng->tr("FT_POWEROFF"));
	if( file.exists(mNewPowerOff) ) {	
		pm.load(mNewPowerOff);
		QImage img = pm.convertToImage();
		img = img.smoothScale(48, 48);
		pm.convertFromImage(img);
		listBoxItem->setPixmap(0, pm);
		listBoxItem->appendSubItem(1, extractName( mNewPowerOff ));
	}
	else {
		listBoxItem->appendSubItem(1, lng->tr("FT_NULL") );
	}	
	listBox->insertItem(listBoxItem);
}
void ThemeSettingView::loadCfg()
{
	ZConfig cfg(mChmName);
	mOrgThemeName = cfg.readEntry("THEME_CONFIG_TABLE", "ThemeName", "NULL");
	mNewThemeName = mOrgThemeName;
	mOrgRing = cfg.readEntry("THEME_CONFIG_TABLE", "CallAlertLine1", "NULL");
	mNewRing = mOrgRing;
	mOrgMsg = cfg.readEntry("THEME_CONFIG_TABLE", "MsgAlert", "NULL");
	mNewMsg = mOrgMsg;
	mOrgAlarm = cfg.readEntry("THEME_CONFIG_TABLE", "CalendarAlarm", "NULL");
	mNewAlarm = mOrgAlarm;
	mOrgWall = cfg.readEntry("THEME_CONFIG_TABLE", "WallPaper", "NULL");
	mNewWall = mOrgWall;
	mOrgScreen = cfg.readEntry("THEME_CONFIG_TABLE", "ScreenSaver", "NULL");
	mNewScreen = mOrgScreen;
	mOrgPowerOn = cfg.readEntry("THEME_CONFIG_TABLE", "PowerOnScreen", "NULL");
	mNewPowerOn = mOrgPowerOn;
	mOrgPowerOff = cfg.readEntry("THEME_CONFIG_TABLE", "PowerOffScreen", "NULL");
	mNewPowerOff = mOrgPowerOff;

}
QString ThemeSettingView::extractName(QString name)
{
    int i = name.findRev("/");
    name.remove(0, i+1);
	//cout<<name<<endl;
    return name;
}


/*int main(int argc, char *argv[])
{
	ZApplication app(argc, argv);
	
	ThemeSettingView *v = new ThemeSettingView( QString("/ezxlocal/download/appwrite/setuptheme/NEXUS.chm") );
	v->exec();
	delete v;
	return 0;

}
*/


