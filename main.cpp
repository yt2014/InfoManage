#include "mainwindow.h"
#include "dlglogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
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
