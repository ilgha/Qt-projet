
#include "MdTank.h"

MdTank::MdTank(int x,int y, int health, Player* team):
    Unit( x,  y,health, 10,  5, "tr",team, 5){
}
