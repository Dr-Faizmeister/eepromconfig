#ifndef CTREEWIDGETITEM_H
#define CTREEWIDGETITEM_H

#include <QByteArray>
#include <QTreeWidgetItem>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QtEndian>
#include "CTreeWidget.h"
#include <QFile>
#include "qdom.h"

class CTreeWidget;

class CTreeWidgetItem: public QTreeWidgetItem
{
public:
    CTreeWidgetItem (CTreeWidget* widg, CTreeWidgetItem* par = NULL);
    ~CTreeWidgetItem();

    void setRecordData (quint8 tlvtype, QString tlvvalue);

    QByteArray* getRecord();

    quint8 getTLVType() { return TLVtype; }
    QString getTLVValue() {return TLVvalue; }

    CTreeWidgetItem* parent() { return cparent;  }

    QWidget* createValueEditor();

private:
    quint8 TLVtype;
    QString TLVvalue;
    CTreeWidgetItem* cparent;
    CTreeWidget* treeWidget;
};

#endif // CTREEWIDGETITEM_H
