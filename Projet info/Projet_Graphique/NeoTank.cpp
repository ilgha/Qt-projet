
#include "NeoTank.h"


NeoTank::NeoTank(int x,int y, int health, Player* team):
    Unit( x,  y, health, 10, 6, "tr",team, 8){
};
