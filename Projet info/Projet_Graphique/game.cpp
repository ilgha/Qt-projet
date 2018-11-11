#include "game.h"
#include <iostream>
#include <cmath>

Player *Game::getPlayer2() const
{
    return player2;
}

void Game::setPlayer2(Player *value)
{
    player2 = value;
}

Player *Game::getPlayer1() const
{
    return player1;
}

void Game::setPlayer1(Player *value)
{
    player1 = value;
}

Game::Game(Player* player1, Player* player2){
    this->player1 = player1;
    this->player2 = player2;
    buildings.reserve(20);
    army.reserve(20);
    map = Map();
    for(int i = 0; i<12; i++){
        for(int j = 0; j<18; j++){
            if(map.getValue(i, j) == 35){
                buildings.push_back(Factory(j, i));
            }
        }
    }


    active = player1;


}

int Game::endTurn() {
    erase();
    if(active == player1){
        active = player2;
    }else{
        active = player1;
    }
    for(unsigned int i = 0; i< army.size(); i++){
        army[i]->newTurn();
    }
    army.push_back(new Infantery(5,5,10,1,active));
    army.push_back(new AntiAir(6,5,10,1,active));
    army.push_back(new BCopter(7,5,10,1,active));
    army.push_back(new Bomber(8,5,10,1,active));
    army.push_back(new Fighter(9,5,10,1,active));
    army.push_back(new MdTank(10,5,10,1,active));
    army.push_back(new Mech(5,6,10,1,active));
    army.push_back(new MegaTank(7,5,10,1,active));
    army.push_back(new NeoTank(8,5,10,1,active));
    army.push_back(new Recon(2,9,10,1,active));

    active->addMoney(active->getIncome());
    if(active->getMoney() == 0){
        endGame();
    }
    return 0;
}

void Game::recruit(Building* building, string buy){
    if(buy == "AntiAir" && building->getTeam()->getMoney()>8000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-8000);
        army.push_back(recruited);
    }else if(buy == "BCopter" && building->getTeam()->getMoney()>9000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-9000);
        army.push_back(recruited);
    }else if(buy == "Bomber" && building->getTeam()->getMoney()>22000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-22000);
        army.push_back(recruited);
    }else if(buy == "Fighter" && building->getTeam()->getMoney()>20000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-20000);
        army.push_back(recruited);
    }else if(buy == "infantery" && building->getTeam()->getMoney()>1000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-1000);
        army.push_back(recruited);
    }else if(buy == "MdTank" && building->getTeam()->getMoney()>16000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-16000);
        army.push_back(recruited);
    }else if(buy == "Mech" && building->getTeam()->getMoney()>3000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-3000);
        army.push_back(recruited);
    }else if(buy == "MegaTank" && building->getTeam()->getMoney()>28000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-28000);
        army.push_back(recruited);
    }else if(buy == "NeoTank" && building->getTeam()->getMoney()>22000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-22000);
        army.push_back(recruited);
    }else if(buy == "Recon" && building->getTeam()->getMoney()>15000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-15000);
        army.push_back(recruited);
    }else if(buy == "Tank" && building->getTeam()->getMoney()>7000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 10, 1, building->getTeam());
        recruited->getTeam()->addMoney(-7000);
        army.push_back(recruited);
    }
}


std::vector<Unit*>* Game::getArmy(){
    return &army;
}

Building* Game::checkBuildings(Unit* unit){
    for(unsigned int i = 0; i < buildings.size(); i++){
        if(unit->getX() == buildings.at(i).getX() && unit->getY() == buildings.at(i).getY()){
            return &buildings[i];
        }
    }
    return nullptr;
}

Land* Game::checkLand(Unit* u){
    return nullptr;
}

bool Game::ennemyNear(Unit *unit)
{
    for(unsigned int i = 0; i < army.size(); i++){
        return (sqrt(pow(unit->getX() - army.at(i)->getX(), 2) + pow(unit->getY() - army.at(i)->getY(), 2) == 1) && army.at(i)->getTeam() != active);
    }
}

int Game::endGame(){
    return 0;
}

Player* Game::getActive() const{
    return active;
}

void Game::checkFusion(Unit* unit){
    for(unsigned int i = 0; i<army.size(); i++){
        if(army.at(i)->getX() == unit->getX() && army.at(i)->getY() == unit->getY() && army.at(i) != unit){
            setHealth(unit, army.at(i)->getHealth());
            army.at(i)->setDead(true);

        }
    }
}

void Game::erase(){
    for(unsigned int i = 0; i< army.size(); i++){
        if(army.at(i)->getDead()){
           army.erase(army.begin()+i);
        }
    }
}

void Game::setHealth(Unit* unit, int addedHealth){
    unit->setHealth(addedHealth);
    if(unit->getHealth()<=0){
        unit->setDead(true);
    }
}

Unit* Game::getActiveUnit() const{
    return activeUnit;
}

void Game::setActiveUnit(Unit* unit){
    activeUnit = unit;
}
<<<<<<< HEAD
Player *Game::getPlayer1() const
{
    return player1;
}

void Game::setPlayer1(Player *value)
{
    player1 = value;
}

void Game::attack(Unit* unitA,Unit* unitD, bool isCounter){
    int damage = unitD->getDamage(unitA,unitD);
    int health = unitD->getHealth();
    if (health - damage <=0){
        unitD->setHealth(0);
    }
    else if (bool isCounter = false) {
        unitD -> setHealth(health - damage);
        void attack(Unit* unitD, Unit* unitA,bool isCounter=true);
    }
    else{
        unitD->setHealth(health - damage);
    }
};
=======
>>>>>>> a63fa1c108ea2ba9eef292c30b27be93b6ff5965
