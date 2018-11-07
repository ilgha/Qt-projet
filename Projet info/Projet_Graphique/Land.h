#ifndef LAND_H
#define LAND_H

#include <string>
class Land
{
    int def, f, b, tr, ti, a;

public:
    Land(int defence, int f, int b, int tr, int ti, int a);
    ~Land();

    int getMoved(std::string mt) const ;
    int getDef()const ;
};

#endif // LAND_H
