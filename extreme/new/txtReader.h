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
	ZLabel *zlb; //��ʾ�ı�������
	ZFormContainer *form;
	Lng *lng;
	//ZScrollPanel *zsv;
	
	int codeNameIndex;	//��ǰ�ı��������
	int pageCount;	//��ҳ��
	int pageCur;	//��ǰҳ,��1��ʼ
	int pageSize;	//ÿҳ������

	QString filename;	//�򿪵��ļ�ȫ·��
	QString m_txtContainer;	//�ı��ļ�������
	
	ZSoftKey *softKey;	
	ZOptionsMenu *menu;
	
	QTextCodec *mTextCodec;
};

#endif



