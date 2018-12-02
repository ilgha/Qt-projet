
#include "infantery.h"
#include <string>
using std::string;


Infantery::Infantery(int x, int y, int health, Player* team):
    Unit(x, y, health, 10, 3, "f",team, 4){
}

