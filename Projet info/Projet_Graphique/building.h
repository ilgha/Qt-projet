#ifndef BUILDING_H
#define BUILDING_H


#include "Unit.h"
#include "player.h"
#include "Land.h"

class Building : public Land{
    Player* team = nullptr;
    int x, y, hp, ID;
    Player* switchTeam(Player* team);

    int maxHp = 20;
    int income = 1000;
public:
    Building(int posX, int posY, int defence, int f, int b, int tr, int ti, int a, int ID);
    Player* getTeam() const ;
    int getHp() const ;
    int getX() const;
    int getY() const;
    int getID() const;
    int setHp(Unit* unit);
    void reset();
};

#endif // BUILDING_H

