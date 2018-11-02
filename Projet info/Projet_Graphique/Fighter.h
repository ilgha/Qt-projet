#ifndef PROJECT_FIGHTER_H
#define PROJECT_FIGHTER_H
#include "Player.h"
#include "unit.h"

class Fighter : public Unit{
public:
Fighter(int x, int y, int health, int mp, Player* team);
};

#endif //PROJECT_FIGHTER_H
