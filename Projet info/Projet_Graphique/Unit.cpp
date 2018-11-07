#include "unit.h"
#include <string>
using std::string;





Unit::Unit(int posX, int posY, int health, int healthMax, int mp, int mpMax, string mt, Player* team, int ID) {
    x = posX;
    y = posY;
    this->health = health;
    this->healthMax = healthMax;
    this->mp = mp;
    this->mpMax = mpMax;
    this->mt = mt;

    this->team = team;
    this->ID = ID;
}

void Unit::setDead(bool value)
{
    dead = value;
}

bool Unit::getDead() const
{
    return dead;
}

int Unit::getHealthMax() const
{
    return healthMax;
}

void Unit::setHealthMax(int value)
{
    healthMax = value;
}

int Unit::getX() const {
    return x;
}

int Unit::getY() const {
    return y;
}

int Unit::getHealth() const {
    return health;
}

int Unit::setHealth(int newHp){
    health += newHp;
    if(health >= healthMax){
        health = healthMax;
    }
    return health;
}

int Unit::getMP() const {
    return mp;
}

string Unit::getMT() const {
    return mt;
}

Player* Unit::getTeam() const {
    return team;
}

void Unit::setX(int x){
    this->x = x;
}
void Unit::setY(int y){
    this->y = y;
}

void Unit::newTurn(){
    mp = mpMax;
}
void Unit::setMovable(bool b)
{
    movable = b;
}

bool Unit::isMovable()
{
    return  movable;
}

int Unit::getDamage(Unit * unitA, Unit * unitD) {

    int damageChart[11][11] = {{45,120,75,65,105,10,105,1,5,60,25},
                               {25,65,0,0,75,25,75,10,20,55,55},
                               {95,0,0,0,110,95,110,35,90,105,105},
                               {0,100,100,55,0,0,0,0,0,0,0},
                               {5,7,0,0,55,1,45,1,1,12,5},
                               {105,12,0,0,105,55,95,25,45,105,85},
                               {65,9,0,0,65,15,55,5,15,85,55},
                               {195,22,0,0,135,125,125,65,115,195,180},
                               {115,22,0,0,125,75,115,35,55,125,105},
                               {4,12,0,0,70,1,65,1,1,35,6},
                               {65,10,0,0,75,15,70,10,15,85,55}};

    int IDA = unitA->ID;
    int IDD = unitD->ID;

    if (damageChart[IDA][IDD] >0 ){
        int B = damageChart[IDA][IDD];
        int A_HP = unitA->health;
        int D_HP = unitD->health;
        string typeD = unitD->mt;
        if (typeD == "a"){
            int D_TR = 0;
        }
        else{
            int PosXD = unitD->x;
            int PosYD = unitD->y;
            //Comment identifier le type de terrain?
            int D_TR = 0;
        }
//        int damage =  B * A_HP / 10 * (100 - D_TR * D_HP) / 100;
//        return damage;
//    }
//    else{
//       cout << "L'unité ne peut pas attaquer ce genre d'unités" << endl;
        return 0;
    }
}
