#include "CFirstAreaTable.h"

//===========================================================================
QWidget* CItemDelegate::createEditor ( QWidget * parent,
                                         const QStyleOptionViewItem & option,
                                         const QModelIndex & index ) const
{
    QLineEdit *editor = new QLineEdit (parent);

    QRegExp hex_in ("[0-9A-Fa-f]{0,8}");
    QValidator *validator = new QRegExpValidator (hex_in);

    editor->setValidator (validator);
    return editor;
}
//=====================================================
CFirstAreaTable::CFirstAreaTable(QWidget *widg):
    QTableWidget(widg)
{   
    setItemDelegate(new CItemDelegate(this));
}
//========================================================
CFirstAreaTable::~CFirstAreaTable()
{

}
//========================================================
