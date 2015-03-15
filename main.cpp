#include "mainwindow.h"
#include "dlglogin.h"
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //set database------
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","PersonInfo");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=PersonInfo.mdb");

    //w.show();
    DlgLogin login;

    if(login.exec()==QDialog::Accepted)
    {
       w.show();
       return a.exec();
    }
    else
    {
        return 0;
    }

   // return a.exec();
}
