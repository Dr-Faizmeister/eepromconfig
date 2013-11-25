#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QtEndian>
#include "ui_mainwindow.h"
#include "CTreeWidgetItem.h"
#include "CTreeWidget.h"

struct rec {
    quint32 addr;
    quint32 val;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow (QWidget *parent = 0);
    ~MainWindow();

    void writeTLV();


public slots:

    void on_ExitAction_triggered ();

private slots:

    void on_Save_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_addTreeWidgetItem_triggered();

    void on_addChildTreeWidgetItem_triggered();

    void on_delTreeWidgetItem_triggered();

private:
    rec recdata[128];
    Ui::MainWindow *ui;
    QByteArray* byteArr;
};

#endif // MAINWINDOW_H
