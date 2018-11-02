#ifndef TANK_H
#define TANK_H

#include "Player.h"
#include "unit.h"

class Tank : public Unit {
public:
Tank(int x, int y, int health,int mp, Player* team);
};

#endif // TANK_H
