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
        if (child.toElement().tagName() == "type") {
            QString term = element.attribute("term");
            TLVFirstLevel << term;
            if (term == "PortInfo") {
                parsePortInfoElement(child.toElement());
            } else if (term == "ChipSwitch") {
                parseChipSwitchElement(child.toElement());
            } else if (term == "POEInfo") {
                parsePOEInfoElement(child.toElement());
            }
        }
        child = child.nextSibling();
    }
}

void DomParser::parsePortInfoElement(const QDomElement &element) {
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "type") {
            PortInfo << element.attribute("term");
            if (element.attribute("term") == "PortSpeed") {
                parsePortSpeedElement(child.toElement());
            } else if (element.attribute("term") == "PortCombo") {
                parsePortComboElement(child.toElement());
            } else if (element.attribute("term") == "OpticTransiever") {
                parseOpticTransieverElement(child.toElement());
            } else if (element.attribute("term") == "TypePHY") {
                parseTypePHYElement(child.toElement());
            } else if (element.attribute("term") == "PortPOE") {
                parsePortPOEElement(child.toElement());
            } else if (element.attribute("term") == "PortStack") {
                parsePortStackElement(child.toElement());
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
        if (child.toElement().tagName() == "type") {
            POEInfo << element.attribute("term");
            if (element.attribute("term") == "POEChip") {
                parsePOEChipElement(child.toElement());
            } else if (element.attribute("term") == "ChipInterface") {
                parseChipInterfaceElement(child.toElement());
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
