#ifndef PROJECT_INFANTERY_H
#define PROJECT_INFANTERY_H
#include "Player.h"
#include "unit.h"
class Infantery : public Unit{
public:
Infantery(int x, int y, int health, int mp,int cost, Player* team);
};
#endif //PROJECT_INFANTERY_H
