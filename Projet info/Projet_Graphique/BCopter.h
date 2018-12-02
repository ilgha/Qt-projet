#ifndef BCOPTER_H
#define BCOPTER_H

#include "Player.h"

#include "Unit.h"
class BCopter : public Unit {
public:
BCopter(int x, int y, int health, Player* team);
};

#endif //BCOPTER_H
