#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene scene;

   // scene.addPixmap(QPixmap("login_user24x24.png"));

    scene.addText("your are so daomei");

 //   QGraphicsView *view = new QGraphicsView(&scene,this);

  //  view->show();

    ui->graphicsView->setScene(&scene);

    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
