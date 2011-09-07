
#ifndef UTILSCODE_H
#define UTILSCODE_H

#include <qtextcodec.h>

#include <iostream>

class UtilsCode 
{
public :
	UtilsCode( const QString &file);
	~UtilsCode();
	
	bool detectFileCodec();
	//QString getFileStr();
	QTextCodec* getCodec();
	//void setFileBlock(char *fileBlock);
	
protected :
	int detectCodec( char * chars, int maxLen = -1 );
	QTextCodec* codecByLocalId( int id );
	int checkCodec(char* chars, int len, int codeId);
	int big5HeuristicContentMatch(const char* chars, int len);

private :
	QString mFile;
	//QString mFileStr;
	QTextCodec *mTextCodec;

};

#endif


