#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QTreeWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_AccountTable = new AccountTable();
    AccountTable_has_readout = false;
    m_UserInfoList = UserInfoList();

}

MainWindow::~MainWindow()
{
    delete m_AccountTable;
    delete ui;

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString strDisplay = QString::number(index) + "is selected";

    QMessageBox::warning(this,tr("warning"),strDisplay,QMessageBox::Ok);

    switch(index)
    {
    case 0:
        QTreeWidget * UserInfoTree = new QTreeWidget(ui->tab);
        if(!AccountTable_has_readout)
        {
            m_UserInfoList = m_AccountTable->getListAllFromDatabase();
            int n = m_UserInfoList.count();
            for(int i=0;i<n;i++)
            {
                UserInfoTree->addTopLevelItem();
                        m_UserInfoList.at(i).name;
            }
        }
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
