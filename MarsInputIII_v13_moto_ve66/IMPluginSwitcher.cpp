#include "IMPluginSwitcher.h"
#include "MarsDialog.h"

#include <ZMultiLineEdit.h>
#include <ZLineEdit.h>
#include <ZTextEdit.h>

#include <qfile.h>

#include <iostream>
using namespace std;

bool IMPluginSwitcher::keyPressed(QKeyEvent *p_keyPressEvent,  ZInputField* field)
//bool IMPluginSwitcher::hack(QKeyEvent *p_keyPressEvent,  ZInputField* field)
{
	
	//cout<<"#################IMPluginSwitcher#######################"<<endl;
	
    int keyCode = p_keyPressEvent->key();
 
    bool ret = keyPressedInternal(p_keyPressEvent, field);
    
	cout<<(field==NULL)<<" ==== keycode "<<keyCode<<endl;
    
    if ( field != NULL && (keyCode == 4144 /*||keyCode == 4159*/))
    {
		QWidget * editor = field->getEditorWidget();
		
		//system("pmtool -d 0");
		//system( QString("echo 532 > /sys/mpm/op") );
		
		EDIT_FILD_TYPE tupeEditor = TYPE_UDEFINE;
		
		{ //For not use more memory, to store class name
			QString s = QString( editor->className() );

			//cout<<"##### Editor class: "<<s<<endl;

			if ( s.find("MultiLineEdit") != -1) {
				tupeEditor = TYPE_MULTI_LINE_EDIT; 
				//cout<<"==== type editor MultiLIne "<<endl;
			}	
			else if ( s.find("LineEdit") != -1 ) {
				tupeEditor = TYPE_LINE_EDIT; 
				//cout<<"==== type editor Line "<<endl;
			}			
			else if ( (s.find("ZTextEdit") != -1) || (s.find("MMS_PageWidget") != -1) ) {
				tupeEditor = TYPE_TEXT_EDIT;
				//cout<<"==== type editor  text "<<endl;
			}	
			else if  ( s.find("SVGCanvas") != -1 ) {
				//cout<<"==== type editor  svg ,will return "<<endl;
				return false; //Copy past don't work(
			}
		}		
		
		if ( tupeEditor != TYPE_UDEFINE )
		{
			QString text_pre = QString::null;
								
			int iSelX = 0;
			int iSelY = 0;
			
			switch (tupeEditor) {
				case TYPE_MULTI_LINE_EDIT:
					//( (ZMultiLineEdit*)editor )->getCursorPosition( &iSelX, &iSelY );
					text_pre = ( (ZMultiLineEdit*)editor )->text();//.local8Bit();
					break;
				case TYPE_LINE_EDIT:
					//( (ZLineEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
					text_pre = ( (ZLineEdit*)editor)->text();
					break;
				case TYPE_TEXT_EDIT:
					//( (ZTextEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
					text_pre = ( (ZTextEdit*)editor)->text();
					break;
				default:
					//editor->getCursorPosition( &iSelX, &iSelY );
					text_pre = field->getText( QPoint(-1, -1), true);	
					break;			
			}

			//cout<<" ==== cursor position "<<iSelX<<"   "<<iSelY<<endl;
			//cout<<"==== text pre "<<text_pre<<endl;
			
			/*QFile fb("/sys/mpm/op");
			fb.open(IO_ReadOnly);
			QString pinlv;
			fb.readLine(pinlv,20);
			fb.close();
			if(!pinlv.contains("532")) {*/
				system("(pmtool -d 0;echo 532 > /sys/mpm/op)&");
			//}
			
			MarsDialog *md =new MarsDialog(0, text_pre.stripWhiteSpace() );
			int res=md->exec();
			
		//	cout<<"res :exec() = "<<res<<endl;
			
			QString text_afte = md->getMarsText();
			delete md;
			md = NULL;
			if ( res == 1 ) {
				//int iSelX = 0;
				//int iSelY = 0;
				//cout<<"insert text "<<endl;
				
				switch (tupeEditor) {
					case TYPE_MULTI_LINE_EDIT:
						( (ZMultiLineEdit*)editor)->setText(text_afte);
						break;
					case TYPE_LINE_EDIT:
						( (ZLineEdit*)editor)->setText(text_afte);
						break;
					case TYPE_TEXT_EDIT:
						//( (ZTextEdit*)editor)->setText(text_afte);
						//( (ZTextEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
						//cout<<" ==== cursor position "<<iSelX<<"   "<<iSelY<<endl;
						( (ZTextEdit*)editor)->clear();	
						( (ZTextEdit*)editor)->insertAt(text_afte, 0, 0);
						( (ZTextEdit*)editor)->moveCursor( ZTextEdit::MoveLineEnd, false);
						
						//( (ZTextEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
						//cout<<" ==== cursor position "<<iSelX<<"   "<<iSelY<<endl;
						break;
					default :
						field->setText(text_afte);
						break;				
				}
				
				system("pmtool -d 1");
				
				//cout<<"sizeof qdialog is:"<<sizeof(md)<<endl;
				//((ZMultiLineEdit*)editor)->setText(text);
				//field->setText(text);
				return true;
			}
			else
			{
				system("pmtool -d 1");
			}
		}
	}
    return ret;
}


