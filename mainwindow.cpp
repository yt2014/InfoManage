#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene scene;

    scene.addPixmap(QPixmap("award.ico"));

    QGraphicsView *view = new QGraphicsView(&scene,this);

    view->show();

   // ui->graphicsView->setScene(&scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}
