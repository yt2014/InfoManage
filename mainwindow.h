#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AccountTable.h"
#include "usermanage_uicontrol.h"
#include "QTreeWidget.h"
#include <QButtonGroup>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AccountTableChangeOperation(Operation_Status operation,int Index_Changed);

private slots:
    void on_tabWidget_currentChanged(int index);
    void showPermission(QTreeWidgetItem* treeItem,int index);    

    void on_pushButton_AddUser_clicked();

    void on_pushButton_Update_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_OK_clicked();

    void PermissionChanged(int id);

private:
    Ui::MainWindow *ui;
    QTreeWidget * m_UserInfoTree;
    QTreeWidgetItem *m_NameTreeItems;
    QButtonGroup * m_UserRadioGroup;
    QButtonGroup * m_SergeantRadioGroup;
    QButtonGroup * m_CadresRadioGroup;


    CAccountTable * m_AccountTable;
    UserInfoList m_UserInfoList;
    bool AccountTable_has_readout;
    CUserManage_UIControl * m_UserUIControl;

private:
    void UserUI_Init(void);//initialize the UI of User Manage
    void DisplayPermission(uint permission);//display the detail of permission.
    void setConfigPermissionOnUIEnabled(bool enable_or_not);
};

#endif // MAINWINDOW_H
