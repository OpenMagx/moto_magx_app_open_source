/****************************************************************************
** U2Panel meta object code from reading C++ file 'U2Panel.h'
**
** Created: Wed May 25 15:15:53 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "../U2Panel.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *U2Panel::className() const
{
    return "U2Panel";
}

QMetaObject *U2Panel::metaObj = 0;

#ifdef QWS
static class U2Panel_metaObj_Unloader {
public:
    ~U2Panel_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "U2Panel" );
    }
} U2Panel_metaObj_unloader;
#endif

void U2Panel::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("U2Panel","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString U2Panel::tr(const char* s)
{
    return qApp->translate( "U2Panel", s, 0 );
}

QString U2Panel::tr(const char* s, const char * c)
{
    return qApp->translate( "U2Panel", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* U2Panel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (U2Panel::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &U2Panel::updateCursor;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "updateCursor()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    typedef void (U2Panel::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    typedef void (U2Panel::*m2_t1)();
    typedef void (QObject::*om2_t1)();
    typedef void (U2Panel::*m2_t2)();
    typedef void (QObject::*om2_t2)();
    typedef void (U2Panel::*m2_t3)();
    typedef void (QObject::*om2_t3)();
    m2_t0 v2_0 = &U2Panel::Input_Accepted;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &U2Panel::Output_Rejected;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &U2Panel::accepted;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    m2_t3 v2_3 = &U2Panel::rejected;
    om2_t3 ov2_3 = (om2_t3)v2_3;
    QMetaData *signal_tbl = QMetaObject::new_metadata(4);
    signal_tbl[0].name = "Input_Accepted()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "Output_Rejected()";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "accepted()";
    signal_tbl[2].ptr = (QMember)ov2_2;
    signal_tbl[3].name = "rejected()";
    signal_tbl[3].ptr = (QMember)ov2_3;
    metaObj = QMetaObject::new_metaobject(
	"U2Panel", "QWidget",
	slot_tbl, 1,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

// SIGNAL Input_Accepted
void U2Panel::Input_Accepted()
{
    activate_signal( "Input_Accepted()" );
}

// SIGNAL Output_Rejected
void U2Panel::Output_Rejected()
{
    activate_signal( "Output_Rejected()" );
}

// SIGNAL accepted
void U2Panel::accepted()
{
    activate_signal( "accepted()" );
}

// SIGNAL rejected
void U2Panel::rejected()
{
    activate_signal( "rejected()" );
}
