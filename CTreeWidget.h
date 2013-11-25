#ifndef CTREEWIDGET_H
#define CTREEWIDGET_H

#include <QTreeWidget>
#include <QStringList>
#include <QItemDelegate>
#include <QLineEdit>
#include <QComboBox>
#include "CTreeWidgetItem.h"
#include <QFile>
#include "qdom.h"

class CTreeWidgetItem;

struct CTreeItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CTreeItemDelegate (QObject * parent);

    QWidget* createEditor (QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

};

class CTreeWidget: public QTreeWidget
{
    Q_OBJECT
public:
    CTreeWidget (QWidget* widg);

    CTreeWidgetItem* currentItem();
    QByteArray getRecords();

    ~CTreeWidget();
public slots:
    void editorClosed (QWidget* editor);
};

#endif // CTREEWIDGET_H
