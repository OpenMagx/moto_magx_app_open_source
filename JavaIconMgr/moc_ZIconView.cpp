/****************************************************************************
** ZIconView meta object code from reading C++ file 'ZIconView.h'
**
** Created: Sat Mar 12 23:11:28 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "ZIconView.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *ZIconView::className() const
{
    return "ZIconView";
}

QMetaObject *ZIconView::metaObj = 0;

#ifdef QWS
static class ZIconView_metaObj_Unloader {
public:
    ~ZIconView_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "ZIconView" );
    }
} ZIconView_metaObj_unloader;
#endif

void ZIconView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZScrollPanel::className(), "ZScrollPanel") != 0 )
	badSuperclassWarning("ZIconView","ZScrollPanel");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZIconView::tr(const char* s)
{
    return qApp->translate( "ZIconView", s, 0 );
}

QString ZIconView::tr(const char* s, const char * c)
{
    return qApp->translate( "ZIconView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZIconView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZScrollPanel::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (ZIconView::*m1_t0)(const QSize&,bool);
    typedef void (QObject::*om1_t0)(const QSize&,bool);
    typedef void (ZIconView::*m1_t1)(bool);
    typedef void (QObject::*om1_t1)(bool);
    typedef void (ZIconView::*m1_t2)(int,int);
    typedef void (QObject::*om1_t2)(int,int);
    typedef void (ZIconView::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (ZIconView::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (ZIconView::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (ZIconView::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (ZIconView::*m1_t7)(int,int);
    typedef void (QObject::*om1_t7)(int,int);
    typedef void (ZIconView::*m1_t8)();
    typedef void (QObject::*om1_t8)();
    m1_t0 v1_0 = &ZIconView::arrangeItemsInGrid;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &ZIconView::arrangeItemsInGrid;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &ZIconView::setContentsPos;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &ZIconView::updateContents;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &ZIconView::ensureCurrentVisible;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &ZIconView::adjustItems;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &ZIconView::slotUpdate;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &ZIconView::movedContents;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &ZIconView::slotWaitWrapFinished;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    QMetaData *slot_tbl = QMetaObject::new_metadata(9);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(9);
    slot_tbl[0].name = "arrangeItemsInGrid(const QSize&,bool)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "arrangeItemsInGrid(bool)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "setContentsPos(int,int)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "updateContents()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "ensureCurrentVisible()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "adjustItems()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Protected;
    slot_tbl[6].name = "slotUpdate()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Protected;
    slot_tbl[7].name = "movedContents(int,int)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Private;
    slot_tbl[8].name = "slotWaitWrapFinished()";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Private;
    typedef void (ZIconView::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    typedef void (ZIconView::*m2_t1)(ZIconViewItem*);
    typedef void (QObject::*om2_t1)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t2)(ZIconViewItem*);
    typedef void (QObject::*om2_t2)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t3)(ZIconViewItem*);
    typedef void (QObject::*om2_t3)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t4)(ZIconViewItem*,const QPoint&);
    typedef void (QObject::*om2_t4)(ZIconViewItem*,const QPoint&);
    typedef void (ZIconView::*m2_t5)(ZIconViewItem*);
    typedef void (QObject::*om2_t5)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t6)(ZIconViewItem*,const QPoint&);
    typedef void (QObject::*om2_t6)(ZIconViewItem*,const QPoint&);
    typedef void (ZIconView::*m2_t7)(ZIconViewItem*);
    typedef void (QObject::*om2_t7)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t8)(ZIconViewItem*);
    typedef void (QObject::*om2_t8)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t9)(ZIconViewItem*,const QPoint&);
    typedef void (QObject::*om2_t9)(ZIconViewItem*,const QPoint&);
    typedef void (ZIconView::*m2_t10)(ZIconViewItem*,const QPoint&);
    typedef void (QObject::*om2_t10)(ZIconViewItem*,const QPoint&);
    typedef void (ZIconView::*m2_t11)(int,ZIconViewItem*,const QPoint&);
    typedef void (QObject::*om2_t11)(int,ZIconViewItem*,const QPoint&);
    typedef void (ZIconView::*m2_t12)(int,ZIconViewItem*,const QPoint&);
    typedef void (QObject::*om2_t12)(int,ZIconViewItem*,const QPoint&);
    typedef void (ZIconView::*m2_t13)();
    typedef void (QObject::*om2_t13)();
    typedef void (ZIconView::*m2_t14)(ZIconViewItem*);
    typedef void (QObject::*om2_t14)(ZIconViewItem*);
    typedef void (ZIconView::*m2_t15)();
    typedef void (QObject::*om2_t15)();
    m2_t0 v2_0 = &ZIconView::selectionChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &ZIconView::selectionChanged;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &ZIconView::currentChanged;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    m2_t3 v2_3 = &ZIconView::clicked;
    om2_t3 ov2_3 = (om2_t3)v2_3;
    m2_t4 v2_4 = &ZIconView::clicked;
    om2_t4 ov2_4 = (om2_t4)v2_4;
    m2_t5 v2_5 = &ZIconView::pressed;
    om2_t5 ov2_5 = (om2_t5)v2_5;
    m2_t6 v2_6 = &ZIconView::pressed;
    om2_t6 ov2_6 = (om2_t6)v2_6;
    m2_t7 v2_7 = &ZIconView::doubleClicked;
    om2_t7 ov2_7 = (om2_t7)v2_7;
    m2_t8 v2_8 = &ZIconView::returnPressed;
    om2_t8 ov2_8 = (om2_t8)v2_8;
    m2_t9 v2_9 = &ZIconView::rightButtonClicked;
    om2_t9 ov2_9 = (om2_t9)v2_9;
    m2_t10 v2_10 = &ZIconView::rightButtonPressed;
    om2_t10 ov2_10 = (om2_t10)v2_10;
    m2_t11 v2_11 = &ZIconView::mouseButtonPressed;
    om2_t11 ov2_11 = (om2_t11)v2_11;
    m2_t12 v2_12 = &ZIconView::mouseButtonClicked;
    om2_t12 ov2_12 = (om2_t12)v2_12;
    m2_t13 v2_13 = &ZIconView::moved;
    om2_t13 ov2_13 = (om2_t13)v2_13;
    m2_t14 v2_14 = &ZIconView::onItem;
    om2_t14 ov2_14 = (om2_t14)v2_14;
    m2_t15 v2_15 = &ZIconView::onViewport;
    om2_t15 ov2_15 = (om2_t15)v2_15;
    QMetaData *signal_tbl = QMetaObject::new_metadata(16);
    signal_tbl[0].name = "selectionChanged()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "selectionChanged(ZIconViewItem*)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "currentChanged(ZIconViewItem*)";
    signal_tbl[2].ptr = (QMember)ov2_2;
    signal_tbl[3].name = "clicked(ZIconViewItem*)";
    signal_tbl[3].ptr = (QMember)ov2_3;
    signal_tbl[4].name = "clicked(ZIconViewItem*,const QPoint&)";
    signal_tbl[4].ptr = (QMember)ov2_4;
    signal_tbl[5].name = "pressed(ZIconViewItem*)";
    signal_tbl[5].ptr = (QMember)ov2_5;
    signal_tbl[6].name = "pressed(ZIconViewItem*,const QPoint&)";
    signal_tbl[6].ptr = (QMember)ov2_6;
    signal_tbl[7].name = "doubleClicked(ZIconViewItem*)";
    signal_tbl[7].ptr = (QMember)ov2_7;
    signal_tbl[8].name = "returnPressed(ZIconViewItem*)";
    signal_tbl[8].ptr = (QMember)ov2_8;
    signal_tbl[9].name = "rightButtonClicked(ZIconViewItem*,const QPoint&)";
    signal_tbl[9].ptr = (QMember)ov2_9;
    signal_tbl[10].name = "rightButtonPressed(ZIconViewItem*,const QPoint&)";
    signal_tbl[10].ptr = (QMember)ov2_10;
    signal_tbl[11].name = "mouseButtonPressed(int,ZIconViewItem*,const QPoint&)";
    signal_tbl[11].ptr = (QMember)ov2_11;
    signal_tbl[12].name = "mouseButtonClicked(int,ZIconViewItem*,const QPoint&)";
    signal_tbl[12].ptr = (QMember)ov2_12;
    signal_tbl[13].name = "moved()";
    signal_tbl[13].ptr = (QMember)ov2_13;
    signal_tbl[14].name = "onItem(ZIconViewItem*)";
    signal_tbl[14].ptr = (QMember)ov2_14;
    signal_tbl[15].name = "onViewport()";
    signal_tbl[15].ptr = (QMember)ov2_15;
    metaObj = QMetaObject::new_metaobject(
	"ZIconView", "ZScrollPanel",
	slot_tbl, 9,
	signal_tbl, 16,
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

// SIGNAL selectionChanged
void ZIconView::selectionChanged()
{
    activate_signal( "selectionChanged()" );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL selectionChanged
void ZIconView::selectionChanged( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("selectionChanged(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL currentChanged
void ZIconView::currentChanged( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("currentChanged(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL clicked
void ZIconView::clicked( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("clicked(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL clicked
void ZIconView::clicked( ZIconViewItem* t0, const QPoint& t1 )
{
    // No builtin function for signal parameter type ZIconViewItem*,const QPoint&
    QConnectionList *clist = receivers("clicked(ZIconViewItem*,const QPoint&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    typedef void (QObject::*RT2)(ZIconViewItem*,const QPoint&);
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

// SIGNAL pressed
void ZIconView::pressed( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("pressed(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL pressed
void ZIconView::pressed( ZIconViewItem* t0, const QPoint& t1 )
{
    // No builtin function for signal parameter type ZIconViewItem*,const QPoint&
    QConnectionList *clist = receivers("pressed(ZIconViewItem*,const QPoint&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    typedef void (QObject::*RT2)(ZIconViewItem*,const QPoint&);
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

// SIGNAL doubleClicked
void ZIconView::doubleClicked( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("doubleClicked(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL returnPressed
void ZIconView::returnPressed( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("returnPressed(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL rightButtonClicked
void ZIconView::rightButtonClicked( ZIconViewItem* t0, const QPoint& t1 )
{
    // No builtin function for signal parameter type ZIconViewItem*,const QPoint&
    QConnectionList *clist = receivers("rightButtonClicked(ZIconViewItem*,const QPoint&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    typedef void (QObject::*RT2)(ZIconViewItem*,const QPoint&);
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

// SIGNAL rightButtonPressed
void ZIconView::rightButtonPressed( ZIconViewItem* t0, const QPoint& t1 )
{
    // No builtin function for signal parameter type ZIconViewItem*,const QPoint&
    QConnectionList *clist = receivers("rightButtonPressed(ZIconViewItem*,const QPoint&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    typedef void (QObject::*RT2)(ZIconViewItem*,const QPoint&);
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

// SIGNAL mouseButtonPressed
void ZIconView::mouseButtonPressed( int t0, ZIconViewItem* t1, const QPoint& t2 )
{
    // No builtin function for signal parameter type int,ZIconViewItem*,const QPoint&
    QConnectionList *clist = receivers("mouseButtonPressed(int,ZIconViewItem*,const QPoint&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,ZIconViewItem*);
    typedef void (QObject::*RT3)(int,ZIconViewItem*,const QPoint&);
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

// SIGNAL mouseButtonClicked
void ZIconView::mouseButtonClicked( int t0, ZIconViewItem* t1, const QPoint& t2 )
{
    // No builtin function for signal parameter type int,ZIconViewItem*,const QPoint&
    QConnectionList *clist = receivers("mouseButtonClicked(int,ZIconViewItem*,const QPoint&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,ZIconViewItem*);
    typedef void (QObject::*RT3)(int,ZIconViewItem*,const QPoint&);
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

// SIGNAL moved
void ZIconView::moved()
{
    activate_signal( "moved()" );
}

// SIGNAL onItem
void ZIconView::onItem( ZIconViewItem* t0 )
{
    // No builtin function for signal parameter type ZIconViewItem*
    QConnectionList *clist = receivers("onItem(ZIconViewItem*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(ZIconViewItem*);
    RT0 r0;
    RT1 r1;
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
	}
    }
}

// SIGNAL onViewport
void ZIconView::onViewport()
{
    activate_signal( "onViewport()" );
}
