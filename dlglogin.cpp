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
    this->setFixedSize(541,557);
    this->setWindowFlags(Qt::FramelessWindowHint);

   /* QGraphicsScene scene;
    scene.setSceneRect(ui->graphicsView->sceneRect());
    scene.addPixmap(QPixmap("login_user24x24.png"));
    this->ui->graphicsView->setScene(&scene);
    this->ui->graphicsView->show();
    */
    //palette.setBrush(QPalette::Background, QBrush(QPixmap("login_user24x24.png")));
    //this->ui->graphicsView->setBackgroundBrush(QPixmap("login_user24x24.png"));

    QGraphicsScene scene;
    scene.addText("GraphicsView rotated clockwise");

   // QGraphicsView view(&scene);
    this->ui->graphicsView->setScene(&scene);
   // view.rotate(90); // the text is rendered with a 90 degree clockwise rotation
   // view.show();

    ui->graphicsView->show();

          //  setBackgroundBrush(QPixmap("login_user24x24.png"));
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
