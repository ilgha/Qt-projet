<<<<<<< HEAD
#include "infantery.h"
#include <string>
using std::string;


Infantery::Infantery(int x, int y, int health, int mp, Player* team):
    Unit(x, y, health, 10, mp, 3, "f",1000, team, 1){
}
=======
#include "infantery.h"
#include <string>
using std::string;


Infantery::Infantery(int x, int y, int health, int mp, Player* team):
    Unit(x, y, health, 10, mp, 3, "f", team, 1){
}
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
