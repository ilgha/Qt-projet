#include "map.h"
#include "Plain.h"
Map::Map(){
    Plain plain = Plain();
}

Land Map::getTile(int x, int y){
    int type = map[x][y];
    if(type == 1){
        return plain;
    }else{
        return plain;
    }
}
