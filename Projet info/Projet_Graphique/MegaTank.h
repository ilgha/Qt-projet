#ifndef MEGATANK_H
#define MEGATANK_H
#include "Player.h"
#include "unit.h"

class MegaTank : public Unit {
public:
MegaTank(int x, int y, int health,int mp, Player* team);
};
#endif //MEGATANK_H
