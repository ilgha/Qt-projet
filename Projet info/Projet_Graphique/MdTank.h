#ifndef MDTANK_H
#define MDTANK_H

#include "Player.h"

#include "Unit.h"
class MdTank : public Unit {
public:
MdTank(int x, int y, int health, Player* team);
};
#endif //MDTANK_H
