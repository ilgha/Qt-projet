#ifndef FIGHTER_H
#define FIGHTER_H

#include "Player.h"

#include "Unit.h"

class Fighter : public Unit{
public:
Fighter(int x, int y, int health, int mp, Player* team);
};

#endif //FIGHTER_H
