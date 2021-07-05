#ifndef BONUS_H
#define BONUS_H
#include <bonus/bonuses.h>
#include <random>
#include <time.h>
#include <QObject>
#include <publicconstants.h>
#include "QTimer"
#include <iostream>
class Bonus : public QObject
{
    Q_OBJECT
public:
    Bonus(int positive_chance);
    Bonus(const Bonus& obj);
    Bonus();
    Bonuses getTypeBonus();
    Bonuses  start();
    void  operator =(const Bonus& obj);

signals:
    void increaseSizePlatform(bool finished); //Сигнал на увеличение ракетки
    void decreaseSizePlatform(bool finished); //Сигнал на уменьшение ракетки
    void increaseSpeedBall();    //Сигнал на увеличение скорости шара
    void decreaseSpeedBall();    //Сигнал на уменьшение скорости шара
    void addNewBall();          //Сигнал на добавление еще шара
    void setUberBall();         //Сигнал на то чтобы сделать шар усиленным
    void setCommonBall();       //Сигнал на то чтобы вернуть изначальный шар
    void changeInverse();       //Сигнал на инверсию управления
    void changeStickness();     //Сигнал на прилипание к ракетке
    void setMagnet();           //Сигнал на магнитный шар
    void addLife();             //Сигнал на новую жизнь
    void stop(Bonus* bonus);

private slots:
      void tick();

private:
    Bonuses type_bonus;
    int lifetime=15*1000; //15 секунд
    QTimer* timer;
    bool finish_signal=false;

};

#endif // BONUS_H
