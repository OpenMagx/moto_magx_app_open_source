
#include <ZFormContainer.h>
#include <ZSoftKey.h>

#include <AM_LauncherClient.h>

#include <qdir.h>
#include <qfile.h>

#include <iostream>

#include "mediaBrowser.h"
#include "lng.h"
#include "myDef.h"

#ifdef ZN5
#define ZListBoxItem ZSettingItem
#endif

using namespace std;

extern Lng *lng;

MediaBrowser::MediaBrowser(MEDIA_TYPE type):ZPopup()
{
	isCancel = true;
	mType = type;
	
	mCurDir = QString("/mmc");
	mSelectedFile = QString::null;
	
	#ifdef ZN5
	#define setTitle setMainWidgetTitle
	#define insertChild setContentWidget
	#define softkey_rep
	#endif
	this->setTitle( lng->tr("FT_FILEPICKER") );
	
	ZFormContainer *form = new ZFormContainer(this);

	this->insertChild(form);	

	listBox = new ZListBox ( QString ( "%I%M" ), this, 0);
	listBox->enableMarquee(ZListBox::LISTITEM_REGION_A, true);
	listBox->enableMarquee(ZListBox::LISTITEM_REGION_B, true);	
	form->addChild(listBox);
	
	#ifdef softkey_rep
	ZSoftKey *softKey = new ZSoftKey("CST_2A", this, this);
	this->setSoftKey(softKey);
	#else
	ZSoftKey *softKey = this->getSoftKey();
	#endif
	softKey->setText(ZSoftKey::LEFT,  lng->tr("FT_SELECT"));
    softKey->setText(ZSoftKey::RIGHT, lng->tr("FT_CANCEL"));	
	softKey->setClickedSlot(ZSoftKey::RIGHT, this, SLOT( slotCancel() ));
	softKey->setClickedSlot(ZSoftKey::LEFT, this, SLOT ( slotOK() ));	

	connect(listBox, SIGNAL( selected(int) ), this, SLOT( obj_click(int) ) );

	QTimer::singleShot(100, this, SLOT( initList() ) );

}	

MediaBrowser::~MediaBrowser()
{
	//delete lng;
	//lng = NULL;
	printf("====== delete meida browser =====\n");
}		
QString MediaBrowser::getSelectedFile()
{
	return mSelectedFile;
}
void MediaBrowser::initList()
{
	setDir(mCurDir);
    listBox->setCurrentItem(0);
}

void MediaBrowser::setDir(QString pdir)
{   
	int fileCount = 0;
	int dirCount = 0;	
	
	mCurDir = pdir;

	listBox->clear();
	
	QDir dir(pdir);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::System); 
	#ifndef ZN5
	dir.setSorting(QDir::DirsFirst | QDir::Name | QDir::IgnoreCase);
	#endif
	
	dir.setMatchAllDirs (true);		
	dir.sorting();

	if ( !dir.isReadable() ) return;

	QStringList entries;
	QStringList::ConstIterator p;   
	entries = dir.entryList();	

	ZListBoxItem* pItem = NULL;
	QPixmap icon;	
	for (p=entries.begin(); p!=entries.end(); p++)
	{
        if ( *p == "." || *p == ".." ) continue;		
		icon = iconReader.getIcon( (QFileInfo(pdir+"/"+*p).isFile()) ? "fm_insert_file_small.bmp" : "fm_folder_small.bmp" );

		if ( !QFileInfo(pdir+"/"+*p).isFile() ) {
			pItem = new ZListBoxItem(listBox, QString("%I%M"));
			//#endif
			pItem->appendSubItem(1, *p);
			pItem->setPixmap(0, icon);
			dirCount++;	
			listBox->insertItem(pItem);					
		}	
		else {
		
			if(mType == TYPE_IMG)
			{
				if( getFileType( QString("%1/%2").arg(mCurDir).arg(*p) ) == TYPE_IMG ) 	{						
					//#ifdef SCREEN_V
					//pItem = new ZListBoxItem(this, QString("%I%M170%I"));
					//#else
					pItem = new ZListBoxItem(listBox, QString("%I%M"));
					//#endif
					pItem->appendSubItem(1, *p);
					pItem->setPixmap(0, icon);
					fileCount++;
					listBox->insertItem(pItem);			
				} else 	{
					continue;
				}
			}
			if(mType == TYPE_AUDIO)
			{
				if( getFileType( QString("%1/%2").arg(mCurDir).arg(*p) ) == TYPE_AUDIO ) 	{
					//#ifdef SCREEN_V
					//pItem = new ZListBoxItem(this, QString("%I%M170%I"));
					//#else
					pItem = new ZListBoxItem(listBox, QString("%I%M"));
					//#endif
					pItem->appendSubItem(1, *p);
					pItem->setPixmap(0, icon);
					fileCount++;
					listBox->insertItem(pItem);			
				} else 	{
					continue;
				}			
			}
		}	
	}
	printf(" ==== add top item ====\n");
	//#ifdef SCREEN_V
	//pItem = new ZListBoxItem(this, QString("%I%M100%M"));
	//#else	
	pItem = new ZListBoxItem(listBox, QString("%I%M140%M"));
	//#endif
	pItem->appendSubItem(1, pdir);
	pItem->appendSubItem(2, QString( "  %1 Dirs %2 Files").arg(dirCount).arg(fileCount) );	
	listBox->insertItem(pItem, 0);//, false);
}

