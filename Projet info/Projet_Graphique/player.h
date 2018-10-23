#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player();
    Player(int x, int y);

    int getPosX();
    int getPosY();
    void setPosX(int x);
    void setPosY(int y);
    void isMovable();
    void notMovable();

private:
    int posX;
    int posY;
    bool movable;

};

#endif // PLAYER_H
