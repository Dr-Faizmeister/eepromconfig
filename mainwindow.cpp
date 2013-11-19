#include "mainwindow.h"

//=========================================================
MainWindow::MainWindow (QWidget* parent) :
    QMainWindow (parent)
    ,ui (new Ui::MainWindow)
{
    ui->setupUi (this);

    memset (recdata, 0xFF, sizeof (recdata));
}
//====================================================
MainWindow::~MainWindow()
{
    delete ui;
}
//====================================================
void MainWindow::on_ExitAction_triggered()
{
    close();
}
//============================================================================================
void MainWindow::on_Save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName (this, "Save File", "", "BIN (*.bin )");

    if (fileName.isEmpty())
        return;

     QFile file (fileName);
     file.open (QIODevice::WriteOnly);

     bool ok;

     for (int i = 0; i < 127; i++)
     {
         if ((ui->tableWidget->item(i, 0) != NULL) && (ui->tableWidget->item(i, 1) != NULL))
         {
            recdata[i].addr = ui->tableWidget->item (i, 0)->text().toULong (&ok, 16);
            qToBigEndian (recdata[i].addr);
            recdata[i].val = ui->tableWidget->item (i, 1)->text().toULong (&ok, 16);
            qToBigEndian (recdata[i].val);
         }
         else break;
     }

     file.write ((char*) recdata, sizeof (recdata));

     QByteArray recdata2 = ui->treeWidget->getRecords();
     file.write(recdata2);


     file.close ();
}
//=============================================================
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1)
    {
        ui->addTreeWidgetItem->setEnabled(true);
        ui->delTreeWidgetItem->setEnabled(true);
        ui->addChildTreeWidgetItem->setEnabled(true);
    }
    else
    {
        ui->addTreeWidgetItem->setEnabled(false);
        ui->delTreeWidgetItem->setEnabled(false);
        ui->addChildTreeWidgetItem->setEnabled(false);
    }
}
//==========================================================
void MainWindow::on_addTreeWidgetItem_triggered()
{
    CTreeWidgetItem* cWidgetItem = new CTreeWidgetItem (ui->treeWidget);
    ui->treeWidget->addTopLevelItem (cWidgetItem);
}
//===============================================================================================================

void MainWindow::on_addChildTreeWidgetItem_triggered()
{
    CTreeWidgetItem* witem = ui->treeWidget->currentItem();
    if ( ! witem->parent() )
    {
        if ((witem->getTLVType() == 0x01) || (witem->getTLVType() == 0x03))
        {
            CTreeWidgetItem* cWidgetItem = new CTreeWidgetItem (ui->treeWidget, witem);
            witem->addChild(cWidgetItem);
        }
    }
    else
    {
        CTreeWidgetItem* cWidgetItem = new CTreeWidgetItem (ui->treeWidget, witem->parent());
        witem->parent()->addChild(cWidgetItem);
    }

}

void MainWindow::on_delTreeWidgetItem_triggered()
{
    delete ui->treeWidget->currentItem();
}
