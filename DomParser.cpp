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
                parseChipSwitchElement(el);
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
                parsePortSpeedElement(el);
            } else if (el.attribute("term") == "PortCombo") {
                parsePortComboElement(el);
            } else if (el.attribute("term") == "OpticTransiever") {
                parseOpticTransieverElement(el);
            } else if (el.attribute("term") == "TypePHY") {
                parseTypePHYElement(el);
            } else if (el.attribute("term") == "PortPOE") {
                parsePortPOEElement(el);
            } else if (el.attribute("term") == "PortStack") {
                parsePortStackElement(el);
            }
        }
        child = child.nextSibling();
    }
}

void DomParser::parseChipSwitchElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            ChipSwitch << value;
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
                parsePOEChipElement(el);
            } else if (el.attribute("term") == "ChipInterface") {
                parseChipInterfaceElement(el);
            }
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePortSpeedElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            PortSpeed << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePortComboElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            PortCombo << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parseOpticTransieverElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            OpticTransiever << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parseTypePHYElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while(!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            TypePHY << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePortPOEElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while(!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            PortPOE << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePortStackElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while(!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            PortStack << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePOEChipElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while(!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            POEChip << value;
        }
        child = child.nextSibling();
    }
}

void DomParser::parseChipInterfaceElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while(!child.isNull()) {
        if (child.toElement().tagName() == "value") {
            QString value = element.text();
            ChipInterface << value;
        }
        child = child.nextSibling();
    }
}
