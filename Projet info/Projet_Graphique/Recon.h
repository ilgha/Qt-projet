#ifndef RECON_H
#define RECON_H
#include "Player.h"
#include "unit.h"
class Recon : public Unit {
public:
Recon(int x, int y, int health, int mp, Player* team);
};
#endif // RECON_H
