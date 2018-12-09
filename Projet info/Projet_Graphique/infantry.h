#ifndef Infantry_H
#define Infantry_H

#include "Player.h"
#include "Unit.h"
class Infantry : public Unit{
public:
Infantry(int x, int y, int health, Player* team);
};
#endif //Infantry_H
