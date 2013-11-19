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

//    QStringList TLVFirstLevel;
//    QStringList PortInfo;
//    QStringList POEInfo;
//    QStringList PortSpeed;
//    QStringList PortCombo;
//    QStringList OpticTransiever;
//    QStringList TypePHY;
//    QStringList PortPOE;
//    QStringList PortStack;
//    QStringList ChipSwitch;
//    QStringList POEChip;
//    QStringList ChipInterface;

private:
    void parseTLVElement(const QDomElement &element);
    void parsePortInfoElement(const QDomElement &element);
    void parsePOEInfoElement(const QDomElement &element);
    void parsePortSpeedElement(const QDomElement &element);
    void parsePortComboElement(const QDomElement &element);
    void parseOpticTransieverElement(const QDomElement &element);
    void parseTypePHYElement(const QDomElement &element);
    void parsePortPOEElement(const QDomElement &element);
    void parsePortStackElement(const QDomElement &element);
    void parseChipSwitchElement(const QDomElement &element);
    void parsePOEChipElement(const QDomElement &element);
    void parseChipInterfaceElement(const QDomElement &element);

};

#endif // DOMPARSER_H
