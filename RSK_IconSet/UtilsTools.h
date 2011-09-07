#ifndef UTILSTOOLS_H
#define UTILSTOOLS_H

//#include "myDef.h"
//#include "ZTaskItem.h"

QString getAppDir();
QString getIMEI();

QString getGname(int step = 255); //make a uid 
								 //need set differet step each time

QString ctr(const char*ChineseString);

int basename(char *str);
unsigned int getDirSize(const char* path);
QString size2string(unsigned long size);
bool df2MtdFreeSize(const QString mtdKeyName, unsigned int KBLimitSize ); // return true when free size < KBLimitSize
unsigned int getDf2MtdFreeSize(const QString mtdKeyName); // return the KB size of the target mtd free size

int showQ(const QString &title, const QString &text, int type = 0);
void showNotify(const QString &title, const QString &text, int type = 0, int time = 1);




#endif //UTILSTOOLS_H

