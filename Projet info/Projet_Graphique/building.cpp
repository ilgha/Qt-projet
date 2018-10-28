#include "building.h"

int Building::getHp() const{
    return hp;
}

Player* Building::getTeam() const{
    return team;
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
    }
    return team;
}

int Building::setHp(Unit* unit) {
    hp = hp+unit->getHealth();
    if(hp <= 0){
        switchTeam(unit->getTeam());
    }
    return hp;
}

void Building::reset() {
    hp = maxHp;
}
