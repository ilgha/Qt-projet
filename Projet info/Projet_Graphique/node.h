#ifndef NODE_H
#define NODE_H


class node
{
public:
    node(int x, int y, int cost, int heur);
    bool operator== ( const node & nodeDroite ) const;
    int getCost();
    int getHeuristic();
    int getF();
    int getX();
    int getY();
    node* getChild();
    void setParenting(node* child);

private:
    int x;
    int y;
    int cost;
    int heur;
    node* child;
};

#endif // NODE_H
