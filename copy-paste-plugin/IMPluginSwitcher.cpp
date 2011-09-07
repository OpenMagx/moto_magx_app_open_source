//
// Copy-Past for magx phone - EvolutionPath
//
// Version: 0.3.5
//
// Writen by Ant-ON (prozanton@gmail.com), 2009-2010
//

#include "IMPluginSwitcher.h"

//EZX
#include <ZListBox.h>
#include <ZSingleSelectDlg.h>
#include <ZMultiLineEdit.h>
#include <ZLineEdit.h>
#include <ZTextEdit.h>
#include <ZOptionsMenu.h>

//QT
#include <qclipboard.h>
#include <qtimer.h>

//My
#include "GUI_Define.h"

//#define DEBUG_LIB

#ifdef EZX_U9 //in U9 not function tr(...) in ZWidget class
#define ZWidget ZPopup
#endif

#define INSERT_ITEM(name, id) menu->insertItem(name, NULL, NULL, true, id)
#define INSERT_SEP() menu->insertSeparator(); 
#define CANCEL_CODE -1

#ifdef DEBUG_LIB
#include <iostream>
#define toLog( t ) std::cout << t << std::endl
#else
#define toLog( t ) 
#endif

static bool onSelectText=false;
static QPoint pos;

#define SET_CURSOR { pos.setX(iSelX); pos.setY(iSelY); }
#define GET_CURSOR_X pos.x()
#define GET_CURSOR_Y pos.y()

