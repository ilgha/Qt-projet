#include "node.h"

node::node(int x, int y, int cost, int heur)
{
    this->x=x;
    this->y=y;
    this->cost=cost;
    this->heur=heur;
    this->child=nullptr;
}

//bool node::operator== ( const node &nodeDroite ) const
//{ return x == nodeDroite.x && y == nodeDroite.y; }

bool node::operator== (const node &n) const
{
   if((x == n.getX()) && (y == n.getY()))
     return true;
   else
     return false;
}

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

node* node::getChild()
{
    return child;
}

void node::setParenting(node* child)
{
    this->child=child;
}




