#include "game.h"
#include <iostream>

Game::Game(Player* player1){
    this->player1 = player1;
    //this->player2 = player2;
    active = player1;
    army.reserve(10);
    army.push_back(Infantery(0,3,1,1,1,player1));
}

int Game::endTurn() {
    /*if(&active == &player1){
        active = player2;
    }else{
        active = player1;
    }

    active->addMoney(active->getIncome());
    if(active->getMoney() == 0){
        endGame();
    }*/
    return 0;
}

void Game::recruit(Unit* unit, string buy){
    Unit recruited = Infantery(unit->getX(), unit->getY(), 10, 1, 1000, unit->getTeam());
    /* append all units here*/
    if(buy == "infantery"){
        recruited = Infantery(unit->getX(), unit->getY(), 10, 1, 1000, unit->getTeam());
    }else{
        recruited = Infantery(unit->getX(), unit->getY(), 10, 1, 1000, unit->getTeam());
    }

    if(unit->getTeam() == active && recruited.getCost() < active->getMoney()){
        army.push_back(recruited);
        std::cout<< "Unit recruited" << std::endl;
    }else{
        std::cout<< "Not enough money to do that!" << std::endl;
    }
}


std::vector<Unit> Game::getArmy(){
    return army;
}

int Game::endGame(){
    return 0;
}
