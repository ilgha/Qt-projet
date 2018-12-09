
#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Unit.h"
#include "infantery.h"
#include "AntiAir.h"
#include "BCopter.h"
#include "Bomber.h"
#include "Fighter.h"
#include "MdTank.h"
#include "Mech.h"
#include "MegaTank.h"
#include "NeoTank.h"
#include "Recon.h"
#include "Tank.h"
#include "Land.h"
#include "Plain.h"
#include "building.h"
#include "factory.h"
#include "Airport.h"
#include "city.h"
#include "map.h"
#include <vector>
class Game {
    Player* player1;
    Player* player2;
    Player* active;
    Map map;
    std::vector<Unit*> army;
    std::vector<Building> buildings;
    Unit* activeUnit = nullptr;
    int getDamage(Unit* unitA, Unit* unitD);
public:
    Game(Player* player1, Player* player2);
    int endTurn();
    bool recruit(Building* building, string buy);
    int endGame();
    std::vector<Unit*> *getArmy();
    Building* checkBuildings(unsigned int x, unsigned int y);
    Land* checkLand(Unit* units);
    bool ennemyNear(Unit* unit);
    Player* getActive() const;
    void setActive(Player* player);
    void checkFusion(Unit* unit);
    void erase();
    void setHealth(Unit* unit, int addedHealth);
    Unit* getActiveUnit() const;
    void setActiveUnit(Unit* unit);
    Player *getPlayer2() const;
    void setPlayer2(Player *value);
    Player *getPlayer1() const;
    void setPlayer1(Player *value);
    void attack (Unit* unitA, Unit* initD, bool isCounter);
    Map getMap() const;
    std::vector<Building> getBuildings() const;
};

#endif //GAME_H
