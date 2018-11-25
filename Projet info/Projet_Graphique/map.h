#ifndef MAP_H
#define MAP_H
#include "Plain.h"
#include "mountain.h"
#include "woods.h"
#include "road.h"
#include "bridge.h"
#include "river.h"
#include "factory.h"

class Map
{
    int map[12][18] = {{1,1,1,1,1,1,1,1,44,1,44,1,1,1,1,1,34,3},
                       {1,1,15,15,15,15,15,15,15,47,1,43,1,1,1,1,1,34},
                       {1,1,1,1,34,35,34,1,34,1,43,1,1,1,1,1,34,1},
                       {35,1,1,2,1,1,1,3,1,43,1,1,3,34,1,35,1,2},
                       {34,1,1,34,2,1,3,1,1,3,1,1,1,1,3,1,1,1},
                       {1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1},
                       {28,35,1,1,1,1,1,1,1,3,2,1,3,1,1,34,1,34},
                       {28,28,27,28,28,28,28,3,28,3,3,3,1,1,1,1,1,1},
                       {1,1,1,1,1,35,28,28,28,28,3,3,1,1,34,1,35,1},
                       {1,1,1,1,1,34,1,26,1,1,2,1,34,1,34,1,1,1},
                       {1,1,1,1,1,1,1,34,28,28,1,1,1,1,34,1,3,1},
                       {1,1,1,1,1,1,34,28,28,3,3,1,3,34,1,3,34,3}};
    Plain plain;
    Mountain mountain;
    Woods woods;
    Road road;
    Bridge bridge;
    River river;
public :
    Map();
    Land getTile(int x, int y);
    int getValue(int x, int y);
};


#endif // MAP_H
