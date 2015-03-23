#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_AccountTable = new CAccountTable("PersonInfo","Account");
    AccountTable_has_readout = false;
    m_UserInfoList = UserInfoList();
    m_UserInfoTree = new QTreeWidget(ui->tab);
    m_UserInfoTree->setMaximumSize(220, 16777215);
    m_UserInfoTree->setHeaderHidden(true);
      //  horizontalLayout->addWidget(UserInfoTree);

        // In addition to the visible column, we add an invisible column in the tree view to hold
        // an index to the demo modules.
    m_UserInfoTree->setColumnCount(2);
    m_UserInfoTree->hideColumn(1);

    m_NameTreeItems = 0;
}

MainWindow::~MainWindow()
{
    delete m_AccountTable;

    if(m_NameTreeItems!=0)
    {
        QList<QTreeWidgetItem*>  lst_NameTreeChildren = m_NameTreeItems->takeChildren();
        lst_NameTreeChildren.clear();
        delete m_NameTreeItems;
    }
    if(!m_UserInfoList.isEmpty())
    {
        m_UserInfoList.clear();
    }

    delete m_UserInfoTree;
    delete ui;

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    //QString strDisplay = QString::number(index) + "is selected";

    //QMessageBox::warning(this,tr("warning"),strDisplay,QMessageBox::Ok);

    switch(index)
    {
    case 0:
    {
       if(!AccountTable_has_readout)
        {
            m_UserInfoList = m_AccountTable->getListAllFromDatabase();
            AccountTable_has_readout = true;
            int n = m_UserInfoList.count();

            m_UserInfoTree->addTopLevelItem(m_NameTreeItems = new QTreeWidgetItem(QStringList()<<"names"));

            for(int i=0;i<n;i++)
            {
                m_NameTreeItems->addChild(new QTreeWidgetItem(QStringList() << m_UserInfoList.at(i).name));

            }

            m_UserInfoTree->expandAll();
            m_UserInfoTree->show();
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
