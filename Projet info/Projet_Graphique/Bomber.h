#ifndef BOMBER_H
#define BOMBER_H
#include "Player.h"
#include "unit.h"
class Bomber : public Unit {

public:
Bomber(int x, int y, int health, int mp , Player* team);
};
#endif //BOMBER_H
