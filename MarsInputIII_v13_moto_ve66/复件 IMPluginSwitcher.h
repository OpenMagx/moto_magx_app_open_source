#ifndef IMPLUGINSWITCHER_H 
#define IMPLUGINSWITCHER_H

#include <qevent.h>
#include <ZInputField.h>
#include <qpoint.h>

class IMPluginSwitcher
{
  public:
    bool keyPressed(QKeyEvent *p_keyPressEvent,  ZInputField* field);
    bool keyPressedInternal(QKeyEvent *e, ZInputField* field);
    
  private:
  	QPoint pos;

};
#endif
