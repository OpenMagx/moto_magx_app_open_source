#ifndef MEDIAROWSER_H
#define MEDIAROWSER_H

#include <RES_ICON_Reader.h>
#include <ZListBox.h>
#include <ZPopup.h>

#include "myDef.h"

#ifdef ZN5
	#include "BaseDlg.h"
	#define ZPopup MyBaseDlg
#endif	


class MediaBrowser : public ZPopup
{
    Q_OBJECT
	
public :	
	enum MEDIA_TYPE
	{
		TYPE_IMG,
		TYPE_AUDIO,
		TYPE_NULL
	};
	
public :	    
	MediaBrowser(MEDIA_TYPE type = TYPE_IMG);
	~MediaBrowser();

	bool isCancel;
	QString getSelectedFile();
	
private slots:
	void initList();
    void obj_click(int index);
	void slotOK();
	void slotCancel();

private :
	void setDir(QString pdir);
	void cdBack();
	MEDIA_TYPE getFileType(QString filePath);
	
	
	ZListBox *listBox;
	//Lng *lng;

	QString mCurDir;
	QString mSelectedFile;
	
	MEDIA_TYPE mType;	
	RES_ICON_Reader iconReader;


};


#endif //FILEBROWSER_H


