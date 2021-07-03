#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //view = new GameView(this, game);
    ui->verticalLayout->setGeometry(QRect(0,0,1000,900));
    ui->verticalLayout->addWidget(new GameField());
}

MainWindow::~MainWindow()
{
    delete ui;
}

