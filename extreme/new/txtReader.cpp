

#include <ZMessageDlg.h>
#include <ZGlobal.h>
#include <ZSingleSelectDlg.h>

#include "txtReader.h"
//#include "UtilsCode.h"
#include "lng.h"

//extern Lng *lng;

reader :: reader(QString &_fileName) :MyBaseDlg()
{
    lng = new Lng();
	
	setMainWidgetTitle(tr("READER"));
	
	filename = _fileName;
	pageCount = 0;
	pageCur = 0;
	pageSize = 300;
	mTextCodec = QTextCodec::codecForName("UTF-8");

	this->installEventFilter( this );

	
	form = new ZFormContainer(this);
	form->setVScrollBarMode(ZScrollPanel::Auto);
	form->setHScrollBarMode(ZScrollPanel::Auto);
	this->setContentWidget(form);	
	
	QFont f( qApp->font() );
	f.setPointSize(14); 
	
	zlb = new ZLabel(QString("Loading...."), form, "ZLabel", 0, (ZSkinService::WidgetClsID)4);
	zlb->setFixedWidth(SCREEN_W-10);
	zlb->setFont(f);
	zlb->setAlignment( ZLabel::AlignLeft );
	zlb->setAutoResize(true);
	form->addChild((ZWidget*)zlb);

	softKey = new ZSoftKey ( "CST_2A", this, this );
	this->setSoftKey(softKey);
    softKey->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"),
	                               tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
	softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK", "Back"));	

	QRect rect = ZGlobal::getContentR();
		
	menu = new ZOptionsMenu(rect, this, 0, 0, (ZSkinService::WidgetClsID)55);
	menu->insertItem(lng->tr("FT_CHG_CODEC"), NULL, this, SLOT( slotCodec() ), true, false, false, 0, 0);	
	menu->insertItem(lng->tr("FT_ABOUT"), NULL, this, SLOT( slotAbout() ), true, false, false, 1, 1);	
	
	softKey->setOptMenu(ZSoftKey::LEFT, menu);	
	softKey->setClickedSlot( ZSoftKey::RIGHT, this ,SLOT( reject() ) );

	
	//this->setFullScreenMode(true);
	
	loadText();
	//QTimer::singleShot( 500, this, SLOT( loadText() ) );
}
reader::~reader()
{
	this->removeEventFilter( this );
	delete lng;
	lng = NULL;
}

void reader::loadText()
{
	//printf("====== load text =========\n");
	zlb->setText( QString("Loading....") );
	QFile file( ctr(filename) );
	
	if ( file.open( IO_ReadOnly ) ) 
	{
		if( file.size() > 500000 ) {
			char buf[500000];
			file.readBlock(buf, sizeof(buf));
			m_txtContainer = QString( mTextCodec->toUnicode(buf) );
		} else {
			char buf[file.size()+1];
			file.readBlock(buf, sizeof(buf));
			buf[file.size()+1] = '\0';
			m_txtContainer = QString( mTextCodec->toUnicode(buf) );
		}			
		file.close();
		
		QRegExp rexp( QString("\n") );
		m_txtContainer = m_txtContainer.replace( rexp, ctr("↓") );
	}
	else
	{
		m_txtContainer = ctr("读取文件出错。");
	}

	setPageCount();
	
	pageCur = 0;
	
	nextPage();	
}

void reader::setPageCount()
{
	zlb->setText( QString("Calcuating text words....") );
	QString tmp = m_txtContainer;
	QString subtmp = "tmp";
	pageCount = 0;
	while(subtmp != "")
	{
		pageCount++;
		subtmp = tmp.mid((pageCount-1)*pageSize,pageSize);
	}
	pageCount--;
} 


void reader::nextPage()
{
	if(pageCur<pageCount)
		pageCur++;
    QString tmp = m_txtContainer.mid( (pageCur-1)*pageSize,pageSize );
	zlb->setText(tmp);
	zlb->setFocus();

	this->setMainWidgetTitle( ctr("页数：%1/%2").arg(pageCur).arg(pageCount) );
}

