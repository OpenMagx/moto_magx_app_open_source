#ifndef _H_GUI_DEFINE_H
#define _H_GUI_DEFINE_H

#ifndef __cplusplus
#error "This is a C++ header file; it requires C++ to compile."
#endif

//--------------------------------------------------------------------------------------------------
//
//   Header Name: GUI_Define.h
//
//--------------------------------------------------------------------------------------------------
//                                       INCLUDE FILES
//--------------------------------------------------------------------------------------------------

#include <qwidget.h>
#include <ZApplication.h>
#include <ZGlobal.h>

//Define key
#define KEY_LEFT              0x1012
#define KEY_UP                0x1013
#define KEY_RIGHT             0x1014
#define KEY_DOWN              0x1015
#define KEY_CENTER            0x1004

#define KEY_SIDE_SELECT       0x1005

#define KEY_SIDE_UP           0x1016
#define KEY_SIDE_DOWN         0x1017

#define KEY_GREEN             0x1030
#define KEY_RED               0x1031
#define KEY_C                 0x1032
#define KEY_LEFT_SOFTKEY      0x1038
#define KEY_RIGHT_SOFTKEY     0x103a
#define KEY_MUSIC             0x1048

//Define fix for SDK header
#if defined(EZX_Z6) || defined(EZX_V8) 
	#ifndef TypeOK
		#define TypeOK just_ok
	#endif
	#ifndef TypeChoose
		#define TypeChoose yes_no
	#endif
	#ifndef MAINDISPLAY_HEADER
		#define MAINDISPLAY_HEADER FULL_TYPE
	#endif
	#ifndef TypeConfirm
		#define TypeConfirm ok_cancel
	#endif
#else
	#ifndef ok_cancel
		#define ok_cancel TypeConfirm
	#endif
	#ifndef just_ok
		#define just_ok TypeOK
	#endif
	#ifndef yes_no
		#define yes_no TypeChoose
	#endif
	#ifndef FULL_TYPE
		#define FULL_TYPE MAINDISPLAY_HEADER
	#endif
#endif

//Define screen size
#if defined(EZX_E8) || defined(EZX_EM30)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#else
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#endif


#define FRAME_WIDTH 2
#define MARGIN_SPACE 5

#define LINE_HEIGHT ZGlobal::getLineHeight()
#define LINE_SPACE  ZGlobal::getLineSpace()

#define LEFT_X_SCROLL MARGIN_SPACE
#define LEFT_X MARGIN_SPACE+FRAME_WIDTH
#define TOP_Y 5
#define TOP_Y_WITH_TITLEBAR 26

#ifndef SET_MAIN_WIDGET
#define SET_MAIN_WIDGET(pWgt, Title) 		ZApplication* appSet = (ZApplication*)qApp;\
							                		appSet->setMainWidget(pWgt);
#endif

class GUIObjFilterClose : public QObject
{
        bool eventFilter(QObject *pObj, QEvent *pEvent)
        {
                if( pEvent->type() == QEvent::Close )
                {
                        delete this;
                        delete pObj;
                        return true;
                }

                return false;
        }
};
#ifndef DELETE_WIDGET_LATER
#define DELETE_WIDGET_LATER(pWgt)       GUIObjFilterClose *pFilter = new GUIObjFilterClose; \
                                        pWgt->installEventFilter( pFilter );\
                                        QApplication::postEvent( pWgt, new QCloseEvent );\
										if(qApp){qApp->wakeUpGuiThread(); }
#endif 

#ifndef MSG_ERR_ICON
#define MSG_ERR_ICON     "Dialog_Error.gif"
#endif

#ifndef MSG_OK_ICON
#define MSG_OK_ICON	"Dialog_Complete.gif"
#endif

#ifndef MSG_QUESTION_ICON
#define MSG_QUESTION_ICON "Dialog_Question_Mark.gif"
#endif

#ifndef MSG_WAIT_ICON
#define MSG_WAIT_ICON    "Dialog_Waiting.gif"
#endif

#endif //_H_SETUP_UI_DEFINE_H

