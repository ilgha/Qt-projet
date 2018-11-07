<<<<<<< HEAD
#include "AntiAir.h"
#include <string>
using std::string;

AntiAir::AntiAir(int x,int y, int health,int mp, Player* team ):
    Unit(x, y, health, 10,  mp,  6, "tr", 8000, team, 0){
}


=======
#include "AntiAir.h"
#include <string>
using std::string;

AntiAir::AntiAir(int x,int y, int health,int mp, Player* team ):
    Unit(x, y, health, 10,  mp,  6, "tr", team, 0){
}


>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
