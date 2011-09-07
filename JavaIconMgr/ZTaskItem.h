#ifndef ZTASKITEM_H
#define ZTASKITEM_H

//#ifdef NEWUI
	#include "ZIconView.h"
//#else
//	#include <ZSettingItem.h>
//#endif	

#include "myDef.h"
#include "source.h"

//#ifdef NEWUI
class Q_EXPORT ZTaskItem : public ZIconViewItem
//#else
//class Q_EXPORT ZTaskItem : public ZSettingItem
//#endif

{
public: 
	//#ifdef NEWUI
	ZTaskItem( ZIconView *parent, const QString itemType = NULL );
	//#else
	//ZTaskItem( ZListBox* container = 0, const QString itemType = NULL );
	//#endif
	~ZTaskItem();

	 void setOriName(QString name); //full cmd for each process in tasklist
	 QString getOriName();
	
	 ITEMTYPE getType();
	 void setType( ITEMTYPE type);		
	
	 uint getPid();
	 void setPid( uint pid);
	
	 QString getGname();
	 void setGname( QString UID);	
	
	 bool isSD();
	 void setPath(bool isSD);
	
private:
	ITEMTYPE type;
	uint pid;
	bool isSDPath;
	//int data;
	QString oriName;
	QString uid;
};

#endif //ZTASKITEM_H
