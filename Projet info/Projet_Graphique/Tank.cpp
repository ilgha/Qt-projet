
#include "Tank.h"
#include <string>
using std::string;

Tank::Tank(int x,int y, int health,int mp, Player* team ):
    Unit( x,  y, health,10, mp, 6,"tr",7000,team,10){
};
