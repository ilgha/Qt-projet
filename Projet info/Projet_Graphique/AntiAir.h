#ifndef ANTIAIR_H
#define ANTIAIR_H
#include "Player.h"
#include "unit.h"

class AntiAir : public Unit {
public:
AntiAir(int x, int y, int health, int mp,Player* team);
};
#endif //ANTIAIR_H
