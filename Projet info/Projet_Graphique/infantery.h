#ifndef INFANTERY_H
#define INFANTERY_H
#include "player.h"
#include "unit.h"
class Infantery : public Unit{
public:
Infantery(int x, int y, int health, int mp, Player* team);
};
#endif //INFANTERY_H
