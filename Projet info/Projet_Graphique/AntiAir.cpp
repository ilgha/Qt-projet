#include "AntiAir.h"
#include <string>
using std::string;

AntiAir::AntiAir(int x,int y, int health, Player* team ):
    Unit(x, y, health, 10,  6, "tr", team, 0){
}


