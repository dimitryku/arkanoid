#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gamefield.h>
#include <QTimer>
#include <QMessageBox>
#include <QInputDialog>
#include <vector>
#include <algorithm>
#include <QFile>
#include <QDataStream>

class GameField;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Score
    {
        int points = 0;
        QString name = "";
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_game_triggered();

    void on_actionLeaderboard_triggered();

private:
    Ui::MainWindow *ui;
    GameField* MainGameField;


    QTimer* ScoreTimer;
    void UpdateScore();
    void onGameEnded();


    std::vector<Score> leaderboard;

    void LoadScore();
    void StoreScore();
    void AddScore(Score newScore);
    void ShowHighScore();
    void OrganizeHighscore();
};
#endif // MAINWINDOW_H
