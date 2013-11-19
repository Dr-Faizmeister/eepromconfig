#include "CTreeWidget.h"

CTreeItemDelegate::CTreeItemDelegate(QObject * parent) :
    QItemDelegate(parent)
{
}
//===========================================================================
QWidget* CTreeItemDelegate::createEditor ( QWidget * parent,
                                         const QStyleOptionViewItem & option,
                                         const QModelIndex & index ) const
{
    CTreeWidget* treeWidget = dynamic_cast<CTreeWidget*> (this->parent());
    CTreeWidgetItem* treeWidgetItem = treeWidget->currentItem();

    if ((index.column() == 2) && (treeWidgetItem->getTLVType() != 0)) //столбец ЗНАЧЕНИЯ и задан ТИП
    {
       treeWidgetItem->setText(2, "");
       return treeWidgetItem->createValueEditor();
    }

    if (index.column() == 1) //столбец ДЛИНА
        return NULL;

    if ((index.column() == 0) && (treeWidgetItem->childCount() == 0) ) //столбец ТИП и не имеет дочерних записей
    {
        QComboBox *editor = new QComboBox (parent);

        if (treeWidgetItem->parent()) //у текущей записи имеется родитель
        {
            if (treeWidgetItem->parent()->getTLVType() == 0x01)
                editor->addItems(PortInfo);

            if (treeWidgetItem->parent()->getTLVType() == 0x03)
                editor->addItems(POEInfo);
        }
        else
            editor->addItems(TLVFirstLevel);   // если не имеет родителя, добавить ТИП верхнего уровня

        return editor;
    }
    return NULL;
}
//=====================================================
CTreeWidget::CTreeWidget(QWidget *widg):
    QTreeWidget(widg)
{
    CTreeItemDelegate* tItemDelegate = new CTreeItemDelegate (this);

    QObject::connect(tItemDelegate, SIGNAL(closeEditor(QWidget*)), this, SLOT(editorClosed(QWidget*)));

    setItemDelegate(tItemDelegate);

}
//========================================================
CTreeWidget::~CTreeWidget()
{

}
//========================================================
CTreeWidgetItem* CTreeWidget::currentItem()
{
    return dynamic_cast<CTreeWidgetItem*>(QTreeWidget::currentItem());
}
//=========================================================
void CTreeWidget::editorClosed(QWidget *editor)
{
      CTreeWidgetItem* tItem = currentItem(); //текущая выделенная запись

    if (currentIndex().column() == 0) //текущий столбец - ТИП
    {
        QComboBox* teditor = dynamic_cast<QComboBox*>(editor);

        // список всех имеющихся записей в дереве
         QList<QTreeWidgetItem*> list = findItems("", Qt::MatchContains | Qt::MatchRecursive);


         for (int i = 0; i < list.length(); ++i) // цикл проверки на повторение значений поля ТИП
         {
             CTreeWidgetItem* trwi=dynamic_cast<CTreeWidgetItem*>(list[i]);
             //у записей совпадают родители
             if (trwi->parent() == tItem->parent())
             {
                 //в дереве нашлась запись совпадающая с только что введенным типом
                 if (trwi->getTLVType() == teditor->currentIndex()+1)
                 {
                     teditor->setCurrentIndex(tItem->getTLVType());
                     tItem->setText(0,"");
                     return;
                 }
             }
         }


         if (tItem->getTLVType() != teditor->currentIndex() + 1)
            tItem->setRecordData (teditor->currentIndex() + 1, ""); //запись введенного значения
    }

    if (currentIndex().column() == 2) // текущий столбец ЗНАЧЕНИЕ
    {
        if (tItem->parent()) //у записи есть родитель
        {
            if (tItem->parent()->getTLVType() == 0x01) //Port Info
                switch (tItem->getTLVType())
                {
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:
                case 0x0A:
                case 0x0B:
                {
                    QComboBox* teditor = dynamic_cast<QComboBox*>(editor);

                    if (tItem->getTLVValue().toInt() != teditor->currentIndex())
                        tItem->setRecordData (tItem->getTLVType(),QString("%1").arg(teditor->currentIndex()));

                    break;
                }
                default:
                {
                    QLineEdit* teditor = dynamic_cast<QLineEdit*>(editor);

                    if (tItem->getTLVValue() != teditor->text())
                        tItem->setRecordData (tItem->getTLVType(),teditor->text());
                }
                }

            if (tItem->parent()->getTLVType() == 0x03) //POE Info
                switch (tItem->getTLVType())
                {
                    case 0x02:
                    case 0x03:
                {
                    QComboBox* teditor = dynamic_cast<QComboBox*>(editor);

                    if (tItem->getTLVValue().toInt() != teditor->currentIndex())
                        tItem->setRecordData (tItem->getTLVType(),QString("%1").arg(teditor->currentIndex()));

                    break;
                }
                default:
                {
                    QLineEdit* teditor = dynamic_cast<QLineEdit*>(editor);

                    if (tItem->getTLVValue() != teditor->text())
                        tItem->setRecordData (tItem->getTLVType(),teditor->text());
                }
                }
        }
        else //записи верхнего уровня
        {
            QLineEdit* teditor = dynamic_cast<QLineEdit*>(editor);

            if (tItem->getTLVValue() != teditor->text())
                tItem->setRecordData (tItem->getTLVType(),teditor->text());
        }
    }
}
//=================================================================================================================
//создание образа из текущих данных item-ов
QByteArray CTreeWidget::getRecords()
{
    QByteArray records;
    QList<QTreeWidgetItem*> list = findItems("",Qt::MatchContains); //все верхние записи

    for (int i = 0; i < list.count(); ++i)
    {
        CTreeWidgetItem* treeWidgetItem = dynamic_cast <CTreeWidgetItem*> (list[i]);
        records.append(*treeWidgetItem->getRecord());
    }
    return records;
}
