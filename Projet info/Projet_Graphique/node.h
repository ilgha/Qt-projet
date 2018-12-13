#ifndef NODE_H
#define NODE_H


class node
{
public:
    node(int x, int y, int cost, int heur);

private:
    int x;
    int y;
    int cost;
    int heur;
};

#endif // NODE_H
