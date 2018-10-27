#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H
#include "Player.h"
#include "unit.h"
#include "infantery.h"
#include <vector>
class Game {
    Player* player1;
    Player* active;
    std::vector<Unit> army;
public:
    Game(Player* player1);
    int endTurn();
    int endGame();
    std::vector<Unit> getArmy();
};


#endif //PROJECT_GAME_H
