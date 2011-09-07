#include "IMPluginSwitcher.h"
#include "MarsDialog.h"
#include <iostream>
#include <ZMultiLineEdit.h>
using namespace std;

bool IMPluginSwitcher::keyPressed(QKeyEvent *p_keyPressEvent,  ZInputField* field)
{
	
	cout<<"#################IMPluginSwitcher#######################"<<endl;
    int keyCode = p_keyPressEvent->key();
 
    bool ret = keyPressedInternal(p_keyPressEvent, field);
    
	cout<<(field==NULL)<<"dddd"<<keyCode<<endl;
    
    if ( field != NULL && (keyCode == 4144||keyCode == 4159))
    {
		QWidget * editor = field->getEditorWidget();
		int iSelX = 0;
		int iSelY = 0;
		((ZMultiLineEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
		cout<<iSelX<<"   "<<iSelY<<endl;

		QString text_pre=((ZMultiLineEdit*)editor)->text();//.local8Bit();
		MarsDialog *md =new MarsDialog(0,text_pre.stripWhiteSpace() );
		int res=md->exec();
		cout<<"res :exec() ="<<res<<endl;
		QString text= md->getMarsText();
		delete md;
		if(res==1){
			cout<<"insert text "<<endl;
			((ZMultiLineEdit*)editor)->setText(text);
			//field->setText(text);
		}
	}
    return ret;
}

