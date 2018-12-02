#ifndef CITY_H
#define CITY_H

<<<<<<< HEAD
#include "player.h"
=======
#include "Player.h"
>>>>>>> a63fa1c108ea2ba9eef292c30b27be93b6ff5965
#include "building.h"

class City : public Building{
    int income = 1000;
//    Player team = NULL;
public:
    City(int x, int y);
    int switchTeam(Player* team);
};

#endif // CITY_H
