#ifndef IMPLUGINSWITCHER_H 
#define IMPLUGINSWITCHER_H

#include <qevent.h>
#include <ZInputField.h>
#include <qpoint.h>
#include <qwidget.h>

enum EDIT_FILD_TYPE
{
	TYPE_UDEFINE,
	TYPE_LINE_EDIT,
	TYPE_TEXT_EDIT,
	TYPE_MULTI_LINE_EDIT,
};

class IMPluginSwitcher
{
  public:
    bool keyPressed(QKeyEvent *p_keyPressEvent,  ZInputField* field);
	//bool hack(QKeyEvent *,  ZInputField* );
    bool keyPressedInternal(QKeyEvent *e, ZInputField* field);
    
  private:
  	QPoint pos;

};
#endif
