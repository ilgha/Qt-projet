#ifndef UNIT_H
#define UNIT_H

#include <string>
#include "player.h"

using std::string;

class Unit{
    int x;
    int y;
    int health;
    int healthMax;
    int mp;
    int mpMax;
    bool movable = false;
    string mt;
    int cost;
    Player* team;
    int ID;

public:
    Unit(int posX, int posY, int health, int healthMax, int mp, int mpMax, string mt,int cost, Player* team, int ID);
    ~Unit();

    int getX() const ;
    int getY() const;
    int getHealth() const;
    int setHealth(int newHp);
    int getMP() const;
    string getMT() const;
    Player* getTeam() const;
    void setX(int x);
    void setY(int y);
    void newTurn();
    void setMovable(bool b);
    bool isMovable();
    void fusion(Unit* unit);
    int getDamage(Unit * unitA, Unit * unitD);
    int attack (Unit * unitA, Unit * unitD);

};

#endif //UNIT_H
