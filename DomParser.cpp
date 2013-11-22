#include "DomParser.h"

bool DomParser::readFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }
    QDomDocument config;
    if (!config.setContent(&file, false)) {
        return false;
    }
    QDomElement root = config.documentElement();
    if (root.tagName() != "TLV") {
        return false;
    }
    parseTLVElement(root);
    file.close(); // нужно ли вообще его закрывать??
    return true;
}

void DomParser::parseTLVElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        QDomElement el = child.toElement();
        if (el.tagName() == "type") {
            TLVFirstLevel << el.attribute("term");
            if (el.attribute("term") == "PortInfo") {
                parsePortInfoElement(el);
            } else if (el.attribute("term") == "ChipSwitch") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        ChipSwitch << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "POEInfo") {
                parsePOEInfoElement(el);
            }
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePortInfoElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        QDomElement el = child.toElement();
        if (el.tagName() == "type") {
            PortInfo << el.attribute("term");
            if (el.attribute("term") == "PortSpeed") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        PortSpeed << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "PortCombo") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        PortCombo << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "OpticTransiever") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        OpticTransiever << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "TypePHY") {
                QDomNode child = el.firstChild();
                while(!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        TypePHY << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "PortPOE") {
                QDomNode child = el.firstChild();
                while(!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        PortPOE << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "PortStack") {
                QDomNode child = el.firstChild();
                while(!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        PortStack << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            }
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePOEInfoElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        QDomElement el = child.toElement();
        if (el.tagName() == "type") {
            POEInfo << el.attribute("term");
            if (el.attribute("term") == "POEChip") {
                QDomNode child = el.firstChild();
                while(!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        POEChip << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "ChipInterface") {
                QDomNode child = el.firstChild();
                while(!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                       ChipInterface << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            }
        }
        child = child.nextSibling();
    }
}
