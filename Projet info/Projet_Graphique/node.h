#ifndef NODE_H
#define NODE_H


class node
{
public:
    node(int x, int y, int cost, int heur);
    bool operator== ( const node & nodeDroite ) const;
    int getCost();
    int getHeuristic();
    unsigned int getF();
    int getX() const;
    int getY() const;

private:
    int x;
    int y;
    int cost;
    int heur;
};

#endif // NODE_H
