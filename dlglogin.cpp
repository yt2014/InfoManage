#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QMessageBox>
#include <QString>

DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    ui->setupUi(this);

//begin setting the window gui.
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

    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::yellow);
   //label->setPalette(pe);
    font.setPointSize(24);

    this->ui->label_thesis->setFont(font);
    this->ui->label_thesis->setPalette(pe);

    this->setWindowFlags(Qt::FramelessWindowHint);

    //this->ui->label_UserPicture->setPixmap(QPixmap("login_user_24x24.png"));
    QPalette pe1;
    pe1.setColor(QPalette::Background,Qt::white);
    //ui->label_UserPicture->setPalette(pe1);
    ui->label_UserImage->setPalette(pe1);
    //ui->label_UserPicture->setAutoFillBackground(true);
    ui->label_UserImage->setAutoFillBackground(true);
    ui->label_UserImage->setPixmap(QPixmap(":/image/photos/login_user_24x24.png"));
    //this->ui->lineEdit_User->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_UserInput->setFocus();


    ui->label_PwdImage->setPixmap(QPixmap(":/image/photos/login_psw_24x24.png"));
    ui->label_PwdImage->setPalette(pe1);
    ui->label_PwdImage->setAutoFillBackground(true);
//end setting the window gui.
    db = QSqlDatabase::database("PersonInfo",true);

    if(db.isValid()&&db.isOpen())
    {
        ui->label_indications->setText("database opened successfully!");
    }
    else
    {
        ui->label_indications->setText("can't open database!");
    }



}

DlgLogin::~DlgLogin()
{
    delete ui;
    db.close();
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
    QString name = ui->lineEdit_UserInput->text().trimmed();
    QString password = ui->lineEdit_PwdInput->text().trimmed();

    QString strSelect = "select * from [Account] where [UserName] = '" + name + "' and [password] = '" + password + "'";

    if(db.isOpen())
    {
        QSqlQuery QueryForSelect(db);

        if(QueryForSelect.exec(strSelect))
        {
            if(QueryForSelect.size() == 0)
            {
                QMessageBox::warning(this,tr("warning"),tr("username or password are not correct!"),QMessageBox::Ok);
                this->ui->lineEdit_User->clear();
                this->ui->lineEdit_Pwd->clear();
            }
            else
            {
                accept();
            }

        }
        else
        {
            QMessageBox::warning(this,tr("warning"),tr("dabase operation failed"),QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::warning(this,tr("warning"),tr("database is not open"),QMessageBox::Ok);
    }

    /*if((ui->lineEdit_UserInput->text().trimmed() == tr("admin"))
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
    }*/

}


void DlgLogin::on_PushBtnCancel_clicked()
{
    reject();
}
