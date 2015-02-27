#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QMessageBox>

DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    ui->setupUi(this);


    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    palette.setBrush(QPalette::Background, QBrush(QPixmap("army.png")));

    QFont font;
    font.setBold(true);
    font.setFamily("Courier");
    font.setPointSize(14);

    this->setFont(font);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    this->setFixedSize(467,469);
}

DlgLogin::~DlgLogin()
{
    delete ui;
}

/*void DlgLogin::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok)  == button)   //check if the [OK] button are pressed
    {
        if((ui->lineEdit_User->text().trimmed() == tr("admin"))
                &&(ui->lineEdit_Pwd->text().trimmed() == tr("admin")))
        {
            accept();

        }
        else
        {
                // QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
                //  QMessageBox::warning(this,tr("warning"),tr("username or password are not correct!"),QMessageBox::Yes);
                  this->ui->lineEdit_User->clear();
                  this->ui->lineEdit_Pwd->clear();
                  //reject();
                  this->show();
                  //this->ui->txtname->setFocus();
        }

    }
    else if(button == ui->buttonBox->button((QDialogButtonBox::Cancel)))
    {
        reject();
    }
}
*/
void DlgLogin::on_PushBtnOK_clicked()
{
    if((ui->lineEdit_User->text().trimmed() == tr("admin"))
            &&(ui->lineEdit_Pwd->text().trimmed() == tr("admin")))
    {
        accept();

    }
    else
    {
            // QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
              QMessageBox::warning(this,tr("warning"),tr("username or password are not correct!"),QMessageBox::Yes);
              this->ui->lineEdit_User->clear();
              this->ui->lineEdit_Pwd->clear();
              //reject();
              //this->show();
              //this->ui->txtname->setFocus();
    }

}


void DlgLogin::on_PushBtnCancel_clicked()
{
    reject();
}
