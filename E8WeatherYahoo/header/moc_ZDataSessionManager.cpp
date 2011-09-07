/****************************************************************************
** ZDataSessionManager meta object code from reading C++ file 'ZDataSessionManager.h'
**
** Created: Thu Jan 13 20:25:37 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ZDataSessionManager.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *ZDataSessionManager::className() const
{
    return "ZDataSessionManager";
}

QMetaObject *ZDataSessionManager::metaObj = 0;

#ifdef QWS
static class ZDataSessionManager_metaObj_Unloader {
public:
    ~ZDataSessionManager_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "ZDataSessionManager" );
    }
} ZDataSessionManager_metaObj_unloader;
#endif

void ZDataSessionManager::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWSSocket::className(), "QWSSocket") != 0 )
	badSuperclassWarning("ZDataSessionManager","QWSSocket");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZDataSessionManager::tr(const char* s)
{
    return qApp->translate( "ZDataSessionManager", s, 0 );
}

QString ZDataSessionManager::tr(const char* s, const char * c)
{
    return qApp->translate( "ZDataSessionManager", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZDataSessionManager::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWSSocket::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (ZDataSessionManager::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (ZDataSessionManager::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (ZDataSessionManager::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &ZDataSessionManager::slotReadIndicator;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &ZDataSessionManager::slotLoseConnection;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &ZDataSessionManager::slotCancelBtnClicked;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "slotReadIndicator()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "slotLoseConnection()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    slot_tbl[2].name = "slotCancelBtnClicked()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Private;
    typedef void (ZDataSessionManager::*m2_t0)(int,ZLinkInfo&);
    typedef void (QObject::*om2_t0)(int,ZLinkInfo&);
    typedef void (ZDataSessionManager::*m2_t1)(int,unsigned short,unsigned short);
    typedef void (QObject::*om2_t1)(int,unsigned short,unsigned short);
    typedef void (ZDataSessionManager::*m2_t2)(int,ZLinkInfo&);
    typedef void (QObject::*om2_t2)(int,ZLinkInfo&);
    m2_t0 v2_0 = &ZDataSessionManager::connected;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &ZDataSessionManager::openFailed;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &ZDataSessionManager::broken;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    QMetaData *signal_tbl = QMetaObject::new_metadata(3);
    signal_tbl[0].name = "connected(int,ZLinkInfo&)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "openFailed(int,unsigned short,unsigned short)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "broken(int,ZLinkInfo&)";
    signal_tbl[2].ptr = (QMember)ov2_2;
    metaObj = QMetaObject::new_metaobject(
	"ZDataSessionManager", "QWSSocket",
	slot_tbl, 3,
	signal_tbl, 3,
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

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL connected
void ZDataSessionManager::connected( int t0, ZLinkInfo& t1 )
{
    // No builtin function for signal parameter type int,ZLinkInfo&
    QConnectionList *clist = receivers("connected(int,ZLinkInfo&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,ZLinkInfo&);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL openFailed
void ZDataSessionManager::openFailed( int t0, unsigned short t1, unsigned short t2 )
{
    // No builtin function for signal parameter type int,unsigned short,unsigned short
    QConnectionList *clist = receivers("openFailed(int,unsigned short,unsigned short)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,unsigned short);
    typedef void (QObject::*RT3)(int,unsigned short,unsigned short);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    RT3 r3;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	    case 3:
#ifdef Q_FP_CCAST_BROKEN
		r3 = reinterpret_cast<RT3>(*(c->member()));
#else
		r3 = (RT3)*(c->member());
#endif
		(object->*r3)(t0, t1, t2);
		break;
	}
    }
}

// SIGNAL broken
void ZDataSessionManager::broken( int t0, ZLinkInfo& t1 )
{
    // No builtin function for signal parameter type int,ZLinkInfo&
    QConnectionList *clist = receivers("broken(int,ZLinkInfo&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,ZLinkInfo&);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}
