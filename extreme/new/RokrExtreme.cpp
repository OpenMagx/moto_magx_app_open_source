
#include <ZMessageDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZNoticeDlg.h>
#include <ZSingleCaptureDlg.h>
#include <ZConfig.h>
//#include <ZSMS.h>

#include <qtextcodec.h>
#include <qfile.h>
#include <qdir.h>

#include "RokrExtreme.h"
#include "lng.h"
#include "deathDlg.h"
#ifndef USE_NOTEPAD
#include "txtReader.h"
#endif
#include "fontView.h"
#include "showPic.h"
#include "UtilsTools.h"
#include "UtilsCode.h"


RokrExtreme::RokrExtreme(int argc, char **argv) : ZApplication(argc, argv)
{
	loadConfig();
	lng = new Lng();

	QDir cardDir = QDir("/mmc/mmca1/.system");
	if ( cardDir.exists() == true ) 
		CardExist = true;
	else 
		CardExist = false;
	
    
	QDir p7zDir(cfgP7zPath );
	if ( !p7zDir.exists() ) {
		showNotify(lng->tr("POP_ERROR"), lng->tr("POP_NO_7Z"), 2, 2);
		printf("Debug: 7z not exist!\n");
		::exit(1);
	}
	
	int cutPoint = basename(argv[2]);
	sprintf(filename, argv[2]+cutPoint);
	sprintf(dirname, argv[2]);
	dirname[cutPoint-1] = '\0';
	
	printf("==== %s ==== \n", filename);
	
	QFile myfile( ctr(argv[2]) );
	if( !myfile.exists() ) {
		showQ( lng->tr("POP_ERROR"), lng->tr("FT_INVALID"), 2);
		::exit(1);	
	}	
	if(myfile.size()>50000000)
	{
		int ret = showQ(lng->tr("POP_BIGFILE_TITLE"), lng->tr("POP_BIGFILE_TEXT")+ctr(filename)+" ?", 1);
		if ( ret != 1 )
			::exit(0);
	}	
	
	int i=0;
	for(i=0; filename[i]!='\0'; i++) {
		if(filename[i]=='.') {
			cutPoint=i;
			break;
		}
	}
	filename[cutPoint]='\0';
	printf("==== %s ==== \n", filename);
	
	myPath = getAppDir();
	qsFilePath = ctr(argv[2]);
	sprintf(argFile, argv[2]); 
	

	fileType = getFileType( argv[2] );
	
	switch(fileType) {
		case FILE_PACKAGE:
			packageCore();
			break;
		case FILE_SCRIPT:
			scriptCore();
			break;
		case FILE_THEME:
			themeCore();
			break;
		#ifndef VE66
		case FILE_IMS:
			iMarsCore();
			break;
		#endif
		case FILE_FONT:
			fontCore();
			break;
		case FILE_KM:
			km_qkt_Core( FILE_KM );
			break;
		case FILE_QKT:
			km_qkt_Core( FILE_QKT );
			break;
		case FILE_LOGO:
			logoCore();
			break;
		case FILE_MEDIA:
			mediaCore();
			break;
		case FILE_TEXT:
			textCore();
			break;
		case NONE_TYPE:
		default :
			otherCore();
			break;	
	}	
	
	::exit(0);	
}
RokrExtreme::~RokrExtreme()
{
	delete lng;
	lng = NULL;
}

