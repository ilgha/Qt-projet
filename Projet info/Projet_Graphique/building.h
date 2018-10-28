#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"
#include "Player.h"
#include "Land.h"

class Building : public Land{
    Player* team = nullptr;
    int hp;
    Player* switchTeam(Player* team);
    void reset();
    int maxHp = 20;
    int income = 1000;
public:
    Player* getTeam() const ;
    int getHp() const ;
    int setHp(Unit* unit);
    int addHp(int newHp, Unit* unit);

};

#endif // BUILDING_H
