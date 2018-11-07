#include "AntiAir.h"
#include <string>
using std::string;

AntiAir::AntiAir(int x,int y, int health,int mp, Player* team ):
    Unit(x, y, health, 10,  mp,  6, "tr", team, 0){
}


