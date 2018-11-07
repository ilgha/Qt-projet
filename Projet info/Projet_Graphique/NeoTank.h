#ifndef NEOTANK_H
#define NEOTANK_H
#include "Player.h"
#include "unit.h"
class NeoTank : public Unit {
public:
NeoTank(int x, int y, int health, int mp, Player* team);
};
#endif // NEOTANK_H
