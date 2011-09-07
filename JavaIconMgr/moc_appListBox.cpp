/****************************************************************************
** appListBox meta object code from reading C++ file 'appListBox.h'
**
** Created: Sat Mar 12 23:11:29 2011
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.8   edited 2004-08-05 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "appListBox.h"
#include <qmetaobject.h>
#include <qapplication.h>
#ifdef QWS
#include <qobjectdict.h>
#endif



const char *appListBox::className() const
{
    return "appListBox";
}

QMetaObject *appListBox::metaObj = 0;

#ifdef QWS
static class appListBox_metaObj_Unloader {
public:
    ~appListBox_metaObj_Unloader()
    {
         if ( objectDict )
             objectDict->remove( "appListBox" );
    }
} appListBox_metaObj_unloader;
#endif

void appListBox::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(ZIconView::className(), "ZIconView") != 0 )
	badSuperclassWarning("appListBox","ZIconView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString appListBox::tr(const char* s)
{
    return qApp->translate( "appListBox", s, 0 );
}

QString appListBox::tr(const char* s, const char * c)
{
    return qApp->translate( "appListBox", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* appListBox::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) ZIconView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"appListBox", "ZIconView",
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
