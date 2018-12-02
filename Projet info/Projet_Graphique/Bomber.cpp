

#include "Bomber.h"
#include <string>
using std::string;

Bomber::Bomber(int x,int y, int health,Player* team ):
    Unit( x,  y, health, 10, 7, "a",team, 2){
}
