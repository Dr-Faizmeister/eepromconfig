#ifndef CFIRSTAREATABLE_H
#define CFIRSTAREATABLE_H

#include <QTableWidget>
#include <QItemDelegate>
#include <QLineEdit>


struct CItemDelegate : public QItemDelegate
{
public:
    CItemDelegate (QObject * parent) : QItemDelegate (parent) { }

    QWidget* createEditor (QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

class CFirstAreaTable: public QTableWidget
{
    Q_OBJECT
public:
    CFirstAreaTable (QWidget* widg);
    ~CFirstAreaTable();
};

#endif // CFIRSTAREATABLE_H
