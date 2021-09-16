#include "node.h"

#define ABS(a)      (((a) > 0) ? (a) : (-1) * (a))

Node::Node(Coord pos, int g, Node* prev_node) : pos(pos), g(g), prev_node(prev_node)
{
    this->calc_f();
}

void Node::calc_f(void)
{
    this->calc_h();
    this->f = this->g + this->h;
}

void Node::calc_h(void)
{
    this->h = ABS(Node::end.row - this->pos.row) + ABS(Node::end.col - this->pos.col);
}
