<<<<<<< HEAD

#include "Mech.h"
#include <string>
using std::string;

Mech::Mech(int x,int y, int health,int mp, Player* team ):
    Unit( x,  y, health,  10, mp,  2,  "b", 3000,team, 6){
};
=======

#include "Mech.h"
#include <string>
using std::string;

Mech::Mech(int x,int y, int health,int mp, Player* team ):
    Unit( x,  y, health,  10, mp,  2,  "b",team, 6){
};
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
