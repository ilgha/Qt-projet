<<<<<<< HEAD
#include "Bomber.h"
#include <string>
using std::string;

Bomber::Bomber(int x,int y, int health,int mp,Player* team ):
    Unit( x,  y, health, 10,  mp, 7, "a", 22000,team, 2){
}
=======
#include "Bomber.h"
#include <string>
using std::string;

Bomber::Bomber(int x,int y, int health,int mp,Player* team ):
    Unit( x,  y, health, 10,  mp, 7, "a",team, 2){
}
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
