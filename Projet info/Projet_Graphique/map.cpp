#include "map.h"
#include "Plain.h"
Map::Map(){
    Plain plain = Plain();
}

int Map::getTile(int x, int y){
    return map[x][y];
}
