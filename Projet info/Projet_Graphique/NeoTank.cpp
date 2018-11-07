<<<<<<< HEAD
#include "NeoTank.h"
#include <string>
using std::string;

NeoTank::NeoTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y, health, 10, mp, 6, "tr",22000,team, 8){
};
=======
#include "NeoTank.h"
#include <string>
using std::string;

NeoTank::NeoTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y, health, 10, mp, 6, "tr",team, 8){
};
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
