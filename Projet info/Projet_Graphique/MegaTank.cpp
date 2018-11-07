#include "MegaTank.h"
#include <string>
using std::string;

MegaTank::MegaTank(int x,int y, int health,int mp, Player* team):
    Unit(x, y,health, 10, mp, 4, "tr", 28000,team, 7){
};
