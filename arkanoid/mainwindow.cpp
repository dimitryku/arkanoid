#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->MainGameField = new GameField();
    ui->verticalLayout->addWidget(MainGameField);
    connect(MainGameField, &GameField::GameEnded, this, QOverload<>::of(&MainWindow::onGameEnded));

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
    this->statusBar()->showMessage(QString("Score: %1   Lives: %2")
                                   .arg(MainGameField->getScore()).arg(MainGameField->getLives()));
}


void MainWindow::on_actionNew_game_triggered()
{
    ScoreTimer->stop();
    ui->verticalLayout->removeWidget(MainGameField);
    disconnect(MainGameField, &GameField::GameEnded, this, QOverload<>::of(&MainWindow::onGameEnded));
    delete MainGameField;


    this->MainGameField = new GameField();
    ui->verticalLayout->addWidget(MainGameField);
    QTimer::singleShot(0, MainGameField, SLOT(setFocus()));
    connect(MainGameField, &GameField::GameEnded, this, QOverload<>::of(&MainWindow::onGameEnded));
    ScoreTimer->start(PublicConstants::DefaultTimerTick);
}

void MainWindow::onGameEnded()
{
    QMessageBox msgBox(this);
    msgBox.setText(QString("Game over! Your score is %1").arg(MainGameField->getScore()));
    msgBox.exec();

    bool ok;
        QString text = QInputDialog::getText(this, tr("New record!"),
                                             tr("Your name:"), QLineEdit::Normal,
                                             "anon", &ok);
        if (ok && !text.isEmpty()){

        }

    /// TODO
}
