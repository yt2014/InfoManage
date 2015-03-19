#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

namespace Ui {
class DlgLogin;
}

class DlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLogin(QWidget *parent = 0);
    ~DlgLogin();

private slots:
  //  void on_buttonBox_clicked(QAbstractButton *button);

    void on_PushBtnOK_clicked();

    void on_PushBtnCancel_clicked();

private:
    Ui::DlgLogin *ui;

    QSqlDatabase db;
};

#endif // DLGLOGIN_H
