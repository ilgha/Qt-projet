#ifndef PLAYER_H
#define PLAYER_H


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


#endif //PLAYER_H
