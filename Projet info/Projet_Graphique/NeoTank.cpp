#include "NeoTank.h"
#include <string>
using std::string;

NeoTank::NeoTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y, health, 10, mp, 6, "tr",22000,team, 8){
};
