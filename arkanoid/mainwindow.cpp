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

    Score newsc;
    newsc.name = "";
    newsc.points = MainGameField->getScore();
    AddScore(newsc);

    ShowHighScore();

        /// TODO
}

void MainWindow::LoadScore()
{

}

void MainWindow::StoreScore()
{

}

void MainWindow::AddScore(MainWindow::Score newScore)
{
    leaderboard.resize(5);
    for(auto x: leaderboard){
        if(newScore.points > x.points){
            bool ok;
            QString text = QInputDialog::getText(this, tr("New record!"),
                                                 tr("Your name:"), QLineEdit::Normal,
                                                 "anon", &ok);
            if (ok && !text.isEmpty()){
                newScore.name = text;
                leaderboard.push_back(newScore);
                SortHighscore();
                while (leaderboard.size() > 5
                       || !leaderboard[leaderboard.size()-1].name.length()) {
                    leaderboard.pop_back();
                }
            }
            break;
        }
    }
}

void MainWindow::ShowHighScore()
{
    QString rec = "";
    for(auto i = 0; i < 5; i++){
        if(leaderboard.size() - 1 < i)
            break;
        rec = rec.append(
                    QString("%1) %2  -  %3\n")
                    .arg(i + 1)
                    .arg(leaderboard[i].name)
                    .arg(leaderboard[i].points));
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Leaderbord");
    msgBox.setText(rec);
    msgBox.exec();
}

bool comp (MainWindow::Score a, MainWindow::Score b) {

  return a.points > b.points;

}

void MainWindow::SortHighscore()
{
    sort(this->leaderboard.begin(), this->leaderboard.end(), comp);
}
