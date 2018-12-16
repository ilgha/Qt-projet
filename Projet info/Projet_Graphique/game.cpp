#include "game.h"
#include <iostream>
#include <cmath>
#include <algorithm>


typedef std::pair <int, int> IntPair;



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


    army.push_back(new Infantry(7,7,10,player1));
    army.push_back(new Mech(7,8,10,player1));
    army.push_back(new BCopter(7,9,10,player1));

    //army.push_back(new Fighter(13,7,10,player2));
    army.push_back(new Bomber(14,7,10,player2));


    for(int i = 0; i< buildings.size(); i++){
        if(buildings.at(i).getX() == 14 && buildings.at(i).getY() == 4){
            buildings.at(i).setHp(army.at(0));
            buildings.at(i).setHp(army.at(0));
        }
    }

    for(int i = 0; i< buildings.size(); i++){
        if(buildings.at(i).getX() == 4 && buildings.at(i).getY() == 14){
            buildings.at(i).setHp(army.at(4));
            buildings.at(i).setHp(army.at(4));
        }
    }



    active = player2;
    for (unsigned int k=1; k<army.size();k++){
        if (army.at(k)->getTeam()==active){
            army.at(k)->setMovable(true);
        }
    }
}

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

    return 0;
}

bool Game::recruit(Building* building, string buy){
    if(buy == "AntiAir" && building->getTeam()->getMoney()>8000){
        Unit* recruited = new AntiAir(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-8000);
        army.push_back(recruited);
    }else if(buy == "BCopter" && building->getTeam()->getMoney()>9000){
        Unit* recruited = new BCopter(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-9000);
        army.push_back(recruited);
    }else if(buy == "Bomber" && building->getTeam()->getMoney()>22000){
        Unit* recruited = new Bomber(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-22000);
        army.push_back(recruited);
    }else if(buy == "Fighter" && building->getTeam()->getMoney()>20000){
        Unit* recruited = new Fighter(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-20000);
        army.push_back(recruited);
    }else if(buy == "Infantry" && building->getTeam()->getMoney()>1000){
        Unit* recruited = new Infantry(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-1000);
        army.push_back(recruited);
    }else if(buy == "MdTank" && building->getTeam()->getMoney()>16000){
        Unit* recruited = new MdTank(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-16000);
        army.push_back(recruited);
    }else if(buy == "Mech" && building->getTeam()->getMoney()>3000){
        Unit* recruited = new Mech(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-3000);
        army.push_back(recruited);
    }else if(buy == "MegaTank" && building->getTeam()->getMoney()>28000){
        Unit* recruited = new MegaTank(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-28000);
        army.push_back(recruited);
    }else if(buy == "NeoTank" && building->getTeam()->getMoney()>22000){
        Unit* recruited = new NeoTank(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-22000);
        army.push_back(recruited);
    }else if(buy == "Recon" && building->getTeam()->getMoney()>15000){
        Unit* recruited = new Recon(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-15000);
        army.push_back(recruited);
    }else if(buy == "Tank" && building->getTeam()->getMoney()>7000){
        Unit* recruited = new Tank(building->getX(), building->getY(), 10, building->getTeam());
        recruited->getTeam()->addMoney(-7000);
        army.push_back(recruited);
    }else{
        return false;
    }
    return true;
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

void Game::endGame(){

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

void Game::resetActiveUnit(){
    activeUnit = nullptr;
}

Map Game::getMap() const
{
    return map;
}

std::vector<Building> Game::getBuildings() const
{
    return buildings;
}



std::vector<IntPair> Game::getCases() const
{
    return cases;
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
        unitD->setHealth(health - damage);
        attack(unitD, unitA, true);
    }
    else{
        unitD->setHealth(health - damage);
    }
};

void Game::moveUnit(Unit* unit, int x, int y, int MP)
{

    int i = 0;
    int j = 1;
    IntPair pos = std::make_pair(x+i,y+j);
    MP -= getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    bool present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }

    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }

    MP += getMap().getTile(x+i, y+j).getMoved(unit->getMT());;
    i = 0;
    j = -1;

    pos = std::make_pair(x+i,y+j);
    MP -= getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }
    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }

    MP += getMap().getTile(x+i, y+j).getMoved(unit->getMT());;
    i = 1;
    j = 0;
    pos = std::make_pair(x+i,y+j);
    MP -= getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }
    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }

    MP += getMap().getTile(x+i, y+j).getMoved(unit->getMT());;
    i = -1;
    j = 0;

    pos = std::make_pair(x+i,y+j);
    MP -= getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }
    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }
}

void Game::checkBlocked(){
    for(unsigned int u = 0; u<cases.size(); u++){
        for(unsigned int i = 0; i<army.size(); i++){
            if(cases.at(u).first == army.at(i)->getX() && cases.at(u).second == army.at(i)->getY()){
                cases.erase(cases.begin()+u);
            }
        }
    }
    for(unsigned int u = 0; u<cases.size(); u++){
        if(cases.at(u).first < 0 || cases.at(u).second < 0){
            cases.erase(cases.begin()+u);
        }
    }
}

void Game::clearCases(){
    cases.clear();
}