RokrExtreme::FILE_TYPE RokrExtreme::getFileType( const char *path )
{
	QString filePath = QString(path);

	filePath = filePath.remove( 0, filePath.findRev("/")+1 );
	filePath = filePath.remove( 0, filePath.findRev(".")+1 );
	
	filePath = ( QString(".%1").arg(filePath) ).lower();
	
	if (  filePath == ".7z" || filePath == ".zip" || filePath == ".tar" || 
		  filePath == ".gz" || filePath == ".bz2" || filePath == ".rar" ||
		  filePath == ".cab" || filePath == ".iso" || filePath == ".arg" ||
		  filePath == ".z" ) 
		return FILE_PACKAGE;
	
	if ( filePath == ".lin" || filePath == ".sh" )
		return FILE_SCRIPT;
		
	if ( filePath == ".mgs" )
		return FILE_THEME;
	#ifndef VE66
	if ( filePath == ".ims" )
		return FILE_IMS;
	#endif	
		
	if ( filePath == ".ttf" || filePath == ".ttc" )
		return FILE_FONT;
	
	if ( filePath == ".km" )
		return FILE_KM;
	
	if ( filePath == ".qkt" )
		return FILE_QKT;
	
	if ( QString(".bmp%1").arg(filePath) == ".bmp.logo" )
		return FILE_LOGO;

	if ( filePath == ".flv" || filePath == ".avi" || filePath == ".flac" || filePath == ".vob")
		return FILE_MEDIA;		
	if ( filePath == ".txt" || filePath == ".cfg" || filePath == ".chm" || 
		 filePath == ".ini" || filePath == ".conf" || filePath == ".c" ||
		 filePath == ".cc" || filePath == ".cpp" || filePath == ".h" ||
		 filePath == ".hh" || filePath == ".java" || filePath == ".lng" || 
		 filePath == ".desktop" || filePath == ".log" || filePath == ".pro")
		return FILE_TEXT;
		
	return NONE_TYPE;	
}

void RokrExtreme::themeChk()
{
	int i;
	char buf[1024];
	
	QStringList entries;
	QStringList::ConstIterator p;
	
	QString path[] = {cfgSkin_phone, cfgSkin_part2};
	for (i = 0; i <= 1; i++)
	{
		QString spath = path[i];
		QDir skinDir(spath);
		
		if ( !skinDir.exists() ) { 
		    std::cout<<spath<<" not exist !"<<std::cout;
			continue;
		}
	    
	    skinDir.setFilter(QDir::Dirs);        
		if (skinDir.isReadable())
	    {
 		    entries = skinDir.entryList();
		    entries.sort();
		    p = entries.begin();
			for (p = entries.begin(); p != entries.end(); ++p ) 
		    {
		        if(*p != "." && *p != "..")
			    {		
                    QString curSkinPath = spath+"/"+*p;             
					QString chmFile = curSkinPath+"/"+*p+".chm"; 
					#ifdef VE66
					QString destFile = "/ezxlocal/download/appwrite/setup/theme/"+*p+".phm";
					#else
					QString destFile = "/ezxlocal/download/appwrite/setuptheme/"+*p+".chm";
					#endif
      
					std::cout<<"cur chm file path is "<<chmFile<<std::endl;
					QFile file(chmFile);
                    if( file.exists() )
					{
					    std::cout<<"chm file exists "<<std::endl;
						
						/*if ( file.open( IO_ReadOnly ) ) 
						{
							QTextCodec *codec = NULL;
							UtilsCode *utilsCode = new UtilsCode(chmFile);
							if( utilsCode->detectFileCodec() ) {
								codec = utilsCode->getCodec();
							} else {
								codec = QTextCodec::codecForName("UTF-8");
							}
							delete utilsCode;
							utilsCode = NULL;
							
							char data[file.size()+1];
							
							file.readBlock(data, sizeof(data));
							file.close();
							
							QString str = QString( codec->toUnicode(data) );
							QFile f(destFile);
							if( !f.exists() ) {
								if( f.open(IO_WriteOnly) ) {
									f.writeBlock( (const char*)str.local8Bit(),  sizeof( (const char*)str.local8Bit() ) );
									f.flush();
									f.close();							
								}							
							}					
						}*/
						//else
						//{
							sprintf(buf, "cp -fR '%s' '%s' ; chmod 777 '%s'",
										(const char *)chmFile.utf8(), (const char *)destFile.utf8(), (const char *)destFile.utf8());
							printf("exec buf is %s\n", buf);
							system(buf);	
						//}
						//
						ZConfig cfg(destFile);
						cfg.writeEntry(QString("THEME_CONFIG_TABLE"), QString("Skin"), QString(curSkinPath));
						cfg.writeEntry(QString("THEME_CONFIG_TABLE"), QString("ThemeName"), QString(*p));
					}
			    }
			}
		}
	}

}

