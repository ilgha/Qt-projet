#include "map.h"


Map::Map(){
    Plain plain = Plain();
    Mountain mountain = Mountain();
    Woods woods = Woods();
    Road road = Road();
    Bridge bridge = Bridge();
    River river = River();
}

Land Map::getTile(int x, int y){
    int type = map[x][y];
    switch(type){
        case 1 :
            return plain;
        case 2 :
            return mountain;
        case 3 :
            return woods;
        case 15 :
            return road;
        case 27 :
            return bridge;
        case 28 :
            return river;
    }
    return plain;
}
