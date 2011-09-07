#include "MarsDialog.h"

MarsDialog::MarsDialog(QWidget *parent,QString text):QDialog(parent,0,TRUE)
{
	setFixedSize(240, 320);
	//this->resize(240, 320);
	//this->setGeometry(0, 0,240,320);
	//setMorphMode(3);
	//this->show();
    
	//system("pmtool -d 1");	
	//system("pmtool -d 0");
	//system( QString("echo 532 > /sys/mpm/op") );
	
	//建立U2Panel界面
    u2p = new U2Panel(this,text);
    layout = new QVBoxLayout(this);
    layout->addWidget(u2p);
    

	//u2p->doResize();
	connect(u2p,SIGNAL(accepted()),this,SLOT(accept()));
	connect(u2p,SIGNAL(rejected()),this,SLOT(reject()));
	//cout<<"hel"<<endl;
}
MarsDialog::~MarsDialog()
{
	//system("pmtool -d 1");
	
	delete u2p;
	delete layout;
}

QString MarsDialog::getMarsText(){
	return u2p->text_buf;
}
void MarsDialog::keyPressEvent(QKeyEvent *event){
        int key=event->key();
        u2p->keyPre(key);
}
void MarsDialog::keyReleaseEvent(QKeyEvent *event){
        int key=event->key();
        u2p->keyRel(key);
}

