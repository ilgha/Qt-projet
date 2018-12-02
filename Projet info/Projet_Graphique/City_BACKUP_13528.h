<<<<<<< Updated upstream
#ifndef CITY_H
#define CITY_H

#include "player.h"
#include "building.h"

class City : public Building{
    int income = 1000;
//    Player team = NULL;
public:
    City(int x, int y);
    int switchTeam(Player* team);
};

#endif // CITY_H
=======
#ifndef CITY_H
#define CITY_H

#include "player.h"
#include "building.h"

class City : public Building{
    int income = 1000;
//    Player team = NULL;
public:
    City(int x, int y);
    int switchTeam(Player* team);
};

#endif // CITY_H
>>>>>>> Stashed changes
