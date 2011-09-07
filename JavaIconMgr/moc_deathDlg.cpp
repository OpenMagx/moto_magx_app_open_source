/****************************************************************************
** deathDlg meta object code from reading C++ file 'deathDlg.h'
**
** Created: Sat Mar 12 23:11:30 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "deathDlg.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *deathDlg::className() const
{
    return "deathDlg";
}

QMetaObject *deathDlg::metaObj = 0;

#ifdef QWS
static class deathDlg_metaObj_Unloader {
public:
    ~deathDlg_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "deathDlg" );
    }
} deathDlg_metaObj_unloader;
#endif

void deathDlg::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZPopup::className(), "ZPopup") != 0 )
	badSuperclassWarning("deathDlg","ZPopup");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString deathDlg::tr(const char* s)
{
    return qApp->translate( "deathDlg", s, 0 );
}

QString deathDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "deathDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* deathDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZPopup::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (deathDlg::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &deathDlg::system_exec;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "system_exec()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"deathDlg", "ZPopup",
	slot_tbl, 1,
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
