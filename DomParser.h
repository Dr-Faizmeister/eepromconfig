#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <qdom.h>
#include <QFile>
#include <QStringList>
#include "TLV.h"

class DomParser
{
public:

    bool readFile(const QString &fileName);

private:
    void parseTLVElement(const QDomElement &element, QStringList &TLVFirstLevel);
    void parsePortInfoElement(const QDomElement &element, QStringList &PortInfo);
    void parsePOEInfoElement(const QDomElement &element, QStringList &POEInfo);
};

#endif // DOMPARSER_H
