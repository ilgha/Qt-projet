#include "game.h"
#include <iostream>
Game::Game(Player* player1){
    this->player1 = player1;
    //this->player2 = player2;
    active = player1;
    army.push_back((Unit)Infantery(1,1,1,1,1,player1));
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
    }
    return 0;*/
}

std::vector<Unit> Game::getArmy(){
    std::cout<<"done"<<std::endl;
    return army;
}
