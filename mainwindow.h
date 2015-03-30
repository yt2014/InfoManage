#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AccountTable.h"
#include "usermanage_uicontrol.h"
#include "QTreeWidget.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);
    void showPermission(QTreeWidgetItem* treeItem,int index);    

private:
    Ui::MainWindow *ui;
    QTreeWidget * m_UserInfoTree;
    QTreeWidgetItem *m_NameTreeItems;


    CAccountTable * m_AccountTable;
    UserInfoList m_UserInfoList;
    bool AccountTable_has_readout;
    CUserManage_UIControl * m_UserUIControl;
};

#endif // MAINWINDOW_H
