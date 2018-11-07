
#include "BCopter.h"
#include <string>
using std::string;

BCopter::BCopter(int x,int y, int health,int mp,Player* team ):
    Unit(x,y,health,10, mp, 6, "a", team, 1){
}
