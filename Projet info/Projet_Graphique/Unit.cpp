#include "unit.h"
#include <string>
using std::string;

Unit::Unit(int posX, int posY, int health, int healthMax, int mp, int mpMax, string mt, Player* team) {
    x = posX;
    y = posY;
    this->health = health;
    this->healthMax = healthMax;
    this->mp = mp;
    this->mpMax = mpMax;
    this->mt = mt;
    this->team = team;
}


Unit::~Unit() {
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

void Unit::fusion(Unit* unit){

}
