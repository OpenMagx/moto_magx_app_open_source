#include <ZSingleSelectDlg.h>
#include <ZSingleCaptureDlg.h>

#include "iconSet.h"
#include "lng.h"

Lng *lng;

int main( int argc, char **argv)
{
    ZApplication *a = new ZApplication(argc, argv);
    
	bool mark = false;
	
	lng = new Lng();
	
	ZConfig cfg("/ezxlocal/download/appwrite/setup/ezx_idle.cfg");
	QString rskText = cfg.readEntry("Framework", "RSK_Text", "none");
	
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("FT_RSK"), lng->tr("FT_PLEASCHOOSE"));
	QStringList list;
	list += lng->tr("FT_TEXT_L");
	list += lng->tr("FT_TEXT_R");
	list += lng->tr("FT_IMG_R");

	dlg->addItemsList(list);
	
	if(dlg->exec() == ZPopup::Accepted) 
	{			
		int ret = dlg->getCheckedItemIndex();	
		delete dlg;
		dlg = NULL;
		if( ret == 0 || ret == 1 ) {			
			ZSingleCaptureDlg *sc = new ZSingleCaptureDlg( lng->tr("FT_RSK"), lng->tr("FT_INPUT_NAME"),
							 (ZSingleCaptureDlg::CaptureDlgType)0, NULL, "ZSingleCaptureDlg", true, 0, 0);
			ZLineEdit *line = sc->getLineEdit();
			line->setText(rskText);
			int i = sc->exec();	
			if( i == 1 ) {
				QString str = sc->getResultText().stripWhiteSpace();
				delete sc;
				sc = NULL;	
				if( ret == 0 ) {
					cfg.writeEntry("Framework", "LSK_Text", str );
					cfg.writeEntry("Framework", "LSK_GraphicName", "" );				
					cfg.flush();
					mark = true;	
				} else if ( ret == 1 ) {
					cfg.writeEntry("Framework", "RSK_Text", str );
					cfg.writeEntry("Framework", "RSK_GraphicName", "" );
					cfg.flush();
					mark = true;					
				
				}
			} else {
				delete sc;
				sc = NULL;
			}		
		} else if ( ret == 2 ) {
			iconSet *gui = new iconSet();//NULL, NULL);
			int i = gui->exec();
			if( i == 1 ) {
				QString icon = "";
				icon = gui->getIconItemName();
				delete gui;
				gui = NULL;
				if( icon != "" ) {
					cfg.writeEntry("Framework", "RSK_Text", "" );
					cfg.writeEntry("Framework", "RSK_GraphicName", icon );
					cfg.flush();
					mark = true;	
				}
			} else {
				delete gui;
				gui = NULL;			
			}
		} 
	} else {
		delete dlg;
		dlg = NULL;	
	}

	if( mark) {
		int ret = showQ( lng->tr("FT_CONFIRM"), lng->tr("FT_REFRESH_TO_USE"), 1 );
		if( ret == 1 )
			system( QString("kill `pidof phone`") );
		
	}
    delete a;
    return 0;
}


