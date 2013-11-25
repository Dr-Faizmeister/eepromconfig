#include "CTreeWidgetItem.h"

CTreeWidgetItem::CTreeWidgetItem(CTreeWidget *widg, CTreeWidgetItem* par):
    QTreeWidgetItem(0)
{
    cparent = par;
    treeWidget = widg;
    TLVtype = 0;
    setFlags(flags() | Qt::ItemIsEditable);
}
//==========================================================================
CTreeWidgetItem::~CTreeWidgetItem()
{

}
//==========================================================================
//вывод образа item-а
QByteArray* CTreeWidgetItem::getRecord()
{
    QByteArray* bytearr = new QByteArray();

    bool ok;

    bytearr->append((char) TLVtype);  //добавление Type

    if (! cparent) //не является дочерней записью
    {
        switch (TLVtype)
        {
        case 0x05: //MACAddr
        case 0x06: //SerialNumber
        {
            bytearr->append(0x06); //добавление length

            quint64 ut = TLVvalue.toULongLong (&ok, 16);
            bytearr->append((char*) &ut, 6); //добавление value

            break;
        }
        case 0x01: // Port Info
        {
            quint16 len;
            QByteArray childrecords; //образ дочерних записей

            for (int i = 0; i < childCount(); ++i) //формирование образа
            {
                CTreeWidgetItem* tlvchild = dynamic_cast <CTreeWidgetItem*> (child(i));
                childrecords.append(*tlvchild->getRecord());
            }

            len = childrecords.length() | 0x8000; //длина дочерних записей и указание что length содержит 2 байта
            len = qToBigEndian(len);

            bytearr->append((char*) &len, sizeof(len)); //добавление length
            bytearr->append(childrecords); //добавление value
            break;
        }

        case 0x03: //POE Info
        {
            QByteArray childrecords; //образ дочерних записей

            for (int i = 0; i < childCount(); ++i) //формирование образа
            {
                CTreeWidgetItem* tlvchild = dynamic_cast <CTreeWidgetItem*> (child(i));
                childrecords.append(*tlvchild->getRecord());
            }

            bytearr->append((char) childrecords.length()); //добавление length
            bytearr->append(childrecords); //добавление value
            break;
        }

        case 0x07: //name

            bytearr->append((char) TLVvalue.length()); //добавление length
            bytearr->append(TLVvalue.toAscii()); //добавление value
            break;

        default:

            bytearr->append(0x01);
            bytearr->append((char)TLVvalue.toUInt(&ok, 16));
            break;
        }
    }
    else //запись дочерняя
    {
        bytearr->append(0x01); //добавление length
        bytearr->append((char)TLVvalue.toUInt(&ok, 16)); //добавление value
    }

    return bytearr;
}
//==========================================================================
//задание нового значения
void CTreeWidgetItem::setRecordData(quint8 tlvtype, QString tlvvalue)
{
    TLVtype = tlvtype;
    TLVvalue = tlvvalue;

    if (cparent) //вывод длины в визуальное представление
    {
        setText(1, "1");
    }
    else
    {
        switch (TLVtype)
        {
        case 0x05: //MACAddr
        case 0x06: //SerialNumber
            setText(1, "6");
            break;
        case 0x01: //Port Info
        case 0x03: //POE Info
            setText(1, "");
            break;
        case 0x07: //name
            setText(1, QString("%1").arg(TLVvalue.size()));
            break;
        default:
            setText(1, "1");
            break;
        }
    }
}
//============================================================================================
QWidget* CTreeWidgetItem::createValueEditor()
{
    QStringList PortSpeed;
    QStringList PortCombo;
    QStringList OpticTransiever;
    QStringList TypePHY;
    QStringList PortPOE;
    QStringList PortStack;
    QStringList ChipSwitch;
    QStringList POEChip;
    QStringList ChipInterface;

    QFile file("C:/Qt/proj/eeprom/eepromconf/config.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    QDomDocument config;
    if (!config.setContent(&file, false)) {
        return false;
    }
    QDomElement root = config.documentElement();
    if (root.tagName() != "TLV") {
        return false;
    }
    QDomNode child = root.firstChild();
    while (!child.isNull()) {
        QDomElement el = child.toElement();
        if (el.tagName() == "type") {
            if (el.attribute("term") == "PortInfo") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    QDomElement element = child.toElement();
                    if (element.tagName() == "type" && element.attribute("term") == "PortSpeed") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                PortSpeed << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    } else if (element.tagName() == "type" && element.attribute("term") == "PortCombo") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                PortCombo << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    } else if (element.tagName() == "type" && element.attribute("term") == "OpticTransiever") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                OpticTransiever << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    } else if (element.tagName() == "type" && element.attribute("term") == "TypePHY") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                TypePHY << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    } else if (element.tagName() == "type" && element.attribute("term") == "PortPOE") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                PortPOE << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    } else if (element.tagName() == "type" && element.attribute("term") == "PortStack") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                PortStack << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "POEInfo") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    QDomElement element = child.toElement();
                    if (element.tagName() == "type" && element.attribute("term") == "POEChip") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                POEChip << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    } else if (element.tagName() == "type" && element.attribute("term") == "ChipInterface") {
                        QDomNode child = element.firstChild();
                        while (!child.isNull()) {
                            if (child.toElement().tagName() == "value") {
                                ChipInterface << child.toElement().text();
                            }
                            child = child.nextSibling();
                        }
                    }
                    child = child.nextSibling();
                }
            } else if (el.attribute("term") == "ChipSwitch") {
                QDomNode child = el.firstChild();
                while (!child.isNull()) {
                    if (child.toElement().tagName() == "value") {
                        ChipSwitch << child.toElement().text();
                    }
                    child = child.nextSibling();
                }
            }
        }
        child = child.nextSibling();
    }
    file.close(); // нужно ли вообще его закрывать??

    if (cparent)
    {
        QComboBox *editor = new QComboBox(treeWidget);
        if (cparent->getTLVType() == 0x01) //Port Info
        {
            switch (TLVtype)
            {
                case 0x06:
                    editor->addItems(PortSpeed);
                    return editor;
                case 0x07:
                    editor->addItems(PortCombo);
                    return editor;
                case 0x08:
                    editor->addItems(OpticTransiever);
                    return editor;
                case 0x09:
                    editor->addItems(TypePHY);
                    return editor;
                case 0x0A:
                    editor->addItems(PortPOE);
                    return editor;
                case 0x0B:
                    editor->addItems(PortStack);
                    return editor;
            }
        }

        if (cparent->getTLVType() == 0x03) //POE Info
        {
            switch (TLVtype)
            {
                case 0x02:
                    editor->addItems(POEChip);
                    return editor;
                case 0x03:
                    editor->addItems(ChipInterface);
                    return editor;
            }
        }

        QLineEdit *teditor = new QLineEdit(treeWidget);

        QRegExp hex_in("[0-9A-Fa-f]{1,2}");
        QValidator *validator = new QRegExpValidator(hex_in);

        teditor->setValidator(validator);
        return teditor;

    }

    else if (getTLVType() == 0x02) {  // Chip Switch             +
        QComboBox *editor = new QComboBox(treeWidget);
        editor->addItems(ChipSwitch);
        return editor;
    }

    else
    {
        QLineEdit *editor = new QLineEdit(treeWidget);
        switch (TLVtype)
        {
        case 0x05: //MACAddr
        case 0x06: //SerialNumber
        {
            QRegExp hex_in("[0-9A-Fa-f]{1,12}");
            QValidator *validator = new QRegExpValidator(hex_in);
            editor->setValidator(validator);
            break;
        }
        case 0x07: //name
        {
            //для поля name валидация не проводится
            break;
        }
        case 0x01: //Port Info
        case 0x03: //POE Info
            return NULL;
        default:
        {
            QRegExp hex_in("[0-9A-Fa-f]{1,2}");
            QValidator *validator = new QRegExpValidator(hex_in);

            editor->setValidator(validator);
            break;
        }
        }
        return editor;

    }
}
