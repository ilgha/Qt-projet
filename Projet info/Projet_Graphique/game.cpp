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
    for(int i = 0; i<17; i++){
        for(int j = 0; j<21; j++){
            if(map.getValue(i, j) == 35){
                buildings.push_back(Factory(j, i));
            }else if(map.getValue(i, j) == 34){
                buildings.push_back(City(j,i));
            }else if(map.getValue(i, j) == 36){
                buildings.push_back(Airport(j,i));
            }
        }
    }

    army.push_back(new MdTank(7,7,20,player1));
    army.push_back(new MdTank(13,7,20,player2));

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
    active->addMoney(active->getIncome());
    if(active->getMoney() == 0){
        endGame();
    }
    return 0;
}

void Game::recruit(Building* building, string buy){
    if(buy == "AntiAir" && building->getTeam()->getMoney()>8000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 1, building->getTeam());
        recruited->getTeam()->addMoney(-8000);
        army.push_back(recruited);
    }else if(buy == "BCopter" && building->getTeam()->getMoney()>9000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 1, building->getTeam());
        recruited->getTeam()->addMoney(-9000);
        army.push_back(recruited);
    }else if(buy == "Bomber" && building->getTeam()->getMoney()>22000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 1, building->getTeam());
        recruited->getTeam()->addMoney(-22000);
        army.push_back(recruited);
    }else if(buy == "Fighter" && building->getTeam()->getMoney()>20000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 1, building->getTeam());
        recruited->getTeam()->addMoney(-20000);
        army.push_back(recruited);
    }else if(buy == "infantery" && building->getTeam()->getMoney()>1000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 1, building->getTeam());
        recruited->getTeam()->addMoney(-1000);
        army.push_back(recruited);
    }else if(buy == "MdTank" && building->getTeam()->getMoney()>16000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 20, building->getTeam());
        recruited->getTeam()->addMoney(-16000);
        army.push_back(recruited);
    }else if(buy == "Mech" && building->getTeam()->getMoney()>3000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 20, building->getTeam());
        recruited->getTeam()->addMoney(-3000);
        army.push_back(recruited);
    }else if(buy == "MegaTank" && building->getTeam()->getMoney()>28000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 20, building->getTeam());
        recruited->getTeam()->addMoney(-28000);
        army.push_back(recruited);
    }else if(buy == "NeoTank" && building->getTeam()->getMoney()>22000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 20, building->getTeam());
        recruited->getTeam()->addMoney(-22000);
        army.push_back(recruited);
    }else if(buy == "Recon" && building->getTeam()->getMoney()>15000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 20, building->getTeam());
        recruited->getTeam()->addMoney(-15000);
        army.push_back(recruited);
    }else if(buy == "Tank" && building->getTeam()->getMoney()>7000){
        Unit* recruited = new Infantery(building->getX(), building->getY(), 20, building->getTeam());
        recruited->getTeam()->addMoney(-7000);
        army.push_back(recruited);
    }

}


std::vector<Unit*>* Game::getArmy(){
    return &army;
}

Building* Game::checkBuildings(unsigned int x, unsigned int y){
    for(unsigned int i = 0; i < buildings.size(); i++){
        if(x == buildings.at(i).getX() && y == buildings.at(i).getY()){
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
        if(sqrt(pow(unit->getX() - army[i]->getX(), 2) + pow(unit->getY() - army[i]->getY(), 2) == 1) && army[i]->getTeam() != unit->getTeam()){
            return true;
        }
    }
}

int Game::endGame(){
    return 0;
}

Player* Game::getActive() const{
    return active;
}

void Game::setActive(Player* player){
    this->active = player;
}


void Game::checkFusion(Unit* unit){
    for(unsigned int i = 0; i<army.size(); i++){
        if(army[i]->getX() == unit->getX() && army[i]->getY() == unit->getY() && army[i] != unit && army.at(i)->getTeam() == unit->getTeam()){
            setHealth(unit, army[i]->getHealth());
            army[i]->setDead(true);

        }
    }
}

void Game::erase(){
    for(unsigned int i = 0; i< army.size(); i++){
        if(army[i]->getDead()){
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

Map Game::getMap() const
{
    return map;
}

std::vector<Building> Game::getBuildings() const
{
    return buildings;
}

int Game::getDamage(Unit * unitA, Unit * unitD) {

    int damageChart[11][11] = {{45,120,75,65,105,10,105,1,5,60,25},
                               {25,65,0,0,75,25,75,10,20,55,55},
                               {95,0,0,0,110,95,110,35,90,105,105},
                               {0,100,100,55,0,0,0,0,0,0,0},
                               {5,7,0,0,55,1,45,1,1,12,5},
                               {105,12,0,0,105,55,95,25,45,105,85},
                               {65,9,0,0,65,15,55,5,15,85,55},
                               {195,22,0,0,135,125,125,65,115,195,180},
                               {115,22,0,0,125,75,115,35,55,125,105},
                               {4,12,0,0,70,1,65,1,1,35,6},
                               {65,10,0,0,75,15,70,10,15,85,55}};

    int IDA = unitA->getID();
    int IDD = unitD->getID();
    int B = damageChart[IDA][IDD];
    if (B >0 ){
        int A_HP = unitA->getHealth();
        int D_HP = unitD->getHealth();
        string typeD = unitD->getMT();
        if (typeD == "a"){
            int damage =  B * A_HP / 10 ;
            return damage;
        }
        else{
            int PosXD = unitD->getX();
            int PosYD = unitD->getY();
            int D_TR = map.getTile(PosXD, PosYD).getDef();
            int damage =  B * A_HP / 10 * (100 - D_TR * D_HP) / 100;
            return damage;
        }
    }
    else{
       std::cout << "Attaque impossible entre ces unités" << std::endl;
        return 0;
    }
}

void Game::attack(Unit* unitA,Unit* unitD, bool isCounter){
    int damage = getDamage(unitA,unitD);
    int health = unitD->getHealth();
    if (health - damage <=0){
        unitD->setHealth(0);
    }
    else if (isCounter == false) {
        unitD -> setHealth(health - damage);
        void attack(Unit* unitD, Unit* unitA,bool isCounter=true);
    }
    else{
        unitD->setHealth(health - damage);
    }
};