void RokrExtreme::loadConfig()
{
	ZConfig cfg( getAppDir()+"/RokrExtreme.cfg");
	
	cfgP7zPath = cfg.readEntry("CFG", "p7z", "");
	cfgSkin_phone = cfg.readEntry("CFG", "skin_phone", "");
	cfgSkin_part2 = cfg.readEntry("CFG", "skin_part2", "");
	cfgTxtEditorPath = cfg.readEntry("CFG", "text_editor", "");
	//cfgKmTargetPath = cfg.readEntry("CFG", "km_path", "");
	//cfgQktTargetPath = cfg.readEntry("CFG", "qkt_path", "");
	cfgMPlayerPath = cfg.readEntry("CFG", "mp_path", "");
	cfgMPSrcPath = cfg.readEntry("CFG", "mp_src", "");
	cfgMPDestPath = cfg.readEntry("CFG", "mp_destPath", "");
	
	cfgLogoConvPath = cfg.readEntry("CFG", "logoConv_path", "");
	cfgFlashcpPath = cfg.readEntry("CFG", "flashcp_path", "");
	cfgMarsSkinPath = cfg.readEntry("CFG", "marsSkin_path", "");
	
	//cout<<cfgP7zPath<<endl;	
	//cout<<cfgSkin_phone<<endl;	
	//cout<<cfgSkin_part2<<endl;	
	//cout<<cfgLogoConvPath<<endl;	
	//cout<<cfgFlashcpPath<<endl;	
	//cout<<cfgP7zPath<<endl;		
}

