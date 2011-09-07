
#include <ZConfig.h>
#include <ZApplication.h>
#include <ZFormContainer.h>
#include <ZScrollPanel.h>
#include <ZScrollView.h>
#include <ZSoftKey.h>
#include <ZLabel.h>

#include <iostream>

#include "iconSet.h"

using namespace std;

extern Lng *lng;

iconSet::iconSet():MyBaseDlg()
{
	//lng = new Lng();
	
	creatWindow();
	creatSoftKey();	
		
	m_appDir = getAppDir();
	
	ZConfig cfg( QString("%1/%2").arg(m_appDir).arg(DATA_FILE) );
	QString d1 = cfg.readEntry( "LIST1", "Icon", "");
	QStringList list = QStringList::split( "!", d1 );
	
	showIconList(list);
	
	showIconList(list);
	
	qApp->installEventFilter(this);
	
}
iconSet::~iconSet()
{
	this->removeEventFilter(this);
	
	//delete lng;
	//lng = NULL;
}

void iconSet::creatWindow()
{
	this->setAppTitle( QString("iconSet") );
	
	iconView = new ZIconView(this);
	iconView->enableMarquee(true);
	this->setContentWidget(iconView);
	
//	connect( iconView , SIGNAL( clicked( ZIconViewItem * ) ), this, SLOT( slotClicked(ZIconViewItem *) ) );	
}
void iconSet::creatSoftKey()
{
	ZSoftKey *softKey = new ZSoftKey (  "CST_2A" , this, this );
	this->setSoftKey(softKey);
    softKey->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"),
	                               tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
	softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK", "Back"));	

	QRect rect = ZGlobal::getContentR();
		
	menu = new ZOptionsMenu(rect, this, 0, 0, (ZSkinService::WidgetClsID)55);
	menu->insertItem(lng->tr("FT_DATA1"), NULL, this, SLOT( creatData1() ), true, false, false, 0, 0);	
	menu->insertItem(lng->tr("FT_DATA2"), NULL, this, SLOT( creatData2() ), true, false, false, 1, 1);
	menu->insertItem(lng->tr("FT_DATA3"), NULL, this, SLOT( creatData3() ), true, false, false, 2, 2);
	menu->insertItem(lng->tr("FT_DATA4"), NULL, this, SLOT( creatData4() ), true, false, false, 3, 3);
	menu->insertItem(lng->tr("FT_DATA5"), NULL, this, SLOT( creatData5() ), true, false, false, 4, 4);
	menu->insertItem(lng->tr("FT_ABOUT"), NULL, this, SLOT( slotAbout() ), true, false, false, 5, 5);	
	
	softKey->setOptMenu(ZSoftKey::LEFT, menu);	
	softKey->setClickedSlot( ZSoftKey::RIGHT, this ,SLOT( reject() ) );	
}
QString iconSet::getIconItemName()
{
	return m_iconItemName;
}
void iconSet::slotQuit()
{
	//qApp->quit();
	MyBaseDlg::reject();
}
void iconSet::slotAbout()
{
	QString title = ctr("关于");
	QString text = ctr("右键图标设置\n");
	text += ctr("Build 2011/04/25\n");
	text += ctr("wanggjghost(泪の单翼天使)\n");
	text += ctr("All rights reserved.\n");
	text += ctr("www.591fan.com\n");
	text += ctr("41245110@qq.com\n");

	showQ( title, text, 2);
}
void iconSet::showIconList(const QStringList &iconDataList)
{
	iconView->clear();
	
	QStringList::ConstIterator p;	
	QString iconName;
	QPixmap pm;
	ZIconViewItem *iconItem = NULL;
	for (p = iconDataList.begin(); p != iconDataList.end(); ++p ) 
	{
		iconName = *p;
		
		if( !iconName.endsWith(".png") ) 
			continue;

		pm = iconReader.getIcon( iconName );
		
		if( !pm.isNull() ) {
			iconItem = new ZIconViewItem(iconView);
			iconItem->setText( iconName );
			iconItem->setPixmap( pm );
			iconView->insertItem(iconItem);
		}	
	}
	iconView->setCurrentItem( iconView->item(0) );
}
void iconSet::creatData1()
{
	ZConfig cfg( QString("%1/%2").arg(m_appDir).arg(DATA_FILE) );
	QString d1 = cfg.readEntry( "LIST1", "Icon", "");
	QStringList list = QStringList::split( "!", d1 );
	
	showIconList(list);
}
void iconSet::creatData2()
{
	ZConfig cfg( QString("%1/%2").arg(m_appDir).arg(DATA_FILE) );
	QString d1 = cfg.readEntry( "LIST2", "Icon", "");
	QStringList list = QStringList::split( "!", d1 );
	
	showIconList(list);
}
void iconSet::creatData3()
{
	ZConfig cfg( QString("%1/%2").arg(m_appDir).arg(DATA_FILE) );
	QString d1 = cfg.readEntry( "LIST3", "Icon", "");
	QStringList list = QStringList::split( "!", d1 );
	
	showIconList(list);
}
void iconSet::creatData4()
{
	ZConfig cfg( QString("%1/%2").arg(m_appDir).arg(DATA_FILE) );
	QString d1 = cfg.readEntry( "LIST4", "Icon", "");
	QStringList list = QStringList::split( "!", d1 );
	
	showIconList(list);
}
void iconSet::creatData5()
{
	ZConfig cfg( QString("%1/%2").arg(m_appDir).arg(DATA_FILE) );
	QString d1 = cfg.readEntry( "LIST5", "Icon", "");
	QStringList list = QStringList::split( "!", d1 );
	
	showIconList(list);
}
void iconSet::slotClicked()
{
	ZIconViewItem *pItem = iconView->currentItem();
	m_iconItemName = pItem->text();
	
	QString title = lng->tr("FT_CONFIRM");
	QString text = QString("%1 : %2 ?").arg(lng->tr("FT_CONFIRM_CUR") ).arg(m_iconItemName);
	
	int ret = showQ(title, text, 1);
	if( ret == 1 )
		MyBaseDlg::accept();
	else 
		return;
}
bool iconSet::eventFilter( QObject *o, QEvent *e)
{
	//return QWidget::eventFilter( o, e );
		
	if (o == iconView ) {
		//cout<<" ==== obj is iconView ======"<<endl;	
		if (/* e->type()==QEvent::KeyRelease || */e->type()==QEvent::KeyPress ) 
		{
			QKeyEvent *k = (QKeyEvent *)e;
			//cout<<" #### key press %d "<<k->key()<<"#####"<<endl;
			if ( k->key()==KEYCODE_LEFT  ||  k->key()==KEYCODE_RIGHT ) {
				//cout<<"===== eat key ===== "<<endl;
				uint t = 0;
				t = iconView->count();
				if( t == 0 ) {
					//cout<<"#### no items #####" <<endl;
					return true;
				}

				int i = iconView->index( iconView->currentItem() );
				
				//cout<<"#### cur item == "<<i<<"  #####"<<endl;
				
				if( k->key()==KEYCODE_LEFT ) {
					iconView->setCurrentItem( iconView->item( (i-1)<0 ? (int)t-1 : (i-1) ) );	
					//cout<<"#### turn to c  "<<(int)i-1<<"   #####"<<endl;
				}	
				if ( k->key()==KEYCODE_RIGHT ) 	{
					iconView->setCurrentItem( iconView->item( (i+1)>=(int)t ? 0 : (i+1) ) );	
					//cout<<"#### turn to c  "<<"0"<<"   #####"<<endl;
				}	
				
				return true; // 吃掉了这个事件
			} else {
				if ( k->key()== KEY_CENTER  ) {
					slotClicked();
					return true;
				} else {			
					return QWidget::eventFilter( o, e );
				}	
			}	
		} else {
				// 标准事件处理
			return QWidget::eventFilter( o, e );
		}
	} else {
		return QWidget::eventFilter( o, e );
	}	
}







