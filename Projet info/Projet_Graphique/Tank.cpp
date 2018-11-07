<<<<<<< HEAD

#include "Tank.h"
#include <string>
using std::string;

Tank::Tank(int x,int y, int health,int mp, Player* team ):
    Unit( x,  y, health,10, mp, 6,"tr",7000,team,10){
};
=======

#include "Tank.h"
#include <string>
using std::string;

Tank::Tank(int x,int y, int health,int mp, Player* team ):
    Unit( x,  y, health,10, mp, 6,"tr",team,10){
};
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
