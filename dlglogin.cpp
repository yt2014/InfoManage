#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QUrl>

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
    this->setFixedSize(541,557);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::yellow);
    //label->setPalette(pe);
    font.setPointSize(24);

    this->ui->label_thesis->setFont(font);
    this->ui->label_thesis->setPalette(pe);


    this->ui->label_thesis->setWindowIcon(QIcon(QPixmap("award.ico")));
    this->setWindowFlags(Qt::FramelessWindowHint);

    //this->ui->label_UserPicture->setPixmap(QPixmap("login_user_24x24.png"));
    QPalette pe1;
    pe1.setColor(QPalette::Background,Qt::white);
    //ui->label_UserPicture->setPalette(pe1);
    ui->label_UserImage->setPalette(pe1);
    //ui->label_UserPicture->setAutoFillBackground(true);
    ui->label_UserImage->setAutoFillBackground(true);
    ui->label_UserImage->setPixmap(QPixmap("login_user_24x24.png"));
    //this->ui->lineEdit_User->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_UserInput->setFocus();


    ui->label_PwdImage->setPixmap(QPixmap("login_psw_24x24.png"));
    ui->label_PwdImage->setPalette(pe1);
    ui->label_PwdImage->setAutoFillBackground(true);



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
    if((ui->lineEdit_UserInput->text().trimmed() == tr("admin"))
            &&(ui->lineEdit_PwdInput->text().trimmed() == tr("admin")))
    {
        accept();

    }
    else
    {
            // QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
              QMessageBox::warning(this,tr("warning"),tr("username or password are not correct!"),QMessageBox::Ok);
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
