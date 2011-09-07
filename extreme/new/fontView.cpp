
#include <ZSeparator.h>
#include <ZLabel.h>
#include <ZOptionsMenu.h>
#include <ZSingleSelectDlg.h>
#include <ZNoticeDlg.h>
#include <ZMessageDlg.h>
#include <ZMultiLineEdit.h>

#include <qstringlist.h>
#include <qtextcodec.h>
#include <qfileinfo.h>

#include <iostream>

#include "fontView.h"
#include "deathDlg.h"


fontView::fontView(QString _fontPath):MyBaseDlg()
{
	
	this->installEventFilter( this );
	
	fontPath = _fontPath;

	appDir = getAppDir(); 
	
	#ifdef ZN5
	fOrg = qApp->font();
	#endif	
	
	fontName = QFileInfo(_fontPath).baseName();
	
	QFontFactory *factory = qt_fontmanager->factories.at(0);	
	QDiskFont *qdf = new QDiskFont(factory, fontName , false, 25, 0, "s", fontPath);
	qt_fontmanager->diskfonts.append(qdf);
	QFontDatabase::qwsAddDiskFont(qdf);
	
	#ifndef ZN5
	fOrg = QFont::defaultFont();
	#endif
	fNew = fOrg;
	fNew.setFamily( fontName );
	QFont::setDefaultFont( fNew ); 
	
	lng = new Lng();
	
	setMainWidgetTitle(lng->tr("Rokr Font"));

	QRect rect=ZGlobal::getContentR();
	
	form = new ZFormContainer(this, 0, ZSkinService::clsZFormContainer);
	form->setVScrollBarMode(ZScrollPanel::AlwaysOff);
	form->setHScrollBarMode(ZScrollPanel::AlwaysOff);	
	this->setContentWidget(form);
	
	
	
	softKey = new ZSoftKey("CST_2A", this, this);
	this->setSoftKey(softKey);
    softKey->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"),
	                               tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
	softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK", "Back"));	
	
	ZOptionsMenu *menu = new ZOptionsMenu(rect, this, 0, 0);//, (ZSkinService::WidgetClsID)55);
	menu->insertItem(lng->tr("FT_TEST_FONT"), NULL, this, SLOT( fontTest() ), true, false, false, 0, 0);	
	menu->insertItem(lng->tr("FT_MOUNT_FONT"), NULL, this, SLOT( fontBind() ), true, false, false, 1, 1 );	
	
	#ifdef FONT_WRITABLE
		#ifdef VE66
		menu->insertItem(lng->tr("FT_REPLACE_FONT"), NULL, this, SLOT( fontFlash() ), true, false, false, 2, 2 );
		#else
		menu->insertItem(lng->tr("FT_FLASH_FONT"), NULL, this, SLOT( fontFlash() ), true, false, false, 2, 2 );
		#endif
	#endif	
	menu->insertItem(lng->tr("FT_USAGE"), NULL, this, SLOT( slotUsage() ), true, false, false, 3, 3 );
	menu->insertItem(lng->tr("FT_ABOUT"), NULL, this, SLOT( about() ), true, false, false, 4, 4 );	
	
	softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT ( reject() ));
	softKey->setOptMenu(ZSoftKey::LEFT, menu);

	
	buildDlg();
}
fontView::~fontView()
{
	delete lng;
	lng = NULL;
	QFont::setDefaultFont( fOrg );
	
	this->removeEventFilter( this );
}
void fontView::buildDlg()
{
	QFile file(fontPath);
	mFontSize = file.size();

	QFont font; 	
	font.setBold(true);
	font.setPointSize ( 20 );
	
	QString info = lng->tr("FT_FONT_NAME")+fontName+"\n";
	info += lng->tr("FT_FONT_SIZE")+ctr( size2string(mFontSize) );
	
	ZLabel *label = new ZLabel(info , form, "ZLabel" , 0, (ZSkinService::WidgetClsID)4);
	label->setFont( font );
	label->setAutoResize(true);
	label->setFixedWidth( SCREEN_WHIDTH);
	label->setAlignment( ZLabel::AlignLeft );
	form->addChild(label);

	ZSeparator *sep = new ZSeparator(this);	
	form->addChild(sep);

	font.setBold(false);
	font.setPointSize ( 13 );
	
	info = QString("The quick brown fox jumps over a lazy dog.%1").arg("\n");
	info += ctr("1234567890!@#$%^&*()[]{}%1").arg("\n");
	info += ctr("中文字型范例, 欢迎使用Rokr Phoenix MP");	

	label = new ZLabel(info , form, "ZLabel" , 0, (ZSkinService::WidgetClsID)4);
	label->setFont( font );
	label->setAutoResize(true);
	label->setFixedWidth( SCREEN_WHIDTH);
	label->setAlignment( ZLabel::AlignLeft );
	form->addChild(label);

	font.setPointSize ( 15 );	
	
	label = new ZLabel(info , form, "ZLabel" , 0, (ZSkinService::WidgetClsID)4);
	label->setFont( font );
	label->setAutoResize(true);
	label->setFixedWidth( SCREEN_WHIDTH);
	label->setAlignment( ZLabel::AlignLeft );
	form->addChild(label);

	
	font.setPointSize ( 17 );	
	
	label = new ZLabel(info , form, "ZLabel" , 0, (ZSkinService::WidgetClsID)4);
	label->setFont( font );
	label->setAutoResize(true);
	label->setFixedWidth( SCREEN_WHIDTH);
	label->setAlignment( ZLabel::AlignLeft );
	form->addChild(label);

	font.setPointSize ( 19 );	
	
	label = new ZLabel(info , form, "ZLabel" , 0, (ZSkinService::WidgetClsID)4);
	label->setFont( font );
	label->setAutoResize(true);
	label->setFixedWidth( SCREEN_WHIDTH);
	label->setAlignment( ZLabel::AlignLeft );
	form->addChild(label);	
}
void fontView::fontTest()
{
	QString cmd = QString::null;
	QStringList plist;
	plist += lng->tr("FT_TEST_AS_MAIN_FONT");
	plist += lng->tr("FT_TEST_AS_NUM_FONT");
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("FT_TEST_FONT"),NULL);
	dlg->addItemsList(plist);	
	if(dlg->exec() == ZPopup::Accepted) 
	{
		int i = dlg->getCheckedItemIndex();
		switch (i) {
			case 0:
				cmd = QString("mount -o bind %1 %2").arg(fontPath).arg("/usr/language/fonts/AMCSL.TTF");
				break;
			case 1:
				cmd = QString("mount -o bind %1 %2").arg(fontPath).arg("/usr/language/fonts/NUMBER.TTF");
				break;
			default:
				break;
		}		
		delete dlg;		
	}
	else
	{
		delete dlg;
		return;
	}	
	
	cout<<" === cmd "<<cmd<<endl;
	
	//showQ("test",  cmd, 1);
	if( cmd != QString::null ) {
		system(cmd);
		system( QString("%1/refresh.sh &").arg(appDir) );
		reject();
	} else {
		return;
	}	
}
void fontView::fontBind()
{
	bool mark = false;
	QString destPath = QString::null;
	QString destFile = QString::null;
	QString targetFile = QString::null;
	QStringList plist;
	plist += lng->tr("FT_BIND_TO_PHONE");
	cout<<" font size "<<(mFontSize/1024+3000)<<endl;
	
	if( !df2MtdFreeSize( QString("/mmc/mmca2"), (unsigned int)(mFontSize/1024+3000) ) ) {
		plist += lng->tr("FT_BIND_TO_MMCA2");
	}	
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("FT_MOUNT_FONT"),NULL);
	dlg->addItemsList(plist);	
	if(dlg->exec() == ZPopup::Accepted) 
	{
		int i = dlg->getCheckedItemIndex();
		switch (i) {
			case 0:
				destPath = "/ezxlocal/download/mystuff/unKnown";
				mark = true;
				break;
			case 1:
				destPath = "/mmc/mmca2";
				mark = true;
				break;
			default:
				mark = false;
				break;
		}		
		delete dlg;		
	}
	else 
	{
		mark = false;
		delete dlg;
		return;
	}	
	
	plist.clear();
	
	plist = lng->tr("FT_TEST_AS_MAIN_FONT");
	plist += lng->tr("FT_TEST_AS_NUM_FONT");	
	dlg = new ZSingleSelectDlg(lng->tr("FT_MOUNT_FONT"),NULL);
	dlg->addItemsList(plist);		
	if(dlg->exec() == ZPopup::Accepted) 
	{
		int i = dlg->getCheckedItemIndex();
		switch (i) {
			case 0:
				destFile = "myfont.ttf";
				targetFile = "AMCSL.TTF";
				mark = true;
				break;
			case 1:
				destFile = "mynum.ttf";
				targetFile = "NUMBER.TTF";
				mark = true;
				break;
			default:
				mark = false;
				break;
		}		
		delete dlg;		
	}
	else 
	{
		mark = false;
		delete dlg;
		return;
	}
	
	if( mark ) {
		char buf[1024];
		sprintf(buf, "cp -fR \"%s\" \"%s/%s\"", (const char*)fontPath.local8Bit(),
					(const char*)destPath.local8Bit(), (const char*)destFile.local8Bit() );
		QString title = "";
		QString subtitle = lng->tr("POP_PLEASE_WAIT"); 
		deathDlg *execDlg = new deathDlg(title, subtitle, buf);
		execDlg->exec();
		int ret = execDlg->ret;
		delete execDlg;
		execDlg = NULL;	
		if( ret == 0) {
			system( QString("mount -o bind %1/%2 /usr/language/fonts/%3").arg(destPath).arg(destFile).arg(targetFile) );
			system( QString("%1/refresh.sh &").arg(appDir) );
			reject();
		} else {
			return;
		}				
	}
	else
		return;	
}

