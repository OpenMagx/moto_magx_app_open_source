/****************************************************************************
** MarsDialog meta object code from reading C++ file 'MarsDialog.h'
**
** Created: Wed May 25 15:15:52 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "../MarsDialog.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *MarsDialog::className() const
{
    return "MarsDialog";
}

QMetaObject *MarsDialog::metaObj = 0;

#ifdef QWS
static class MarsDialog_metaObj_Unloader {
public:
    ~MarsDialog_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "MarsDialog" );
    }
} MarsDialog_metaObj_unloader;
#endif

void MarsDialog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("MarsDialog","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MarsDialog::tr(const char* s)
{
    return qApp->translate( "MarsDialog", s, 0 );
}

QString MarsDialog::tr(const char* s, const char * c)
{
    return qApp->translate( "MarsDialog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MarsDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"MarsDialog", "QDialog",
	0, 0,
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
