
#include "showPic.h"


showPic::showPic(QString &fileName) :MyBaseDlg()
{
	setAppTitle(fileName);
	
	img_bg.load(fileName);	
	
	softKey = new ZSoftKey("CST_2A", this, this);
	this->setSoftKey(softKey);	
	//softKey->setText(ZSoftKey::LEFT,  tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
	softKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK", "Back"));	
	softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT ( slotQuit() ));
	softKey->setClickedSlot(ZSoftKey::LEFT, this, SLOT (  slotQuit() ));	
	
	this->setFullScreenMode(true);
}

void showPic::keyPressEvent(QKeyEvent* k)
{
	printf("key pressed %d\n", k->key());
	switch(k->key())
	{
		case 4152://左键
			reject();
			//softKey->show();
			break;
		case 4154: //右键
			reject();
			//softKey->show();
			break;
		default:
			break;
	}		
	QWidget::keyPressEvent(k);		
}

void showPic::slotQuit()
{
	//qApp->quit();
	reject();
}
void showPic::paintEvent( QPaintEvent * pe)
{
	QPixmap	mypix;//( "bg.png");
	mypix = img_bg;	//将背景图作为画布
	QRect ur(0,0, SCREEN_W, SCREEN_H);	//用户可见区域
	ur=pe->rect();				
	QPainter p(&mypix);	//定义画笔
	p.begin(&mypix);		//开始绘制
	
	//QFont font1("AMCSL", 12);
	//p.setFont(font1);
	
	//p.drawText(10, 20, 30, 50, 1, text);
	p.end();		//结束绘制
	setWFlags(getWFlags() | Qt::WRepaintNoErase);	//设置无背景色*****
	bitBlt(this, 0, 0, &mypix, 0, 0, SCREEN_W, SCREEN_H);//将内存中画布复制到屏幕
	QWidget::paintEvent( pe);

}

