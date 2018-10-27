#include "Unit.h"
#include <string>
using std::string;

Unit::Unit(int posX, int posY, int health, int healthMax, int mp, int mpMax, string mt, int cost, Player* team) {
    x = posX;
    y = posY;
    this->health = health;
    this->healthMax = healthMax;
    this->mp = mp;
    this->mpMax = mpMax;
    this->mt = mt;
    this->cost = cost;
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

int Unit::getCost() const {
    return cost;
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
