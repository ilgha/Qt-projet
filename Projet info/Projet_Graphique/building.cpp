#include "building.h"
#include <iostream>

Building::Building(int posX, int posY, int defence, int f, int b, int tr, int ti, int a) : Land(defence, f, b, tr, ti, a){
    hp = maxHp;
    x = posX;
    y = posY;
}

int Building::getHp() const{
    return hp;
}

Player* Building::getTeam() const{
    return team;
}

int Building::getX() const {
    return x;
}

int Building::getY() const {
    return y;
}

Player* Building::switchTeam(Player* team) {
    if(this->team == team){
        return this->team;
    }else if(this->team != nullptr){
        this->team->addIncome(-(this->income));
        this->team = team;
        this->team->addIncome(this->income);
    }else{
        this->team = team;
        this->team->addIncome(this->income);
        std::cout << "Building Captured" << std::endl;
    }
    return team;
}

int Building::setHp(Unit* unit) {
    hp = hp-unit->getHealth();
    if(hp <= 0){
        switchTeam(unit->getTeam());
    }
    return hp;
}

void Building::reset() {
    hp = maxHp;
}
