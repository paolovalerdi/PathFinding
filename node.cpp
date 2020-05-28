#include "node.h"

Node::Node()
{
    x = 0;
    x = 0;
    padding = 0;
    size = 0;
    is_obstacle = false;
    is_visited = false;
    parent = nullptr;
}

Node::Node(int x, int y, int padding, int size)
{
    this->x = x;
    this->y = y;
    this->padding = padding;
    this->size = size;
    is_obstacle = false;
    is_visited = false;
    parent = nullptr;
}

Node::~Node()
{
}

int Node::get_x()
{
    return x;
}

int Node::get_y()
{
    return y;
}

void Node::add_neighbour(Node *neighbour)
{
    neighbours.push_back(neighbour);
}

std::vector<Node *> Node::get_neighbours_list()
{
    return neighbours;
}

QRectF Node::boundingRect() const
{
    return QRectF(x + padding, y + padding, size - 10, size - 10);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QColor(70, 71, 84)));
    painter->setBrush(QBrush(QColor(70, 71, 84)));
    painter->drawRect(boundingRect());
}
