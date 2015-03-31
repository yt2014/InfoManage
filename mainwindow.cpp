#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UserUI_Init();

//for Account Table and related Tab
/*    m_AccountTable = new CAccountTable("PersonInfo","Account");
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

    connect(m_UserRadioGroup,SIGNAL(buttonClicked(int)),this,SLOT(PermissionChanged(int)));
    connect(m_SergeantRadioGroup,SIGNAL(buttonClicked(int)),this,SLOT(PermissionChanged(int)));
    connect(m_CadresRadioGroup,SIGNAL(buttonClicked(int)),this,SLOT(PermissionChanged(int)));

    ui->tabWidget->currentChanged(0);*/

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
        strPermission = QString::number(m_UserInfoList.at(n).permission);
        strDisplay += "permission is " + strPermission;        

        //setting the current record and index in m_UserUIControl.
        m_UserUIControl->set_CurrentRecord(&(m_UserInfoList.at(n)));
        m_UserUIControl->set_index(n);

        ui->lineEdit_Name->setText(m_UserInfoList.at(n).name);
        ui->lineEdit_Password->setText(m_UserInfoList.at(n).password);

        ui->lineEdit_Name->setEnabled(false);
        ui->lineEdit_Password->setEnabled(false);

        DisplayPermission(m_UserInfoList.at(n).permission);

        setConfigPermissionOnUIEnabled(false);

        m_UserUIControl->set_Status(Op_Idle);
        ui->pushButton_AddUser->setVisible(true);
        ui->pushButton_Delete->setVisible(true);
        ui->pushButton_Update->setVisible(true);

        ui->pushButton_Cancel->setVisible(false);
        ui->pushButton_OK->setVisible(false);
    }
    ui->label_ForDebug->setText(strDisplay);



}

 void MainWindow::AccountTableChangeOperation(Operation_Status operation,int Index_Changed)
 {
     switch (operation)
     {
        case Op_Add:
             {
                 OneUserInfo RecordToAdd;
                 RecordToAdd.name = ui->lineEdit_Name->text().trimmed();
                 RecordToAdd.password = ui->lineEdit_Password->text().trimmed();
                 RecordToAdd.permission = 0;
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
                          ui->label_ForDebug->setText("database not open!");
                      }
                     break;
                   case AddExistRecord:
                      {
                         ui->label_ForDebug->setText("该用户名已经存在!");
                      }
                     break;
                   case AddFailed:
                      {
                         ui->label_ForDebug->setText("添加不成功,请重试!");
                      }
                     break;
                 default:
                      {
                         ui->label_ForDebug->setText("添加不成功，请重试!");
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
                RecordToUpdate.permission = 0;

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
    ui->lineEdit_Password->setEnabled(true);
    ui->lineEdit_Name->setEnabled(true);
    setConfigPermissionOnUIEnabled(true);
}

void MainWindow::on_pushButton_Update_clicked()
{
    m_UserUIControl->set_Status(Op_Update);
    ui->pushButton_AddUser->setVisible(false);
    ui->pushButton_Delete->setVisible(false);
    ui->pushButton_Update->setVisible(false);

    ui->pushButton_Cancel->setVisible(true);
    ui->pushButton_OK->setVisible(true);

    ui->lineEdit_Password->setEnabled(true);
    setConfigPermissionOnUIEnabled(true);

}


void MainWindow::on_pushButton_Delete_clicked()
{
     m_UserUIControl->set_Status(Op_Delete);
     ui->pushButton_AddUser->setVisible(false);
     ui->pushButton_Delete->setVisible(false);
     ui->pushButton_Update->setVisible(false);

     ui->pushButton_Cancel->setVisible(true);
     ui->pushButton_OK->setVisible(true);
     ui->lineEdit_Password->setEnabled(false);
     ui->lineEdit_Name->setEnabled(false);
     setConfigPermissionOnUIEnabled(false);
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    m_UserUIControl->set_Status(Op_Idle);
    ui->pushButton_AddUser->setVisible(true);
    ui->pushButton_Delete->setVisible(true);
    ui->pushButton_Update->setVisible(true);

    ui->pushButton_Cancel->setVisible(false);
    ui->pushButton_OK->setVisible(false);
    ui->lineEdit_Password->setEnabled(false);
    ui->lineEdit_Name->setEnabled(false);
    setConfigPermissionOnUIEnabled(false);
}



void MainWindow::on_pushButton_OK_clicked()
{

    QString UserName = ui->lineEdit_Name->text().trimmed();
    QString PassWord = ui->lineEdit_Password->text().trimmed();

    //currentRecord.permission = 0xff<<PERMISSION_SHIFT_INVALID;

    m_UserUIControl->set_Name(UserName);
    m_UserUIControl->set_Password(PassWord);

    Operation_Result result = m_UserUIControl->ProcessOKEvent();

    m_UserUIControl->set_Status(Op_Idle);
    ui->pushButton_AddUser->setVisible(true);
    ui->pushButton_Delete->setVisible(true);
    ui->pushButton_Update->setVisible(true);

    ui->pushButton_Cancel->setVisible(false);
    ui->pushButton_OK->setVisible(false);

    ui->lineEdit_Password->setEnabled(false);
    ui->lineEdit_Name->setEnabled(false);
    setConfigPermissionOnUIEnabled(false);

    OneUserInfo tempOneRecord;
    OneUserInfo * ptr_currentRecord = m_UserUIControl->getCurrentRecord();
    int index = m_UserUIControl->getIndex();
    switch (result)
    {
    case AddSuccess:
    {
        ui->label_ForDebug->setText("添加成功");
        tempOneRecord.name = ptr_currentRecord->name;
        tempOneRecord.password = ptr_currentRecord->password;
        tempOneRecord.permission = ptr_currentRecord->permission;
        m_UserInfoList.append(tempOneRecord);
        QTreeWidgetItem * itemToAddInNameTree = new QTreeWidgetItem(QStringList()<<tempOneRecord.name);
        m_NameTreeItems->addChild(itemToAddInNameTree);
        m_UserInfoTree->itemClicked(m_NameTreeItems,0);
        m_UserInfoTree->collapseAll();
     }
        break;
    case UpdateSuccess:
        ui->label_ForDebug->setText("修改成功");
        tempOneRecord.name = ptr_currentRecord->name;
        tempOneRecord.password = ptr_currentRecord->password;
        tempOneRecord.permission = ptr_currentRecord->permission;
        m_UserInfoList.removeAt(index);
        m_UserInfoList.insert(index,tempOneRecord);
        break;
    case DeleteSuccess:
        ui->label_ForDebug->setText("删除成功");
        m_UserInfoList.removeAt(index);
        delete m_NameTreeItems->takeChild(index);
        m_UserInfoTree->collapseAll();
        break;
    case DataBaseNotOpen:
        ui->label_ForDebug->setText("数据库没有打开");
        break;
    case AddExistRecord:
        ui->label_ForDebug->setText("想要添加的用户名已经存在");
        break;
    case AddFailed:
    case UpdateFailed:
    case DeleteFailed:
        ui->label_ForDebug->setText("操作失败");
        break;
    case DeleteNotExistRecord:
        ui->label_ForDebug->setText("想要删除的用户不存在");
        break;
    default:
        break;
    }

}

void MainWindow::PermissionChanged(int id)
{
    uint value = id;//value of permission equals to id
    //00:no permission; 01:readonly; 10:readwrite;
    int shifting = -1;
    if(sender() == m_UserRadioGroup)
    {
        shifting = PERMISSION_SHIFT_USER;
    }
    else if(sender() == m_SergeantRadioGroup)
    {
        shifting =  PERMISSION_SHIFT_SERGEANT;
    }
    else if(sender() == m_CadresRadioGroup)
    {
        shifting = PERMISSION_SHIFT_CADRES;
    }

    m_UserUIControl->set_Permission(value,shifting);


}

void MainWindow::UserUI_Init(void)
{
    //initial the member values.
    m_AccountTable = new CAccountTable("PersonInfo","Account");
    AccountTable_has_readout = false;
    m_UserInfoList = UserInfoList();
    m_UserUIControl = new CUserManage_UIControl(m_AccountTable);

    //for trees to display names.
    m_UserInfoTree = ui->treeWidget_Names;
    m_UserInfoTree->setHeaderHidden(true);
    connect(m_UserInfoTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(showPermission(QTreeWidgetItem*,int)));
    m_NameTreeItems = 0;


    //for radios to display and config the permission
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

    connect(m_UserRadioGroup,SIGNAL(buttonClicked(int)),this,SLOT(PermissionChanged(int)));
    connect(m_SergeantRadioGroup,SIGNAL(buttonClicked(int)),this,SLOT(PermissionChanged(int)));
    connect(m_CadresRadioGroup,SIGNAL(buttonClicked(int)),this,SLOT(PermissionChanged(int)));

    //initial the buttons
    m_UserUIControl->set_Status(Op_Idle);
    ui->pushButton_AddUser->setVisible(true);
    ui->pushButton_Delete->setVisible(true);
    ui->pushButton_Update->setVisible(true);

    ui->pushButton_Cancel->setVisible(false);
    ui->pushButton_OK->setVisible(false);
    ui->lineEdit_Password->setEnabled(false);
    ui->lineEdit_Name->setEnabled(false);

    setConfigPermissionOnUIEnabled(false);

    ui->tabWidget->currentChanged(0);
}

void MainWindow::DisplayPermission(uint permission)
{
    uint per_user = (permission>>PERMISSION_SHIFT_USER) & 0x03;
    uint per_sergeant =  (permission>>PERMISSION_SHIFT_SERGEANT) & 0x03;
    uint per_cadres = (permission>>PERMISSION_SHIFT_CADRES) & 0x03;

    m_UserRadioGroup->button(per_user)->setChecked(true);
    m_SergeantRadioGroup->button(per_sergeant)->setChecked(true);
    m_CadresRadioGroup->button(per_cadres)->setChecked(true);

}

void MainWindow::setConfigPermissionOnUIEnabled(bool enable_or_not)
{
    int i = 0;
    for(i=0;i<3;i++)
    {
        m_UserRadioGroup->button(i)->setEnabled(enable_or_not);
        m_SergeantRadioGroup->button(i)->setEnabled(enable_or_not);
        m_CadresRadioGroup->button(i)->setEnabled(enable_or_not);
    }
}
