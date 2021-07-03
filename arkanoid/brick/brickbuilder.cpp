#include "brickbuilder.h"

BrickBuilder::BrickBuilder(int row, int col)
{
    srand(time(0));
    if(col<=0)
        num_lastColum =  PublicConstants::SceneRect.width()/PublicConstants::BrickSize.x();
    else
        num_lastColum = col;
    num_lastRow = row;
    coord.setX(-1);
    coord.setY(0);


}

Brick* BrickBuilder::makeBrick()
{
     reset();
    int random = rand() % 100 + 1;
    Brick* brick = NULL;
    int type;

    if(coord.x() == num_lastColum && coord.y() == num_lastRow)
        return brick;

    if(random <= 40)
        type = 1;
    else if(random <= 75)
        type = 2;
    else if(random <= 80)
        type = 3;
    else if(random <= 85)
        type = 4;
    else
        type = 5;

    if(not_metallic && type == 5){
        type = rand() % 4 + 1;
    }

    switch (type) {

    case 1: brick = new CommonBrick(QVector2D(coord.x() * PublicConstants::BrickSize.x(),coord.y()* PublicConstants::BrickSize.y()), 1);                 break; /* Create NormalBrick */

    case 2: brick = new CommonBrick(QVector2D(coord.x() * PublicConstants::BrickSize.x(),coord.y()* PublicConstants::BrickSize.y()), rand() % 8 + 3);    break; /* Create StrongBrick (CommonBrick with hp>2)*/

    case 3: brick = new GoldenBrick(QVector2D(coord.x() * PublicConstants::BrickSize.x(),coord.y()* PublicConstants::BrickSize.y()));                    break; /* CreateBonusBrick */

    case 4: brick = new TNTBrick(QVector2D(coord.x() * PublicConstants::BrickSize.x(),coord.y()* PublicConstants::BrickSize.y()));                       break; /* Create BoomBrick */

    case 5: brick = new MetallicBrick(QVector2D(coord.x() * PublicConstants::BrickSize.x(),coord.y()* PublicConstants::BrickSize.y()));                  break; /* Create MetallicBrick  */

    }

    if(type == 5){
        not_metallic = true;
    } else
        not_metallic = false;

    return brick;

    //TO DO
}

//empty brackets == max
std::vector<Brick*> BrickBuilder::makeBricks(int quantity)
{
    quantity = quantity == -1 ?  num_lastColum * num_lastRow : quantity;
    std::vector<Brick*> bricks;

    for(int i = 0; i < quantity; i++){
        Brick* temp_br = makeBrick();

        if(temp_br != NULL)
            bricks.push_back(temp_br);

    }

    return bricks;
}

void BrickBuilder::reset()
{
    coord.setX(coord.x() + 1);
    if(coord.x() == num_lastColum){
        coord.setX(0);
        coord.setY(coord.y() + 1);
        not_metallic=false;
    }

}
