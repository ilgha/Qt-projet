#ifndef PROJECT_BOMBER_H
#define PROJECT_BOMBER_H
#include "Player.h"
#include "unit.h"
class Bomber : public Unit {

public:
Bomber(int x, int y, int health, int mp , Player* team);
};
#endif //PROJECT_BOMBER_H
