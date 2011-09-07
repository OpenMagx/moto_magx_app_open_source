#ifndef ROKREXTREME_H_
#define ROKREXTREME_H_

#include <ZApplication.h>

#include <RES_ICON_Reader.h>

#include <qstring.h>
#include <iostream>

#include "lng.h"

//#define P7Z_PATH "/usr/local/p7zip"
//#define SKIN_PHONE "/ezxlocal/download/mystuff/skins"
//#define SKIN_PART2 "/mmc/mmca2/skins"


class RokrExtreme : public ZApplication
{
	Q_OBJECT
	
public:
	enum FILE_TYPE
	{
		FILE_PACKAGE, //.
		FILE_FONT, //
		FILE_SCRIPT, //
		FILE_THEME, //
		FILE_KM,//
		FILE_QKT,//
		FILE_LOGO, //
		FILE_MEDIA,
		FILE_TEXT,
		FILE_IMS,
		NONE_TYPE
	};

public:
	RokrExtreme(int argc, char **argv);
	~RokrExtreme();

protected:
	void packageCore();
	void scriptCore();
	void themeCore();
	#ifndef VE66
	void iMarsCore();
	#endif
	void fontCore();
	void km_qkt_Core( FILE_TYPE fileType = FILE_KM );
	void logoCore();
	void mediaCore();
	void textCore();
	void otherCore();
	
	void themeChk();
	void loadConfig();
	
	FILE_TYPE getFileType( const char *path );

private:
	char filename[128];
	char dirname[384];
	char exec_buffer[1024];	
	char argFile[512];
	
	Lng *lng;
	RES_ICON_Reader iconReader;
	bool CardExist;
	
	QString mFilePath;
	QString mFileName;
	QString mDirName;

	QString myPath;
	QString qsFilePath;
	
	FILE_TYPE fileType;
	
	
	QString cfgP7zPath;
	QString cfgSkin_phone;
	QString cfgSkin_part2;
	QString cfgTxtEditorPath;
	//QString cfgKmTargetPath;
	//QString cfgQktTargetPath;
	QString cfgMPlayerPath;
	QString cfgMPSrcPath;
	QString cfgMPDestPath;
	QString cfgLogoConvPath;
	QString cfgFlashcpPath;
	QString cfgMarsSkinPath;
};

#endif //RokrExtreme



