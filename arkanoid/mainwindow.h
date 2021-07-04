#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gamefield.h>
#include <QTimer>
#include <QMessageBox>
#include <QInputDialog>

class GameField;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_game_triggered();

private:
    Ui::MainWindow *ui;
    GameField* MainGameField;

    QTimer* ScoreTimer;
    void UpdateScore();
    void onGameEnded();
};
#endif // MAINWINDOW_H
