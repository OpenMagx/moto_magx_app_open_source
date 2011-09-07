#ifndef STRUCTUREPARSER_H
#define STRUCTUREPARSER_H

#include <qxml.h>
#include <qstring.h>
#include "weatherData.h"

class QString;


extern WeatherData weatherData;
class StructureParser : public QXmlDefaultHandler
{
    public:
        bool startDocument();
        bool startElement( const QString&, const QString&, const QString& ,
                       const QXmlAttributes& );
        bool endElement( const QString&, const QString&, const QString& );

    private:
        QString indent;
};

#endif