void reader::prePage()
{
	if(pageCur>1)
		pageCur--;
	QString tmp = m_txtContainer.mid( (pageCur-1)*pageSize, pageSize );	
	zlb->setText(tmp);
	zlb->setFocus();

	this->setMainWidgetTitle( ctr("页数：%1/%2").arg(pageCur).arg(pageCount) );
}
void reader::slotCodec()
{
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("FT_CHG_CODEC"),NULL);
	QStringList list;
	list += QString("UTF-8");
	list += QString("CP1251");
	list += QString("KOI8-R");
	list += QString("ISO8859-1");
	list += QString("ISO8859-2");
	list += QString("ISO8859-5");
	list += QString("KOI8-U");
	list += QString("GBK");
	list += QString("Big5");	
	
	dlg->addItemsList(list);	
	if(dlg->exec() == ZPopup::Accepted) 
	{
		int i = dlg->getCheckedItemIndex();
		delete dlg;
		dlg = NULL;

		switch (i) {
			case 0:
				mTextCodec = QTextCodec::codecForName("UTF-8");
				break;		
			case 1:
				mTextCodec = QTextCodec::codecForName("CP1251");
				break;
			case 2:
				mTextCodec = QTextCodec::codecForName("KOI8-R");
				break;	
			case 3:
				mTextCodec = QTextCodec::codecForName("ISO8859-1");
				break;	
			case 4:
				mTextCodec = QTextCodec::codecForName("ISO8859-2");
				break;		
			case 5:
				mTextCodec = QTextCodec::codecForName("ISO8859-5");
				break;				
			case 6:
				mTextCodec = QTextCodec::codecForName("KOI8-U");
				break;
			case 7:
				mTextCodec = QTextCodec::codecForName("GBK");
				break;			
			case 8:
				mTextCodec = QTextCodec::codecForName("Big5");
				break;					
			default:
				mTextCodec = QTextCodec::codecForName("CP1251");		
		}
		//QTimer::singleShot( 500, this, SLOT( loadText() ) );	
		loadText();
	}
	else
	{
		delete dlg;
		return;
	}	

}
bool reader::eventFilter(QObject* o, QEvent* pEvent)
{
	if ( QEvent::KeyRelease == pEvent->type() )
	{
		QKeyEvent *pKey = (QKeyEvent*)pEvent;
		switch ( pKey->key() ) {
			case KEY_UP :	
				form->scrollBy(0,-20);
				return true;
				break;
			case KEY_DOWN :
				form->scrollBy(0,20);	
				return true;
				break;
			case KEYCODE_LEFT :
				prePage();
				form->scrollBy(0,- 400);//??
				return true;
				break;
			case KEYCODE_RIGHT :
				nextPage();
				form->scrollBy(0,- 400);//??
				return true;
				break;
			//case KEYCODE_LEFT_SK :
			//	slotAbout();
			//	break;
			//case KEYCODE_RIGHT_SK :	
			//	reject();
			//	break;
			default :
				break;
		}
	}
    return QWidget::eventFilter( o, pEvent ); 	
}
QString reader::ctr(const char *ChineseString)
{
    QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString);
}

void reader::slotAbout()
{
	QString title = ctr("关于");
	QString text = ctr("简易文本阅读器\n");
	text += ctr("Update 2011/04/25\n");
	text += ctr("wanggjghost(泪の单翼天使)\n");
	text += ctr("www.591fan.com\n");
	text += ctr("41245110@qq.com\n");
	text += ctr("All rights reserved.\n");
	
	text += ctr("左右键翻页，上下键滚动文本\n");
	ZMessageDlg* dlg = new ZMessageDlg(title, text, (ZMessageDlg::MessageDlgType)2);
	dlg->exec();
	delete dlg;
	dlg = NULL;
}

/*
int main( int argc, char **argv)
{

	QString path = argv[2];
	
	ZApplication *app = new ZApplication(argc, argv);
	lng = new Lng();
	reader *a = new reader(path);
	a->exec();

	delete a;
	delete lng;
	delete app;
	return 0;

}
*/



