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

    m_UserRadioGroup = new QButtonGroup(ui->tab);
    m_SergeantRadioGroup = new QButtonGroup(ui->tab);
    m_CadresRadioGroup = new QButtonGroup(ui->tab);

    m_CadresRadioGroup->addButton(ui->rB_CadresNo,0);
    m_CadresRadioGroup->addButton(ui->rB_CadresReadOnly,1);
    m_CadresRadioGroup->addButton(ui->rB_CadresReadWrite,2);

    m_UserRadioGroup->addButton(ui->rB_UserNo,0);
    m_UserRadioGroup->addButton(ui->rB_UserReadOnly,1);
    m_UserRadioGroup->addButton(ui->rB_UserReadWrite,2);


    m_SergeantRadioGroup->addButton(ui->rB_SergeantNo,0);
    m_SergeantRadioGroup->addButton(ui->rB_SergeantReadOnly,1);
    m_SergeantRadioGroup->addButton(ui->rB_SergeantReadWrite,2);

    connect(m_UserRadioGroup,SIGNAL(buttonClicked(int id)),this,SLOT(PermissionChanged(int id)));


    ui->tabWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete m_UserRadioGroup;
    delete m_SergeantRadioGroup;
    delete m_CadresRadioGroup;
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



void MainWindow::on_pushButton_AddUser_clicked()
{
    m_UserUIControl->set_Status(Op_Add);
    ui->pushButton_AddUser->setVisible(false);
    ui->pushButton_Delete->setVisible(false);
    ui->pushButton_Update->setVisible(false);

    ui->pushButton_Cancel->setVisible(true);
    ui->pushButton_OK->setVisible(true);
}

void MainWindow::on_pushButton_Update_clicked()
{
    m_UserUIControl->set_Status(Op_Update);
    ui->pushButton_AddUser->setVisible(false);
    ui->pushButton_Delete->setVisible(false);
    ui->pushButton_Update->setVisible(false);

    ui->pushButton_Cancel->setVisible(true);
    ui->pushButton_OK->setVisible(true);
}


void MainWindow::on_pushButton_Delete_clicked()
{
     m_UserUIControl->set_Status(Op_Delete);
     ui->pushButton_AddUser->setVisible(false);
     ui->pushButton_Delete->setVisible(false);
     ui->pushButton_Update->setVisible(false);

     ui->pushButton_Cancel->setVisible(true);
     ui->pushButton_OK->setVisible(true);
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    m_UserUIControl->set_Status(Op_Idle);
    ui->pushButton_AddUser->setVisible(true);
    ui->pushButton_Delete->setVisible(true);
    ui->pushButton_Update->setVisible(true);

    ui->pushButton_Cancel->setVisible(false);
    ui->pushButton_OK->setVisible(false);
}



void MainWindow::on_pushButton_OK_clicked()
{

    OneUserInfo currentRecord;
    currentRecord.name = ui->lineEdit_Name;
    currentRecord.password = ui->lineEdit_Password;

    m_UserUIControl->

    m_UserUIControl->set_Status(Op_Idle);
    ui->pushButton_AddUser->setVisible(true);
    ui->pushButton_Delete->setVisible(true);
    ui->pushButton_Update->setVisible(true);

    ui->pushButton_Cancel->setVisible(false);
    ui->pushButton_OK->setVisible(false);
}

void MainWindow::PermissionChanged()
{
    if(sender() == m_UserRadioGroup)
    {

    }

}
