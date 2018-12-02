#ifndef UNIT_H
#define UNIT_H

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
    bool movable = false;
    string mt;
    Player* team;
    int ID;
    bool dead = false;



public:
    Unit(int posX, int posY, int health, int healthMax, int mp, int mpMax, string mt, Player* team, int ID);

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

    int getHealthMax() const;
    void setHealthMax(int value);
    void setDead(bool value);
    bool getDead() const;
    int getID() const;
    void setMp(int value);
};

#endif // UNIT_H

