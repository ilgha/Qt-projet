#include "node.h"

node::node(int x, int y, int cost, int heur)
{
    this->x=x;
    this->y=y;
    this->cost=cost;
    this->heur=heur;
}

bool node::operator== ( const node &nodeDroite ) const
{ return x == nodeDroite.x && y == nodeDroite.y; }



int node::getCost()
{
    return cost;
}

int node::getHeuristic()
{
    return heur;
}

unsigned int node::getF()
{
    return (cost+heur);
}

int node::getX() const
{
    return x;
}

int node::getY() const
{
    return y;
}






