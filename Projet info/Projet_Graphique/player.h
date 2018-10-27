//
// Created by Pierre Vander Eyken on 20/10/2018.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H


class Player {
    int income, money, IA;
    bool isActive = false;
public:
    explicit Player(int IA, int money);
    ~Player();
    int getIncome()const ;
    void addIncome(int newIncome);
    void addMoney(int newMoney);
    int getMoney() const ;
    bool isItActive();

};


#endif //PROJECT_PLAYER_H
