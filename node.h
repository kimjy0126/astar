#ifndef __NODE_H
#define __NODE_H

#include "coord.h"

class Node {
private:
    void calc_h();

public:
    static Coord start;
    static Coord end;

    Node(Coord pos = Coord(), int g = -1, Node* prev_node = 0);

    Coord pos;
    Node* prev_node;
    int f, g, h;

    void calc_f();
};

struct compare_node {
    bool operator()(Node*& node1, Node*& node2)
    {
        return (node1->f) > (node2->f);
    }
};

#endif
