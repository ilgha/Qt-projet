#ifndef MDTANK_H
#define MDTANK_H
#include "Player.h"
#include "unit.h"
class MdTank : public Unit {
public:
MdTank(int x, int y, int health, int mp, Player* team);
};
#endif //MDTANK_H
