#ifndef BUILDING_H
#define BUILDING_H

#include "unit.h"
#include "Player.h"
#include "Land.h"

class Building : public Land{
    Player* team = nullptr;
    int x, y, hp;
    Player* switchTeam(Player* team);
    void reset();
    int maxHp = 20;
    int income = 1000;
public:
    Building(int posX, int posY, int defence, int f, int b, int tr, int ti, int a);
    Player* getTeam() const ;
    int getHp() const ;
    int getX() const;
    int getY() const;
    int setHp(Unit* unit);
    int addHp(int newHp, Unit* unit);

};

#endif // BUILDING_H
