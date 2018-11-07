<<<<<<< HEAD
#include "Fighter.h"
#include <string>
using std::string;

Fighter::Fighter(int x,int y, int health,int mp,Player* team ):
    Unit( x,  y, health,  10,  mp,  9,  "a", 20000, team,3){
}
=======
#include "Fighter.h"
#include <string>
using std::string;

Fighter::Fighter(int x,int y, int health,int mp,Player* team ):
    Unit( x,  y, health,  10,  mp,  9,  "a", team,3){
}
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
