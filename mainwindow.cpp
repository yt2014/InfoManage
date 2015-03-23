#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QTreeWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_AccountTable = new CAccountTable("PersonInfo","Account");
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
    {
        QTreeWidget * UserInfoTree = new QTreeWidget(ui->tab);

        UserInfoTree->setMaximumSize(220, 16777215);
            UserInfoTree->setHeaderHidden(true);
          //  horizontalLayout->addWidget(UserInfoTree);

            // In addition to the visible column, we add an invisible column in the tree view to hold
            // an index to the demo modules.
            UserInfoTree->setColumnCount(2);
            UserInfoTree->hideColumn(1);
        if(!AccountTable_has_readout)
        {
            m_UserInfoList = m_AccountTable->getListAllFromDatabase();
            AccountTable_has_readout = true;
            int n = m_UserInfoList.count();

            QTreeWidgetItem *currentCategory = 0;

            UserInfoTree->addTopLevelItem(currentCategory = new QTreeWidgetItem(QStringList()<<"names"));

            for(int i=0;i<n;i++)
            {
                currentCategory->addChild(new QTreeWidgetItem(QStringList() << m_UserInfoList.at(i).name));

            }

            UserInfoTree->expandAll();
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
