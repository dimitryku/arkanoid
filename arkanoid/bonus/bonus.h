#ifndef BONUS_H
#define BONUS_H
#include <bonus/bonuses.h>
#include <random>
#include <time.h>
#include <QObject>
#include <publicconstants.h>
#include "QTimer"
class Bonus : QObject
{

public:
    Bonus(int positive_chance);
    Bonus(const Bonus& obj);
    Bonus();
    Bonuses getTypeBonus();
    Bonuses  start();
    void  operator =(const Bonus& obj);

signals:
    void increseSizePlatform(); //Сигнал на увеличение ракетки
    void decreseSizePlatform(); //Сигнал на уменьшение ракетки
    void increseSpeedBall();    //Сигнал на увеличение скорости шара
    void decreseSpeedBall();    //Сигнал на уменьшение скорости шара
    void addNewBall();          //Сигнал на добавление еще шара
    void setUberBall();         //Сигнал на то чтобы сделать шар усиленным
    void setCommonBall();       //Сигнал на то чтобы вернуть изначальный шар
    void changeInverse();          //Сигнал на инверсию управления
    void changeStickness();            //Сигнал на прилипание к ракетке
    void setMagnet();           //Сигнал на магнитный шар
    void addLife();             //Сигнал на новую жизнь


private slots:
      void tick();

private:
    Bonuses type_bonus;
    int lifetime=30*1000; //30 секунд
    QTimer* timer;

};

#endif // BONUS_H