void MediaBrowser::obj_click(int index)
{
	if( index == 0 )  {
		cdBack();
		return;
	}

	QString sName = QString::null;
	QString sPath  = QString::null;
	
	ZListBoxItem *pItem = (ZListBoxItem *)listBox->item(index);

    sName = pItem->getSubItemText(1, 0);  

	if(mCurDir == "/")  
		sPath = mCurDir + sName;
    else 
		sPath = mCurDir + "/" + sName;	

	if( QFileInfo(sPath).isDir() ) 	{
		mCurDir = sPath;
		setDir(mCurDir);
	} else {   
		cout<<"click file  "<<sPath<<endl;
		
		AM_LauncherClient::openDocument(sPath);			
	}	
}

void MediaBrowser::slotOK()
{
	int index = -1;
	index = listBox->currentItem();
	if( index == -1  || index == 0 ) {
		isCancel = true;
		reject();
	}

	QString sName = QString::null;
	QString sPath  = QString::null;
	
	ZListBoxItem *pItem = (ZListBoxItem *)listBox->item(index);
	sName = pItem->getSubItemText(1, 0);  

	if(mCurDir == "/")  
		sPath = mCurDir + sName;
    else 
		sPath = mCurDir + "/" + sName;	

	if( QFileInfo(sPath).isDir() ) 	{
		return;
	} else {   
		mSelectedFile = sPath;
	}	
	isCancel = false;
	reject();	
}

void MediaBrowser::slotCancel()
{
	isCancel = true;
	reject();
}
void MediaBrowser::cdBack()
{
	QString newDir;  
	int ret = mCurDir.findRev('/');
	if (ret <= 0) 
		newDir = "/";
	else 
		newDir = mCurDir.left(ret);
	mCurDir = newDir;

	setDir(mCurDir);	
}

MediaBrowser::MEDIA_TYPE MediaBrowser::getFileType(QString filePath)
{
	int i = -1;
	i = filePath.findRev("/");
    filePath = filePath.remove(0, i+1);
	i = -1;
	i = filePath.findRev(".");
	filePath = filePath.remove(0, i+1);	
	filePath = ( QString(".%1").arg(filePath) ).lower();
	if( filePath == ".jpg" || filePath == ".jpeg" || filePath == ".png" || filePath == ".bmp" || filePath == ".gif" )
		return TYPE_IMG;
	else if ( filePath == ".mp3" || filePath == ".midi" || filePath == ".ogg" || filePath == ".wma" || filePath == ".wav" )	
		return TYPE_AUDIO;
	else
		return TYPE_NULL;
}





