#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <qdom.h>
#include <QFile>
#include <QStringList>

class DomParser
{
public:

    bool readFile(const QString &fileName);

    QStringList TLVFirstLevel;
    QStringList PortInfo;
    QStringList POEInfo;
    QStringList PortSpeed;
    QStringList PortCombo;
    QStringList OpticTransiever;
    QStringList TypePHY;
    QStringList PortPOE;
    QStringList PortStack;
    QStringList ChipSwitch;
    QStringList POEChip;
    QStringList ChipInterface;

private:
    void parseTLVElement(const QDomElement &element);
    void parsePortInfoElement(const QDomElement &element);
    void parsePOEInfoElement(const QDomElement &element);
};

#endif // DOMPARSER_H
