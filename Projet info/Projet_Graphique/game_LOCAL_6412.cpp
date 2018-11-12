#include "game.h"
#include <iostream>



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
    army.push_back(new Infantery(0,2,10,3,player1));



    army.push_back(new Infantery(4,2,10,3,player2));


    army.push_back(new Infantery(1,3,10,1,player2));
    army.push_back(new Infantery(1,4,10,1,player2));
    army.push_back(new Infantery(1,5,10,1,player2));
    army.push_back(new Infantery(2,6,10,1,player2));
    army.push_back(new Infantery(1,7,10,1,player2));
    army.push_back(new Infantery(1,8,10,1,player2));



    active = player1;
}

int Game::endTurn() {
    if(&active == &player1){
        active = player2;
    }else{
        active = player1;
    }
    for(unsigned int i = 0; i< army.size(); i++){
        army[i]->newTurn();
    }
    active->addMoney(active->getIncome());
    if(active->getMoney() == 0){
        endGame();
    }
    return 0;
}

void Game::recruit(Unit* unit, string buy){
    Unit recruited = Infantery(unit->getX(), unit->getY(), 10, 1, unit->getTeam());
    /* append all units here*/
    if(buy == "infantery" && unit->getTeam()->getMoney()>1000){
        recruited = Infantery(unit->getX(), unit->getY(), 10, 1, unit->getTeam());
        unit->getTeam()->addMoney(-1000);
    }else{
        recruited = Infantery(unit->getX(), unit->getY(), 10, 1, unit->getTeam());
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

Land Game::checkLand(Unit* unit){
    return map.getTile(unit->getX(), unit->getY());
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
            unit->setHealth(army.at(i)->getHealth());
            army.at(i)->setHealth(-1000);
        }
    }
}

void Game::erase(Unit* unit){
    Unit* save = unit;
    for(unsigned int i = 0; i< army.size(); i++){
        if(unit == army.at(i)){
           army.erase(army.begin()+i);
           save->setHealth(-10000);
        }
    }
}

Unit* Game::getActiveUnit() const{
    return activeUnit;
}

void Game::setActiveUnit(Unit* unit){
    activeUnit = unit;
}
Player *Game::getPlayer1() const
{
    return player1;
}

void Game::setPlayer1(Player *value)
{
    player1 = value;
}
