#ifndef MECH_H
#define MECH_H
#include "player.h"
#include "unit.h"

class Mech : public Unit{
public:
Mech(int x, int y, int health, int mp, Player* team);
};
#endif //MECH_H
