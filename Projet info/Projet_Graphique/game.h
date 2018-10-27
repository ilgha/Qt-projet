#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H
#include "Player.h"
#include "unit.h"
#include "infantery.h"
#include "Land.h"
#include "Plain.h"
#include <vector>
class Game {
    Player* player1;
    Player* active;
    std::vector<Unit> army;
    int terrain[12][18] = {{1,1,1,1,1,1,1,1,44,1,44,1,1,1,1,1,34,3},
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
    Plain plain = Plain(1,1);
public:
    Game(Player* player1);
    int endTurn();
    int endGame();
    std::vector<Unit> getArmy();
};

#endif //PROJECT_GAME_H
