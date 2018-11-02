#ifndef PROJECT_BCOPTER_H
#define PROJECT_BCOPTER_H
#include "Player.h"
#include "unit.h"
class BCopter : public Unit {
public:
BCopter(int x, int y, int health, int mp, Player* team);
};

#endif //PROJECT_BCOPTER_H
