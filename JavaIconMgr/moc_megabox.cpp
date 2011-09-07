/****************************************************************************
** megabox meta object code from reading C++ file 'megabox.h'
**
** Created: Sat Mar 12 23:11:31 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "megabox.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *megabox::className() const
{
    return "megabox";
}

QMetaObject *megabox::metaObj = 0;

#ifdef QWS
static class megabox_metaObj_Unloader {
public:
    ~megabox_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "megabox" );
    }
} megabox_metaObj_unloader;
#endif

void megabox::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZKbMainWidget::className(), "ZKbMainWidget") != 0 )
	badSuperclassWarning("megabox","ZKbMainWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString megabox::tr(const char* s)
{
    return qApp->translate( "megabox", s, 0 );
}

QString megabox::tr(const char* s, const char * c)
{
    return qApp->translate( "megabox", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* megabox::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZKbMainWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (megabox::*m1_t0)(ZIconViewItem*);
    typedef void (QObject::*om1_t0)(ZIconViewItem*);
    typedef void (megabox::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (megabox::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (megabox::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (megabox::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (megabox::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (megabox::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (megabox::*m1_t7)();
    typedef void (QObject::*om1_t7)();
    typedef void (megabox::*m1_t8)();
    typedef void (QObject::*om1_t8)();
    m1_t0 v1_0 = &megabox::obj_click;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &megabox::slotQuit;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &megabox::slotAbout;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &megabox::app_props;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &megabox::mpkg_rename;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &megabox::mpkg_refresh;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &megabox::java_back_up;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &megabox::java_set_profile;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &megabox::mpkg_remove;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    QMetaData *slot_tbl = QMetaObject::new_metadata(9);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(9);
    slot_tbl[0].name = "obj_click(ZIconViewItem*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "slotQuit()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "slotAbout()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "app_props()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "mpkg_rename()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "mpkg_refresh()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "java_back_up()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "java_set_profile()";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "mpkg_remove()";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"megabox", "ZKbMainWidget",
	slot_tbl, 9,
	0, 0,
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
