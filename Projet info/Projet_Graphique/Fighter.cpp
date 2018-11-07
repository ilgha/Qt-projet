#include "Fighter.h"
#include <string>
using std::string;

Fighter::Fighter(int x,int y, int health,int mp,Player* team ):
    Unit( x,  y, health,  10,  mp,  9,  "a", team,3){
}
