#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//for Account Table and related Tab
    m_AccountTable = new CAccountTable("PersonInfo","Account");
    AccountTable_has_readout = false;
    m_UserInfoList = UserInfoList();
    m_UserInfoTree = ui->treeWidget_Names;
    m_UserInfoTree->setHeaderHidden(true);
    connect(m_UserInfoTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(showPermission(QTreeWidgetItem*,int)));
    m_NameTreeItems = 0;

    m_UserUIControl = new CUserManage_UIControl(m_AccountTable);

}

MainWindow::~MainWindow()
{
    delete m_UserUIControl;
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

    delete ui;

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString strDisplay = QString::number(index) + "is selected";

    ui->label_ForDebug->setText(strDisplay);

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

void MainWindow::showPermission(QTreeWidgetItem* treeItem,int column)
{
    QString strDisplay = "column " + QString::number(column) + " \n";
    QString strPermission;

    int n = m_NameTreeItems->indexOfChild(treeItem);
    strDisplay += "index " + QString::number(n) + " is clicked\n";

    if(n>=0)
    {
        strPermission = m_UserInfoList.at(n).permission;
        strDisplay += "permission is " + strPermission;        

        //setting the current record and index in m_UserUIControl.
        m_UserUIControl->set_CurrentRecord(&(m_UserInfoList.at(n)));
        m_UserUIControl->set_index(n);
    }
    ui->label_ForDebug->setText(strDisplay);



}

 void MainWindow::AccountTableChangeOperation(Change_Operation operation,int Index_Changed)
 {
     switch (operation)
     {
        case Op_Add:
             {
                 OneUserInfo RecordToAdd;
                 RecordToAdd.name = ui->lineEdit_Name->text().trimmed();
                 RecordToAdd.password = ui->lineEdit_Password->text().trimmed();
                 RecordToAdd.permission = "0x0000";
                 Operation_Result result = m_AccountTable->addOneRecord(RecordToAdd);
                 switch(result)
                 {
                    case Operation_Success:
                      {
                          m_UserInfoList.append(RecordToAdd);
                          m_NameTreeItems->addChild(new QTreeWidgetItem(QStringList() << RecordToAdd.name));
                      }
                     break;
                   case DataBaseNotOpen:
                      {
                          ui->label_ForDebug->setText("database not open！");
                      }
                     break;
                   case AddExistRecord:
                      {
                         ui->label_ForDebug->setText("该用户名已经存在！");
                      }
                     break;
                   case AddFailed:
                      {
                         ui->label_ForDebug->setText("添加不成功,请重试！");
                      }
                     break;
                 default:
                      {
                         ui->label_ForDebug->setText("添加不成功，请重试！");
                      }
                     break;
                 }
             }
         break;
        case Op_Update:
             {
                OneUserInfo RecordToUpdate;
                RecordToUpdate.name = m_UserInfoList.at(Index_Changed).name;
                RecordToUpdate.password = ui->lineEdit_Password->text().trimmed();
                RecordToUpdate.permission = "0x0000";

                m_AccountTable->UpdateOneRecord(RecordToUpdate);
             }
         break;
        case Op_Delete:
             {

             }
         break;
     default:
         break;
     }
 }


