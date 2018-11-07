<<<<<<< HEAD
#include "MdTank.h"
#include <string>
using std::string;

MdTank::MdTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y,health, 10,  mp,  5, "tr", 16000, team, 5){
}
=======
#include "MdTank.h"
#include <string>
using std::string;

MdTank::MdTank(int x,int y, int health,int mp, Player* team):
    Unit( x,  y,health, 10,  mp,  5, "tr", team, 5){
}
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
