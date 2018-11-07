

#include "Bomber.h"
#include <string>
using std::string;

Bomber::Bomber(int x,int y, int health,int mp,Player* team ):
    Unit( x,  y, health, 10,  mp, 7, "a",team, 2){
}
