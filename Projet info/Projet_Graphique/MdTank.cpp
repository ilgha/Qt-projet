#include "MdTank.h"
#include <string>
using std::string;

MdTank::MdTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y,health, 10,  mp,  5, "tr", 16000, team, 5){
}
