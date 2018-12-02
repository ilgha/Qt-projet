#ifndef MECH_H
#define MECH_H

#include "Player.h"

#include "Unit.h"

class Mech : public Unit{
public:
Mech(int x, int y, int health, Player* team);
};
#endif //MECH_H
