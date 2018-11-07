#ifndef FIGHTER_H
#define FIGHTER_H
#include "player.h"
#include "unit.h"

class Fighter : public Unit{
public:
Fighter(int x, int y, int health, int mp, Player* team);
};

#endif //FIGHTER_H
