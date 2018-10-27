#ifndef LAND_H
#define LAND_H

#include <string>
class Land
{
    int x, y, def, f, b, tr, ti, a;

public:
    Land(int posX, int posY, int defence, int f, int b, int tr, int ti, int a);
    ~Land();

    int getMoved(std::string mt) const ;
    int getX() const ;
    int getY() const ;
    int getDef()const ;
};

#endif // LAND_H
