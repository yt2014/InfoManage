#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString strDisplay = QString::number(index) + "is selected";

    QMessageBox::warning(this,tr("warning"),strDisplay,QMessageBox::Ok);

    switch(index)
    {
    case 0:
        break;
    case 1:

        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;


    }
}
