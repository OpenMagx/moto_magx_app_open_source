#ifndef TXTREADER_H
#define TXTREADER_H

#include <ZApplication.h>
#include <ZKbMainWidget.h>
#include <ZLabel.h>
#include <ZSoftKey.h>
#include <ZKeyDef.h>
#include <ZFormContainer.h>
#include <ZOptionsMenu.h>

#include <qstring.h>
#include <qtextcodec.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qscrollview.h>
#include <iostream>

#include "BaseDlg.h"
#include "myDef.h"
#include "lng.h"

class reader : public MyBaseDlg 
{

	Q_OBJECT
	
public:    
	reader(QString &);
	~reader();
	QString ctr(const char *);
	void setPageCount();
	
public slots :	
	void loadText();
	void nextPage();
	void prePage();
	void slotAbout();	
	void slotCodec();
	
protected:
	bool  eventFilter( QObject *, QEvent * );  

private:	
	ZLabel *zlb; //显示文本的容器
	ZFormContainer *form;
	Lng *lng;
	//ZScrollPanel *zsv;
	
	int codeNameIndex;	//当前文本编码序号
	int pageCount;	//总页数
	int pageCur;	//当前页,从1开始
	int pageSize;	//每页几个字

	QString filename;	//打开的文件全路径
	QString m_txtContainer;	//文本文件的内容
	
	ZSoftKey *softKey;	
	ZOptionsMenu *menu;
	
	QTextCodec *mTextCodec;
};

#endif



