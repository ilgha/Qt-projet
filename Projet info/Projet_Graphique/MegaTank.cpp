
#include "MegaTank.h"
#include <string>
using std::string;

MegaTank::MegaTank(int x,int y, int health, Player* team):
    Unit(x, y,health, 10, 4, "tr", team, 7){
};

