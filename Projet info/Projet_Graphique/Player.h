#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H


class Player {
    int income, money, IA;
public:
    explicit Player(int IA, int money);
    ~Player();
    int getIncome()const ;
    void addIncome(int newIncome);
    void addMoney(int newMoney);
    int getMoney() const ;

};


#endif //PROJECT_PLAYER_H