void fontView::fontFlash()
{
	bool mark = false;

	QString targetFile = QString::null;
	QStringList plist;
	
	plist += lng->tr("FT_TEST_AS_MAIN_FONT");
	plist += lng->tr("FT_TEST_AS_NUM_FONT");	
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("FT_FLASH_FONT"),NULL);
	dlg->addItemsList(plist);		
	if(dlg->exec() == ZPopup::Accepted) 
	{
		int i = dlg->getCheckedItemIndex();
		switch (i) {
			case 0:
				targetFile = "AMCSL.TTF";
				mark = true;
				break;
			case 1:
				targetFile = "NUMBER.TTF";
				mark = true;
				break;
			default:
				mark = false;
				break;
		}		
		delete dlg;		
	}
	else 
	{
		mark = false;
		delete dlg;
		return;
	}
	
	plist.clear();
	
	#ifdef REPLACE_FONT
	QFile file( QString("/usr/language/fonts/%1").arg(targetFile) );
	int mTargetFontSize = file.size();
	int mLimitSize = ( (int)getDf2MtdFreeSize( QString("/usr/language") )) *1024 + mTargetFontSize + 1000;
	
	cout<<"cur font size "<<mTargetFontSize<<endl;
	cout<<"test font size "<<mFontSize<<endl;
	cout<<"free mtd size  "<<getDf2MtdFreeSize( QString("/usr/language") )<<endl;
	cout<<"cur font size + free size "<<mLimitSize<<endl;
	
	if( mFontSize >= mLimitSize) {	
		showQ( lng->tr("FT_ERROR"), lng->tr("FT_NO_ENOUGH_FREE_SPACE"), 2 );
		return;
	}
	char buf[1024];
	sprintf(buf, "cp -fr %s /usr/language/fonts/%s", (const char*)fontPath.local8Bit(), (const char*)targetFile.local8Bit() );
	printf("Debug , exec cmd %s \n", buf);
	
	QString title = lng->tr("FT_REPLACE_FONT");
	QString text = lng->tr("FT_REPLACEING_FONT");
	#endif

	
	#ifndef REPLACE_FONT
	int destType = 255;
	//mark = false;
	
	plist = lng->tr("FT_FLASH_CRAMFS");
	plist += lng->tr("FT_FLASH_SQUASHFS");
	plist += lng->tr("FT_FLASH_JFFS2");	
	dlg = new ZSingleSelectDlg(lng->tr("FT_MOUNT_FONT"),NULL);
	dlg->addItemsList(plist);		
	if(dlg->exec() == ZPopup::Accepted) 
	{
		destType = dlg->getCheckedItemIndex();
		//mark = true;
		delete dlg;		
	}
	else 
	{
		//mark = false;
		delete dlg;
		return;
	}	
	
	char buf[1024];
	switch(destType) {
		case 0:
			sprintf(buf, "mkfs.cramfs /usr/language /ezxlocal/download/mystuff/.languageFlashTmp");
			break;
		case 1:
			sprintf(buf, "mksquashfs /usr/language /ezxlocal/download/mystuff/.languageFlashTmp");
			break;
		case 2:
			sprintf(buf, "mkfs.jffs2 -d /usr/language -o /ezxlocal/download/mystuff/.languageFlashTmp --pad=%s", MTD_LANG_SIZE);
			break;
		default:
			return;
			break;	
	}
	QString title = "";
	QString text = lng->tr("FT_MAKING_FLASH_TMP_FILE");

	system( QString("mount -o bind %1 /usr/language/fonts/%2").arg(fontPath).arg(targetFile) );
	
	deathDlg *execDlg = new deathDlg(title, text, buf);
	execDlg->exec();
	int ret = execDlg->ret;
	delete execDlg;
	execDlg = NULL;	
	
	system( QString("umount /usr/language/fonts/%1").arg(targetFile) );
	QFile file(	"/ezxlocal/download/mystuff/.languageFlashTmp" );
	if( ret != 0 ) {
		file.remove();
		return;	
	}
	
	if( file.size() > MTD_LANG_SIZE ) { // the size of tmp file larger than the lang mtdblock size
		showQ(lng->tr("FT_ERROR"), lng->tr("FT_TMP_FILE_BIG"), 2);
		file.remove();
		return;	
	}
	
	if( file.size() < MTD_LANG_SIZE ) {
		text = lng->tr("FT_ADDING_TMP_FILE");
		#ifdef ZN5
		sprintf(buf, "addsmg /ezxlocal/download/mystuff/.languageFlashTmp -total 900000 FF");
		#else
		sprintf(buf, "addsmg /ezxlocal/download/mystuff/.languageFlashTmp -total 980000 FF");
		#endif		
		execDlg = new deathDlg(title, text, buf);
		execDlg->exec();
		int i = execDlg->ret;
		delete execDlg;
		execDlg = NULL;	
		if( i != 0 ) {
			file.remove();
			return;			
		}	
	}
	
	sprintf(buf, "dd if=/ezxlocal/download/mystuff/.languageFlashTmp of=/dev/mtdblock/lang");
	text = lng->tr("FT_FLASHING_FONT");
	#endif
	
	deathDlg *ddlg = new deathDlg(title, text, buf);
	ddlg->exec();
	int r = ddlg->ret;
	delete ddlg;
	ddlg = NULL;
	
	#ifndef REPLACE_FONT
	file.remove();
	#endif
		
	if( r != 0) {
		showQ(lng->tr("FT_ERROR"), lng->tr("FT_FLASHING_ERROR"), 2);
		return;		
	} else {
		showQ(lng->tr("FT_OK"), lng->tr("FT_REBOOT_PHONE"), 2);
		system("reboot");	
	}

	reject();
}


