<<<<<<< HEAD
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
=======
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
    int getDamage(Unit * unitA, Unit * unitD);

    //int damage(unit1, unit2);
    int getHealthMax() const;
    void setHealthMax(int value);
    void setDead(bool value);
    bool getDead() const;
};

#endif //PROJECT_UNIT_H
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
