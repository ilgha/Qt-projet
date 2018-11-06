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

    army.push_back(new Infantery(1,4,10,2,player1));
    army.push_back(new Infantery(1,5,10,2,player1));



    active = player1;
}

int Game::endTurn() {
    erase();
    if(&active == &player1){
        active = player2;
    }else{
        active = player1;
    }
    for(unsigned int i = 0; i< army.size(); i++){
        army[i]->newTurn();
    }
    army.push_back(new Infantery(5,5,10,1,active));
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

Building* Game::check(Unit* unit){
    for(unsigned int i = 0; i < buildings.size(); i++){
        if(unit->getX() == buildings.at(i).getX() && unit->getY() == buildings.at(i).getY()){
            return &buildings[i];
        }
    }
    return nullptr;
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
            unit->setDead(true);
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
