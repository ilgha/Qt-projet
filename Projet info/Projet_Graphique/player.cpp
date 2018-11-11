#include "player.h"

Player::Player(int IA, int money) {
    this->IA = IA;
    this->money = money;
}

Player::~Player() {

}

int Player::getIncome() const {
    return income;
}

void Player::addIncome(int newIncome) {
    income = income+newIncome;
    if(income < 0){
        income = 0;
    }
}

int Player::getMoney() const {
    return money;
}

void Player::addMoney(int newMoney){
    money = money+newMoney;
    if(money<0){
        money = 0;
    }
}
