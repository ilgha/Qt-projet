#include "infantery.h"
#include <string>
using std::string;


Infantery::Infantery(int x, int y, int health, int mp, int cost, Player* team):
    Unit(x, y, health, 10, mp, 3, "f", 1000, team){
}
