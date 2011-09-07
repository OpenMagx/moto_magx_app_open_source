/****************************************************************************
** CitySelectDlg meta object code from reading C++ file 'citySelectDlg.h'
**
** Created: Thu Jan 13 20:25:36 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "citySelectDlg.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *CitySelectDlg::className() const
{
    return "CitySelectDlg";
}

QMetaObject *CitySelectDlg::metaObj = 0;

#ifdef QWS
static class CitySelectDlg_metaObj_Unloader {
public:
    ~CitySelectDlg_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "CitySelectDlg" );
    }
} CitySelectDlg_metaObj_unloader;
#endif

void CitySelectDlg::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZPopup::className(), "ZPopup") != 0 )
	badSuperclassWarning("CitySelectDlg","ZPopup");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString CitySelectDlg::tr(const char* s)
{
    return qApp->translate( "CitySelectDlg", s, 0 );
}

QString CitySelectDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "CitySelectDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* CitySelectDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZPopup::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (CitySelectDlg::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (CitySelectDlg::*m1_t1)(ZSettingItem*);
    typedef void (QObject::*om1_t1)(ZSettingItem*);
    m1_t0 v1_0 = &CitySelectDlg::slotSelected;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &CitySelectDlg::slotItemClicked;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "slotSelected()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Private;
    slot_tbl[1].name = "slotItemClicked(ZSettingItem*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Private;
    metaObj = QMetaObject::new_metaobject(
	"CitySelectDlg", "ZPopup",
	slot_tbl, 2,
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
