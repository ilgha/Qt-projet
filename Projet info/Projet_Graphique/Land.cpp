#include "Land.h"

#include <iostream>


Land::Land(int posX, int posY, int defence, int f, int b, int tr, int ti, int a){
    x = posX;
    y = posY;
    def = defence;
    this->f = f;
    this->b = b;
    this->tr = tr;
    this->ti = ti;
    this->a = a;
}

Land::~Land(){
}

int Land::getMoved(std::string mt) const {
if (mt == "f") {
return f;
}
else if (mt == "b") {
return b;
}
else if (mt == "tr") {
return tr;
}
else if (mt == "ti") {
return ti;
}
else if (mt == "a") {
return a;
}
else {
std::cout << "error not a valid mt" << std::endl;
return NULL;
}
}

int Land::getX() const {
    return x;
}

int Land::getY() const {
    return y;
}