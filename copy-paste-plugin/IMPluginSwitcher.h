//
// Copy-Past for magx phone - EvolutionPath
//
// Version: 0.3.5
//
// Writen by Ant-ON (prozanton@gmail.com), 2009-2010
//

#ifndef IMPLUGINSWITCHER_H 
#define IMPLUGINSWITCHER_H

//EZX
//#include "ZInputField.h"
#include <ZInputField.h>
//QT
#include <qevent.h>
#include <qpoint.h>
#include <qwidget.h>

enum EDIT_FILD_TYPE
{
	TYPE_UDEFINE,
	TYPE_LINE_EDIT,
	TYPE_TEXT_EDIT,
	TYPE_MULTI_LINE_EDIT,
};

enum EDIT_ACTION
{
	ACTION_COPY,
	ACTION_PAST,
	ACTION_CUT,
	ACTION_SELECT_ALL,
	ACTION_SELECT_START,
	ACTION_SELECT_END,
};

class Q_EXPORT IMPluginSwitcher
{
  public: 
   // bool keyReleased(QKeyEvent*, ZInputField*);
   bool keyPressed(QKeyEvent*, ZInputField*);
   // bool hack(QKeyEvent *,  ZInputField* );
    bool keyPressedInternal(QKeyEvent *, ZInputField* );
};

#endif