void fontView::about()
{
	QString text = ctr("Rokr Font\n");
	text += ctr("Version 1.0\n");
	text += ctr("Update 2011/04/21\n");
	text += ctr("wanggjghost(泪の单翼天使)\n");
	text += ctr("www.591fan.com\n");
	text += ctr("41245110@qq.com\n");
	text += ctr("All rights reserved.\n\n");
	
	showQ(lng->tr("Rokr Font"), text, 2);
}
void fontView::slotUsage()
{
	QString text = QString("     %1\n\n" ).arg( lng->tr("FT_USAGE") );
	text += QString("%1\n\n").arg( lng->tr("FT_TEST_USAGE") );
	text +=QString("%1\n\n").arg( lng->tr("FT_MOUNT_USAGE") );
	#ifdef FONT_WRITABLE
		#ifdef VE66
		text +=QString("%1\n\n").arg( lng->tr("FT_REPLACE_USAGE") );	
		#else
		text +=QString("%1\n\n").arg( lng->tr("FT_FLASH_USAGE") );
		text +=QString("%1\n\n").arg( lng->tr("FT_FLASH_TYPE_USAGE") );
		#endif
	#endif	
	
	showQ(lng->tr("FT_USAGE"), text, 2);

}

bool fontView::eventFilter(QObject* o, QEvent* pEvent)
{
	if ( QEvent::KeyRelease == pEvent->type() )
	{
		QKeyEvent *pKey = (QKeyEvent*)pEvent;
		if (pKey->key() == KEY_UP)	
		{
			form->scrollBy(0,-20);
		}
		if (pKey->key() == KEY_DOWN)	
		{
			form->scrollBy(0,20);	
		}
	}
    return QWidget::eventFilter( o, pEvent ); 	
}


/*
int main( int argc, char **argv )
{
	//QString file = argv[2];
	
	ZApplication* a = new ZApplication( argc, argv );
	fontView * v = new fontView();//(file);
	//a->setMainWidget( v );
    //	v->show();
	int ret = v->exec();

	delete v;
	delete a;
   	return ret;		
}
*/



