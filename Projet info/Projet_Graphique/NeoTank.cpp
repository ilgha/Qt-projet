#include "NeoTank.h"


NeoTank::NeoTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y, health, 10, mp, 6, "tr",team, 8){
};

