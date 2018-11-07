
#include "MdTank.h"

MdTank::MdTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y,health, 10,  mp,  5, "tr",team, 5){
}
