#include "game.h"
#include <iostream>

Game::Game(Player* player1, Player* player2){
    this->player1 = player1;
    this->player2 = player2;
    active = player1;
    army.reserve(10);
    army.push_back(Infantery(0,3,10,1,player2));
    buildings.reserve(20);
    buildings.push_back(Factory(0, 3));

    int t[12][18] = {{1,1,1,1,1,1,1,1,44,1,44,1,1,1,1,1,34,3},
                     {1,1,15,15,15,15,15,15,15,47,1,43,1,1,1,1,1,34},
                     {1,1,1,1,34,35,34,1,34,1,43,1,1,1,1,1,34,1},
                     {35,1,1,2,1,1,1,3,1,43,1,1,3,34,1,35,1,2},
                     {34,1,1,34,2,1,3,1,1,3,1,1,1,1,3,1,1,1},
                     {1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1},
                     {28,35,1,1,1,1,1,1,1,3,2,1,3,1,1,34,1,34},
                     {28,28,27,28,28,28,28,3,28,3,3,3,1,1,1,1,1,1},
                     {1,1,1,1,1,35,28,28,28,28,3,3,1,1,34,1,35,1},
                     {1,1,1,1,1,34,1,26,1,1,2,1,34,1,34,1,1,1},
                     {1,1,1,1,1,1,1,34,28,28,1,1,1,1,34,1,3,1},
                     {1,1,1,1,1,1,34,28,28,3,3,1,3,34,1,3,34,3}};

}

int Game::endTurn() {
    if(&active == &player1){
        active = player2;
    }else{
        active = player1;
    }
    for(unsigned int i = 0; i< army.size(); i++){
        army[i].newTurn();
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


std::vector<Unit> Game::getArmy(){
    return army;
}

Building* Game::check(Unit* unit){
    for(unsigned int i = 0; i < buildings.size(); i++){
        if(unit->getX() == buildings[i].getX() && unit->getY() == buildings[i].getY()){
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
