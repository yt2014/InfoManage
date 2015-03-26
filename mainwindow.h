#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AccountTable.h"
#include "QTreeWidget.h"

namespace Ui {
class MainWindow;
}



typedef enum
{
    Data_ADD,
    Data_UPDATE,
    Data_REDUCE
}Change_Operation;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);
    void showPermission(QTreeWidgetItem* treeItem,int index);    
    void AccountTableChangeOperation(Change_Operation operation,int Index_Changed);

private:
    Ui::MainWindow *ui;

    CAccountTable * m_AccountTable;
    UserInfoList m_UserInfoList;
    bool AccountTable_has_readout;
    QTreeWidget * m_UserInfoTree;
    QTreeWidgetItem *m_NameTreeItems;
};

#endif // MAINWINDOW_H
