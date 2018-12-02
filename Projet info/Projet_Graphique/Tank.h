#ifndef TANK_H
#define TANK_H

#include "player.h"
#include "Unit.h"

class Tank : public Unit {
public:
Tank(int x, int y, int health, Player* team);
};

#endif // TANK_H