void RokrExtreme::packageCore()
{
	ZSingleSelectDlg *ssDlg = new ZSingleSelectDlg(lng->tr("POP_PACKAGE_OPTINON"), lng->tr("FT_PLEASCHOOSE"));
	QStringList strlist;
	strlist += lng->tr("FT_EXTRACT_HERE");
	strlist += lng->tr("FT_EXTRACT_PH");			
	if (CardExist) strlist += lng->tr("FT_EXTRACT_SD"); 			
	ssDlg->addItemsList(strlist);
	
	if(ssDlg->exec() == ZPopup::Accepted) 
	{			
		int ret = ssDlg->getCheckedItemIndex();
		delete ssDlg;
		ssDlg = NULL;

		switch(ret) {
			case 0:
				sprintf(exec_buffer, "mkdir -p '%s/%s'", dirname, filename);
				printf("Debug: system(%s)\n", exec_buffer);
				system(exec_buffer);  
				
				sprintf(exec_buffer, "%s/7z x '%s' -o'%s/%s' -y", 
						(const char*)cfgP7zPath.local8Bit(), argFile, dirname, filename);
				break;							
			case 1:
				sprintf(exec_buffer, "%s/7z x '%s' -o'/ezxlocal/download/mystuff' -y", 
						(const char*)cfgP7zPath.local8Bit(), argFile);
				break;						
			case 2:					
				sprintf(exec_buffer, "%s/7z x '%s' -o'/mmc/mmca1' -y", 
					(const char*)cfgP7zPath.local8Bit(), argFile);
				break;
			default :
				break;
		}	
		ret = 255;
		QString title = lng->tr("POP_DECOMPRESSING");
		QString text = lng->tr("POP_PLEASE_WAIT");
		
		deathDlg *dDlg = new deathDlg(title, text, exec_buffer);
		dDlg->exec();
		ret = dDlg->ret;
		delete dDlg;
		dDlg = NULL;
		
		if( ret == 0)  {
			showQ( lng->tr("POP_OK"), lng->tr("FT_DECOMPRESSION_OK"), 2);	
			::exit(0);
		}	
		::exit(1);
	}
	else
	{
		delete ssDlg;
		ssDlg = NULL;
		::exit(1);
	}
}
void RokrExtreme::scriptCore()
{
	ZSingleSelectDlg *ssDlg = new ZSingleSelectDlg(lng->tr("POP_SCRIPT_OPTION"), lng->tr("FT_PLEASCHOOSE"));
	QStringList strlist;
	QString text = QString::null;
	strlist += lng->tr("FT_RUN");
	strlist += lng->tr("FT_VIEW");
	strlist += lng->tr("FT_EDIT");
	strlist += lng->tr("FT_RUN_WITH_PARAMETER");
	ssDlg->addItemsList(strlist);
	if(ssDlg->exec() == ZPopup::Accepted) 
	{			
		int ret = ssDlg->getCheckedItemIndex();
		delete ssDlg;
		ssDlg = NULL;
		switch(ret) {
			case 0:
				sprintf(exec_buffer,"chmod +x '%s'; . /etc/initservices/services/ezxenv.sh; exec '%s' &", argFile, argFile);
				printf("Debug: system %s\n", exec_buffer);
				system(exec_buffer);
				break;
			case 1:
				#ifdef USE_NOTEPAD
				sprintf(exec_buffer,"exec /usr/SYSqtapp/notepad/notepad -d %s &", argFile);
				printf("Debug: system %s\n", exec_buffer);
				system(exec_buffer);
				#else
				reader *r = new reader( qsFilePath);
				r->exec();
				delete r;
				r= NULL;
				#endif
				break;
			case 2:
				sprintf(exec_buffer, "exec '%s' -d '%s' &", (const char *)cfgTxtEditorPath.local8Bit(), argFile);
				printf("Debug: system%s\n", exec_buffer);
				system(exec_buffer);
				break;
			case 3:
				ZSingleCaptureDlg *sc = new ZSingleCaptureDlg(lng->tr("FT_RUN_WITH_PARAMETER"), "",
							 (ZSingleCaptureDlg::CaptureDlgType)0, NULL, "ZSingleCaptureDlg", true, 0, 0);
				sc->exec();
				text = sc->getResultText();
				delete sc;
				sc = NULL;	
				
				sprintf(exec_buffer,"chmod +x '%s'; . /etc/initservices/services/ezxenv.sh; exec '%s' %s &", 
									 argFile, argFile, (const char*)text.local8Bit() );
				printf("Debug: system%s\n", exec_buffer);
				system(exec_buffer);
				break;	
			default :
				break;
		}	
		::exit(0);
	}
	else
	{
		delete ssDlg;
		ssDlg = NULL;
		::exit(1);
	}
}
void RokrExtreme::themeCore()
{
	ZSingleSelectDlg *ssDlg = new ZSingleSelectDlg(lng->tr("POP_SKIN"), lng->tr("FT_PLEASCHOOSE"));
	QStringList strlist;
	strlist += lng->tr("FT_PHONE");
	QDir skin_dir2( cfgSkin_part2 );
	if ( skin_dir2.exists() && !df2MtdFreeSize(QString("/mmc/mmca2"), (unsigned int)5000) )
		strlist += lng->tr("FT_PART2");
	ssDlg->addItemsList(strlist);	
	if(ssDlg->exec() == ZPopup::Accepted) 
	{			
		int ret = ssDlg->getCheckedItemIndex();
		delete ssDlg;
		ssDlg = NULL;

		switch(ret) {
			case 0:
				sprintf(exec_buffer,"%s/7z x '%s' -o'%s' -y",
						(const char*)cfgP7zPath.local8Bit(), argFile, (const char*)cfgSkin_phone.local8Bit() );
				break;
			case 1:
				sprintf(exec_buffer,"%s/7z x '%s' -o'%s' -y", 
						(const char*)cfgP7zPath.local8Bit(), argFile, (const char*)cfgSkin_part2.local8Bit() );
				break;
			default:
				break;				
		}
		ret =255;
		QString title = lng->tr("POP_INSTALLING");
		QString text = lng->tr("POP_PLEASE_WAIT");
		deathDlg *dDlg = new deathDlg(title, text, exec_buffer);
		dDlg->exec();
		ret = dDlg->ret;
		delete dDlg;
		dDlg = NULL;
		
		if( ret == 0)  {
			printf("start chk chm \n");
			themeChk();
			showQ( lng->tr("POP_OK"), lng->tr("FT_SKIN_INSTALL_OK"), 2);	
			::exit(0);
		}	
		::exit(1);
	}
	else
	{
		delete ssDlg;
		ssDlg = NULL;
		::exit(1);
	}	

}
#ifndef VE66
void RokrExtreme::iMarsCore()
{
	QString title = lng->tr("FT_MARS_SKIN");
	QString text = lng->tr("FT_CONFIRM_INSTALL");
	int ret = showQ(title, text, 1);
	if ( ret != 1 ) 
		::exit(0);
	
	text = lng->tr("POP_PLEASE_WAIT");
	ret = 255;
	sprintf(exec_buffer,"%s/7z x '%s' -o'%s' -y", 
		(const char*)cfgP7zPath.local8Bit(), argFile, (const char*)cfgMarsSkinPath.local8Bit() );
		
	deathDlg *dDlg = new deathDlg(title, text, exec_buffer);
	dDlg->exec();
	ret = dDlg->ret;
	delete dDlg;
	dDlg = NULL;
	
	if( ret == 0)  {
		showNotify( lng->tr("FT_MARS_SKIN"), lng->tr("FT_SKIN_INSTALL_OK"), 2);	
		::exit(0);
	}	
	::exit(1);	
}
#endif
void RokrExtreme::fontCore()
{
	fontView *v = new fontView( ctr(argFile) );
	v->exec();
	delete v;
	v=NULL;	
	::exit(0);
}
void RokrExtreme::km_qkt_Core( FILE_TYPE fileType )
{
	QString title, text;
	if( fileType == FILE_KM ) {
		title = lng->tr("POP_KM_OPTION");
		text = lng->tr("FT_KM_INFO");	
	} else {
		title = lng->tr("POP_QKT_OPTION");
		text = lng->tr("FT_QKT_INFO");	
	}
	
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("POP_KM_OPTION"), lng->tr("FT_KM_INFO"));		
	QStringList strlist;
	strlist += lng->tr("FT_VIEW");
	strlist += lng->tr("FT_EDIT");
	strlist += lng->tr("FT_REPLACE");
	if( fileType == FILE_KM ) strlist += lng->tr("FT_MOUNT");
	dlg->addItemsList(strlist);	
	if(dlg->exec() == ZPopup::Accepted) 
	{			
		int ret =dlg->getCheckedItemIndex();
		delete dlg;
		dlg = NULL;	
		if( ret == 0 ) {
			#ifdef USE_NOTEPAD
			sprintf(exec_buffer,"exec /usr/SYSqtapp/notepad/notepad -d %s &", argFile);
			printf("Debug: system %s\n", exec_buffer);
			system(exec_buffer);
			#else					
			reader *r = new reader( qsFilePath);
			r->exec();
			delete r;
			r= NULL;
			#endif
		} 
		if( ret == 1 ) {
			sprintf(exec_buffer, "exec '%s' -d '%s' &", (const char *)cfgTxtEditorPath.local8Bit(), argFile);
			printf("Debug: system%s\n", exec_buffer);
			system(exec_buffer);
		}
		if( ret == 2 ) {
			if( fileType == FILE_KM ) {
				sprintf(exec_buffer, "cp -fR '%s' '/usr/language/inputmethods/%s.km' &", 
						argFile, (const char*)(lng->getCurLngType()).local8Bit() );
			} else {
				sprintf(exec_buffer, "cp -fR '%s' '/usr/data_resource/quicktext/%s.qkt' &", 
							argFile, (const char*)(lng->getCurLngType()).local8Bit() );
			}	
			printf("Debug: system%s\n", exec_buffer);
			system(exec_buffer);
		}
		if( ret == 3 ) {
			sprintf( exec_buffer, "cp -fR '%s' '/ezxlocal/download/mystuff/unKnown/%s.km' &",
				argFile, (const char*)(lng->getCurLngType()).local8Bit() );				
			printf("Debug: system%s\n", exec_buffer);
			system(exec_buffer);			
		}
		::exit(0);		
	}
	else
	{
		delete dlg;
		dlg = NULL;
		::exit(1);		
	}	

}
void RokrExtreme::logoCore()
{
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("POP_LOGO_OPTION"), lng->tr("FT_PLEASCHOOSE"));		
	QStringList strlist;
	strlist += lng->tr("FT_VIEW");
	strlist += lng->tr("FT_FLASH");
	dlg->addItemsList(strlist);	
	if(dlg->exec() == ZPopup::Accepted) 
	{			
		int ret =dlg->getCheckedItemIndex();
		delete dlg;
		dlg = NULL;	
		QString title = QString::null;
		QString text = QString::null;
		switch(ret) {
			case 0:
				showPic *v = new showPic(qsFilePath);
				v->exec();
				delete v;
				v = NULL;
				break;
			case 1:
				#ifdef VE66
				system( QString("/usr/sbin/chlogo -d %1").arg(argFile) );
				showQ(lng->tr("POP_OK"), lng->tr("FT_LOGO_FLASH_OK"), 2);	
				showQ(lng->tr("POP_OK"), lng->tr("FT_LOGO_FLASH_OK"), 2);
				#else
					#ifdef ZN5
						system( QString("cp -fR %1 /tmp/logo.bmp").arg(argFile) );
						system( QString("%1 /tmp/logo.bmp").arg(cfgFlashcpPath) );
						showQ(lng->tr("POP_OK"), lng->tr("FT_LOGO_FLASH_OK"), 2);
					#else
				system( QString("cp -fR %1 /tmp/mylogo.bmp").arg(argFile) );
				sprintf(exec_buffer , "'%s' /tmp/mylogo.bmp /tmp/logo.smg", (const char*)cfgLogoConvPath.local8Bit() );					
				ret = 255;
				title = lng->tr("FT_FLASH");
				text = lng->tr("POP_PLEASE_WAIT");					
				deathDlg *dDlg = new deathDlg(title, text, exec_buffer);
				dDlg->exec();
				ret = dDlg->ret;
				delete dDlg;
				dDlg = NULL;	
				if( ret == 0)  {
					sprintf(exec_buffer, "'%s' -v /tmp/logo.smg /dev/mtd/logo", (const char*)cfgFlashcpPath.local8Bit() );
					ret = 255;
					dDlg = new deathDlg(title, text, exec_buffer);
					dDlg->exec();
					ret = dDlg->ret;
					delete dDlg;
					dDlg = NULL;	
					if( ret == 0 ) {
						QFile::remove("/tmp/logo.smg");
						showQ(lng->tr("POP_OK"), lng->tr("FT_LOGO_FLASH_OK"), 2);
					} else {
						showQ(lng->tr("POP_ERROR"), lng->tr("FT_LOGO_FLASH_ERROR"), 2);
						::exit(1);
					}
				}
				else
				{
					showQ(lng->tr("POP_ERROR"), lng->tr("FT_LOGO_TYPE_ERROR"), 2);
					::exit(1);						
				}
					#endif
				#endif	
				break;	
			default:
				break;
		}
		::exit(0);	
	}
	else
	{
		delete dlg;
		dlg = NULL;
		::exit(1);		
	}
}

