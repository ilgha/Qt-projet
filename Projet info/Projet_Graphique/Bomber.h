#ifndef BOMBER_H
#define BOMBER_H
#include "Player.h"

#include "Unit.h"
class Bomber : public Unit {

public:
Bomber(int x, int y, int health, Player* team);
};
#endif //BOMBER_H
