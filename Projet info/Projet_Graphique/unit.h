#ifndef PROJECT_UNIT_H
#define PROJECT_UNIT_H

#include <string>
#include "Player.h"
using std::string;

class Unit{
    int x;
    int y;
    int health;
    int healthMax;
    int mp;
    int mpMax;
    string mt;
    int cost;
    Player* team;

public:
    Unit(int posX, int posY, int health, int healthMax, int mp, int mpMax, string mt, int cost, Player* team);
    ~Unit();

    int getX() const ;
    int getY() const;
    int getHealth() const;
    int getMP() const;
    string getMT() const;
    int getCost() const;
    Player* getTeam() const;
    void setX(int x);
    void setY(int y);
    //int damage(unit1, unit2);
};

#endif //PROJECT_UNIT_H
