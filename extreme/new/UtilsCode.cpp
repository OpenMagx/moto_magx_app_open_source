
#include <qfile.h>

#include "UtilsCode.h"

using namespace std;

#define CODEC_COUNT 9

UtilsCode::UtilsCode( const QString &file)
{
	mFile = file;
}
UtilsCode::~UtilsCode()
{
}

QTextCodec* UtilsCode::getCodec()
{
	return mTextCodec;
}
bool UtilsCode::detectFileCodec()
{
	QFile file ( mFile );
	if (  file.open ( IO_ReadWrite ) )
	{	
		//cout<<"===== file open ok ====="<<endl;
		
		char data[10000];
		int size = file.readBlock(data, sizeof(data));
		file.reset();
		int id = detectCodec(data, size);
		
		//cout<<"########## code id is "<<id<<" ########"<<endl;
		
		mTextCodec = codecByLocalId(id);
		file.close();
		return true;
	}
	return false;
}
int UtilsCode::detectCodec( char * chars, int maxLen)
{
	//cout<<"==== #Maxlen: "<<QString::number(maxLen)<<" strlen "<<QString::number(strlen(chars))<<endl;
	
	int ret[CODEC_COUNT];

	int id=0;

	for (int i=0;i<CODEC_COUNT; i++) 
	{
		ret[i] = checkCodec( chars, strlen(chars), i );
		//cout<<"====== #CodecId: "<<QString::number(i)<<endl;
		//cout<<" ret[i] "<<QString::number(ret[i])<<endl;
		//cout<<" ret[id] "<<QString::number(ret[id])<<endl;
		//cout<<" id  "<<id<<endl;
		if( ret[i] == 0 ) {
			id = i;
			break; 
		} else if ( ret[i]>ret[id] ) {
			id = i;
			//cout<<" ==== id "<<id<<endl;
		}	
	}

	return id;		

}

int UtilsCode::checkCodec(char* chars, int len, int codeId)
{
	//cout<<"==== checkCodec "<<endl;
	
	if ( codeId == 8 ) //if big5 codec
		return big5HeuristicContentMatch( chars, len );
	
    QTextCodec* codec = codecByLocalId(codeId);
    
    if ( !codec ) { 
		printf("Error: Codec %d not found!!", codeId);
		return -1; 
	}
    
    int col = codec->heuristicContentMatch(chars,len);
    
    if ( codeId > 0 ) {
    	if ( len != strlen(chars) ) {
    		if ( col )
    			col--;
		}		
    }		
    return col;
}

#define InRange(c, lower, upper)  (((c) >= (lower)) && ((c) <= (upper)))
#define IsFirstByte(c)	(InRange((c), 0x81, 0xFE))
#define IsSecondByteRange1(c)	(InRange((c), 0x40, 0x7E))
#define IsSecondByteRange2(c)	(InRange((c), 0xA1, 0xFE))
#define IsSecondByte(c)	(IsSecondByteRange1(c) || IsSecondByteRange2(c))

int UtilsCode::big5HeuristicContentMatch(const char* chars, int len)
{
	//cout<<" ======== big5HeuristicContentMatch ======="<<endl;
	
	int score = 0;
    int i=0;
    while (i<len)
    {
		uchar ch = chars[i];
		if ( !ch )
		    return -1;
		    
		if ( ch < 32 && ch != '\t' && ch != '\n' && ch != '\r' ) 
		{
		    if ( score )
				score--;
		} else 
		if ( ch < 0x80 ) 
		    score++;
		else 
		if ( IsFirstByte(ch) ) 
		{	
		    if ( i < len-1 ) 
		    {
				uchar c2 = chars[++i];
				if ( !IsSecondByte(c2) )
			    	return -1;
				score += 2;
		    } else
		    	score++;
		} else 
		    return -1;
		i++;
    }
    return score;
}

QTextCodec* UtilsCode::codecByLocalId( int id )
{
	//cout<<"==== code by id , id is "<<id<<endl;
	
	QTextCodec* codec;
	switch (id)
	{
		case 0:
			codec = QTextCodec::codecForName("utf8");
			break;		
		case 1:
			codec = QTextCodec::codecForName("CP1251");
			break;
		case 2:
			codec = QTextCodec::codecForName("KOI8-R");
			break;	
		case 3:
			codec = QTextCodec::codecForName("ISO8859-1");
			break;	
		case 4:
			codec = QTextCodec::codecForName("ISO8859-2");
			break;		
		case 5:
			codec = QTextCodec::codecForName("ISO8859-5");
			break;				
		case 6:
			codec = QTextCodec::codecForName("KOI8-U");
			break;
		//case 8:
		case 7:
			codec = QTextCodec::codecForName("GBK");
			break;			
		//case 7:
		case 8:
			codec = QTextCodec::codecForName("Big5");
			break;					
		default:
			codec = QTextCodec::codecForName("CP1251");								
	}
	return codec;
}




