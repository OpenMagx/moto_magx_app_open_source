#ifndef LNG_H
#define LNG_H

#include <ZConfig.h>

class Lng
{
public:
	Lng();
	~Lng();
	QString tr(const char *sourceText);
	QString getCurLngType();
private:
	ZConfig *mCfg;
	QString mLngType;
};
#endif