void RokrExtreme::mediaCore()
{
	QFile file(cfgMPlayerPath);
	#ifndef VE66
	if( !file.exists() ) {
		QString title = lng->tr("FT_NOMP_INFO");
		QString text = lng->tr("POP_INSTALLING");
		sprintf(exec_buffer,"%s/7z x '%s' -o'%s' -y", 
			(const char*)cfgP7zPath.local8Bit(), (const char*)cfgMPSrcPath.local8Bit(), (const char*)cfgMPDestPath.local8Bit() );
		int ret = 255;
		deathDlg *dDlg = new deathDlg(title, text, exec_buffer);
		dDlg->exec();
		ret = dDlg->ret;
		delete dDlg;
		dDlg = NULL;	
		if(ret != 0) 
			::exit(1);	
	}
	#endif
	sprintf(exec_buffer, "exec '%s' -d '%s' &", (const char *)cfgMPlayerPath.local8Bit(), argFile);
	printf("Debug: system %s\n", exec_buffer);
	system(exec_buffer);
}

void RokrExtreme::textCore()
{
	ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->tr("POP_TEXT_OPTION"), lng->tr("FT_PLEASCHOOSE"));		
	QStringList strlist;
	strlist += lng->tr("FT_VIEW");
	strlist += lng->tr("FT_EDIT");
	dlg->addItemsList(strlist);	
	if(dlg->exec() == ZPopup::Accepted) 
	{	
		int ret =dlg->getCheckedItemIndex();
		delete dlg;
		dlg = NULL;	
		switch(ret) {
			case 0:
				#ifdef USE_NOTEPAD
				sprintf(exec_buffer,"exec /usr/SYSqtapp/notepad/notepad -d %s &", argFile);
				printf("Debug: system %s\n", exec_buffer);
				system(exec_buffer);
				#else					
				reader *r = new reader( qsFilePath);
				r->exec();
				delete r;
				r= NULL;
				#endif
				break;
			case 1:
				sprintf(exec_buffer, "exec '%s' -d '%s' &", (const char *)cfgTxtEditorPath.local8Bit(), argFile);
				printf("Debug: system%s\n", exec_buffer);
				system(exec_buffer);
				break;
			default:
				break;
		}
		::exit(0);	
	}
	else
	{
		delete dlg;
		dlg = NULL;
		::exit(1);		
	}
}
void RokrExtreme::otherCore()
{
	ZSingleSelectDlg *ssDlg = new ZSingleSelectDlg(lng->tr("POP_UNKNOWN_TYPE"), lng->tr("FT_CHOOSE_OPEN_TYPE"));
	QStringList strlist;
	strlist += lng->tr("POP_PACKAGE_OPTINON");
	strlist += lng->tr("POP_SCRIPT_OPTION");
	strlist += lng->tr("POP_SKIN");
	strlist += lng->tr("POP_KM_OPTION");
	strlist += lng->tr("POP_QKT_OPTION");
	strlist += lng->tr("POP_LOGO_OPTION");
	strlist += lng->tr("POP_TEXT_OPTION");
		
	ssDlg->addItemsList(strlist);
	
	if(ssDlg->exec() == ZPopup::Accepted) 
	{			
		int ret = ssDlg->getCheckedItemIndex();
		delete ssDlg;
		ssDlg = NULL;
		
		switch(ret) {
			case 0:
				packageCore();
				break;
			case 1:
				scriptCore();
				break;
			case 2:
				themeCore();
				break;
			case 3:
				km_qkt_Core( FILE_KM );
				break;
			case 4:
				km_qkt_Core( FILE_QKT );
				break;
			case 5:
				logoCore();
				break;
			case 6:
				textCore();
				break;
			default:
				break;		
		}
		::exit(0);			
	}
	else
	{
		delete ssDlg;
		ssDlg = NULL;
		::exit(1);
	}

}





