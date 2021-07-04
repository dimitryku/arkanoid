#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->MainGameField = new GameField();
    ui->verticalLayout->addWidget(MainGameField);

    ScoreTimer = new QTimer(this);
    connect(ScoreTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::UpdateScore));
    ScoreTimer->start(PublicConstants::DefaultTimerTick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateScore()
{
    this->statusBar()->showMessage(QString("Score: %1").arg(MainGameField->GetScore()));
}