bool IMPluginSwitcher::keyPressed(QKeyEvent *p_keyPressEvent,  ZInputField* field)
//bool IMPluginSwitcher::keyReleased(QKeyEvent *p_keyPressEvent,  ZInputField* field)
//bool IMPluginSwitcher::hack(QKeyEvent *p_keyPressEvent,  ZInputField* field)
{
	toLog( "##### Start my keyPressed! ");

	bool ret = keyPressedInternal( p_keyPressEvent, field );

    if ( field != NULL && p_keyPressEvent->key() == KEY_GREEN )
    {
		toLog( "##### Key code is GREEN !!! " );
		toLog( "##### Getting editor" );
		
		QWidget * editor = field->getEditorWidget();
		
		toLog( "##### Create action dlg" );
		EDIT_FILD_TYPE tupeEditor = TYPE_UDEFINE;
		
		{ //For not use more memory, to store class name
		QString s = QString(editor->className());

		toLog( "##### Editor class: "+s );

		if ( s.find("MultiLineEdit") != -1)
			tupeEditor = TYPE_MULTI_LINE_EDIT; 
		else if ( s.find("LineEdit") != -1 )
			tupeEditor = TYPE_LINE_EDIT; 
		else if ( (s.find("ZTextEdit") != -1) || (s.find("MMS_PageWidget") != -1) )
			tupeEditor = TYPE_TEXT_EDIT;
		else if  ( s.find("SVGCanvas") != -1 )
			return false; //Copy past don't work(
	
		}

		int selected=CANCEL_CODE;
		
		if ( onSelectText )
		{
			toLog( "##### Auto select" );
			selected = ACTION_SELECT_END;
		} else
		{			
			QRect rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
			ZOptionsMenu * menu = new ZOptionsMenu (rect, editor);//editor->topLevelWidget()
			
			toLog( "##### Insert item to list" );		
			
			INSERT_ITEM(ZWidget::tr("TXT_RID_OPTION_COPY", "Copy"),  ACTION_COPY);
			INSERT_ITEM(ZWidget::tr("TXT_RID_OPTION_INSERT", "Paste"), ACTION_PAST);
			
			int x1=0,x2=0,y1,y2;
			bool oldSel=false;
			
			if ( tupeEditor != TYPE_UDEFINE )
			{
				INSERT_ITEM(ZWidget::tr("TXT_RID_MENU_CUT", "Cut"), ACTION_CUT);
		        INSERT_SEP();
		        INSERT_ITEM(ZWidget::tr("TXT_RID_OPTION_SELECT_ALL", "onSelectText all"), ACTION_SELECT_ALL);
				INSERT_ITEM(ZWidget::tr("TXT_RID_HEADER_SELECT", "Select"), ACTION_SELECT_START);
				
				//save curren state of input fild and get cursor point
				QPoint pos(0,0);
				switch ( tupeEditor )
				{
					case TYPE_MULTI_LINE_EDIT:
						pos = ((ZMultiLineEdit*)editor)->mapToGlobal(((ZMultiLineEdit*)editor)->cursorPoint());
						oldSel = ((ZMultiLineEdit*)editor)->hasMarkedText();
						if ( oldSel )
							((ZMultiLineEdit*)editor)->getMarkedRegion( &x1, &y1, &x2, &y2 );
						else
							((ZMultiLineEdit*)editor)->getCursorPosition( &x1, &y1 );
						break;
					case TYPE_LINE_EDIT:
						pos = ((ZLineEdit*)editor)->mapToGlobal(((ZLineEdit*)editor)->cursorPoint());
						oldSel = ((ZLineEdit*)editor)->hasMarkedText();
						if ( !oldSel )
							x1=((ZLineEdit*)editor)->cursorPosition();
						break;
					case TYPE_TEXT_EDIT:
					default:
						pos = editor->mapToGlobal( field->getCursorPos() );
						break;
				}
				menu->setPosition(ZOptionsMenu::TopLeft, pos );
			}
			
			toLog(  "##### Show dlg" );
			
			menu->popup();	
			while ( !menu->isHidden() ) qApp->processEvents();
			selected = menu->getCurrentSelectedItemId();

			//load state of input fild
			if ( tupeEditor>0 )
			{
				switch ( tupeEditor )
				{
					case TYPE_MULTI_LINE_EDIT:
						if ( oldSel )
							((ZMultiLineEdit*)editor)->setSelection( x1, y1, x2, y2 );
						else
							((ZMultiLineEdit*)editor)->setCursorPosition( x1, y1, false );
						break;
					case TYPE_LINE_EDIT:
						if ( oldSel )
						{
							if ( GET_CURSOR_Y == -1 )
								((ZLineEdit*)editor)->selectAll();
							else
								((ZLineEdit*)editor)->setSelection( GET_CURSOR_X, GET_CURSOR_Y );
						}
						else
							((ZLineEdit*)editor)->setCursorPosition(x1);
						break;
					default:
						break;					
				}				
			}

			toLog(  "##### Delete dlg" );		
			    	
			delete menu;
			menu = NULL;
		}		
		
		if ( selected >= 0 )
		{
			toLog( "##### Operate code:" << selected << " edit type:" << tupeEditor );		
				
			switch (tupeEditor)
			{
				case TYPE_UDEFINE:
				{
					switch (selected)
					{
						case ACTION_COPY:
						{
							QString text = field->getText(QPoint(-1,-1),true);
							QApplication::clipboard()->setText( text=="text/plain"?"":text );
							toLog( "##### >Text:" + text  );
							break;
						}
						case ACTION_PAST:
						{
							field->insertString( field->getCursorPos(), QApplication::clipboard()->text());
							break;
						}
					}
					break;
				}	
				case TYPE_MULTI_LINE_EDIT:
				{							
					switch (selected)
					{
						case ACTION_COPY:
						{
							((ZMultiLineEdit*)editor)->copy();
							break;
						}
						case ACTION_PAST:
						{
							((ZMultiLineEdit*)editor)->paste();
							break;
						}
						case ACTION_CUT:
						{							
							((ZMultiLineEdit*)editor)->cut();
							break;
						}
						case ACTION_SELECT_ALL:
						{
							((ZMultiLineEdit*)editor)->selectAll();
							break;
						}
						case ACTION_SELECT_START:
						{
							int iSelX = 0;
							int iSelY = 0;
							((ZMultiLineEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
							
							onSelectText = true;
		    				SET_CURSOR
							break;
						}	
						case ACTION_SELECT_END:
						{
							if ( !onSelectText )
								break;

							int iSelX = 0;
							int iSelY = 0;
							((ZMultiLineEdit*)editor)->getCursorPosition( &iSelX, &iSelY );

		    				((ZMultiLineEdit*)editor)->setCursorPosition( GET_CURSOR_X, GET_CURSOR_Y, false );
							((ZMultiLineEdit*)editor)->setCursorPosition( iSelX, iSelY, true );
							
		    				onSelectText = false;			
							break;
						}															
					}
					break;
				}
				case TYPE_TEXT_EDIT:
				{				
					switch (selected)
					{
						case ACTION_COPY:
						{
							if ( ((ZTextEdit*)editor)->hasSelectedText() )
								QApplication::clipboard()->setText( ((ZTextEdit*)editor)->selectedText() );
							else
								QApplication::clipboard()->setText( ((ZTextEdit*)editor)->text() );
							break;
						}
						case ACTION_PAST:
						{
							if ( ((ZTextEdit*)editor)->hasSelectedText() )	
								((ZTextEdit*)editor)->del();

							int iSelX = 0;
							int iSelY = 0;
							
		    				((ZTextEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
		    				((ZTextEdit*)editor)->insertAt(QApplication::clipboard()->text(), iSelX, iSelY);							
							break;
						}
						case ACTION_CUT:
						{
							if ( ((ZTextEdit*)editor)->hasSelectedText() )
								QApplication::clipboard()->setText( ((ZTextEdit*)editor)->selectedText() );
							else
								QApplication::clipboard()->setText( ((ZTextEdit*)editor)->text() );	
							if ( ((ZTextEdit*)editor)->hasSelectedText() )	
								((ZTextEdit*)editor)->del();
							else
								((ZTextEdit*)editor)->clear();						
							break;
						}
						case ACTION_SELECT_ALL:
						{
							((ZTextEdit*)editor)->selectAll(true);
							break;
						}
						case ACTION_SELECT_START:
						{
							int iSelX = 0;
							int iSelY = 0;
							
		    				((ZTextEdit*)editor)->getCursorPosition( &iSelX, &iSelY );
							onSelectText = true;
		    				SET_CURSOR
							break;
						}	
						case ACTION_SELECT_END:
						{
							if ( !onSelectText )
								break;

							int iSelX = 0;
							int iSelY = 0;

		    				((ZTextEdit*)editor)->getCursorPosition( &iSelX, &iSelY );					
							((ZTextEdit*)editor)->setSelection( GET_CURSOR_X, GET_CURSOR_Y, iSelX, iSelY );
							
		    				onSelectText = false;			
							break;
						}															
					}
					break;					
				} 
				case TYPE_LINE_EDIT:
				{				
					switch (selected)
					{
						case ACTION_COPY:
						{
							if ( ((ZLineEdit*)editor)->hasMarkedText() )
								QApplication::clipboard()->setText( ((ZLineEdit*)editor)->markedText() );
							else
							{
								QString text = ((ZLineEdit*)editor)->text();
								QApplication::clipboard()->setText( text=="text/plain"?"":text );
							}
							break;
						}
						case ACTION_PAST:
						{
		    				((ZLineEdit*)editor)->insert(QApplication::clipboard()->text());							
							break;
						}
						case ACTION_CUT:
						{
							if ( ((ZLineEdit*)editor)->hasMarkedText() )
								QApplication::clipboard()->setText( ((ZLineEdit*)editor)->markedText() );
							else
								QApplication::clipboard()->setText( ((ZLineEdit*)editor)->text() );	
							if ( ((ZLineEdit*)editor)->hasMarkedText() )	
								((ZLineEdit*)editor)->del();
							else
								((ZLineEdit*)editor)->clear();						
							break;
						}
						case ACTION_SELECT_ALL:
						{
							((ZLineEdit*)editor)->selectAll();
		    				int iSelX=-1;
		    				int iSelY=0;
		    				SET_CURSOR							
							break;
						}
						case ACTION_SELECT_START:
						{
		    				onSelectText = true;
		    				int iSelX=(((ZLineEdit*)editor)->cursorPosition());
		    				int iSelY=0;
		    				
		    				SET_CURSOR		
							break;
						}	
						case ACTION_SELECT_END:
						{
							if ( !onSelectText )
								break;		
							
							int iSelY = ((ZLineEdit*)editor)->cursorPosition()-GET_CURSOR_X;
							int iSelX=GET_CURSOR_X;
							if ( iSelY > 0 )
								((ZLineEdit*)editor)->setSelection( GET_CURSOR_X, iSelY );
		    				
		    				SET_CURSOR	
		    				
		    				onSelectText = false;				
							break;
						}														
					}
					break;					
				}
			}
		}
		return true;
	}
	
	toLog( "##### End my keyPressed!" );
	return ret;
}
