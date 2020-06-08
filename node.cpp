#include "node.h"
#include <QtDebug>

Node::Node()
{
    x = 0;
    x = 0;
    padding = 0;
    size = 0;
    is_obstacle = false;
    is_visited = false;
    is_start_node = false;
    is_end_node = false;
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
    is_start_node = false;
    is_end_node = false;
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

void Node::mark_as_start(bool marked)
{
    is_end_node = false;
    is_obstacle = false;
    is_visited = false;
    is_start_node = marked;
    update();
}

void Node::mark_as_end(bool marked)
{
    is_start_node = false;
    is_obstacle = false;
    is_visited = false;
    is_end_node = marked;
    update();
}

void Node::restart()
{
    global_goal = INFINITY;
    local_goal = INFINITY;
    set_visited(false);
    parent = nullptr;
}

void Node::set_local_goal(float value)
{
    local_goal = value;
}

float Node::get_local_goal()
{
    return local_goal;
}

bool Node::get_is_visited()
{
    return is_visited;
}

float Node::get_global_goal()
{
    return global_goal;
}


void Node::set_global_goal(float value)
{
    global_goal = value;
}

void Node::set_visited(bool value)
{
    is_visited = value;
    update();
}

QRectF Node::boundingRect() const
{
    return QRectF(x + padding, y + padding, size - 10, size - 10);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(is_obstacle)
    {
        painter->setPen(QPen(QColor(160, 161, 164)));
        painter->setBrush(QBrush(QColor(160, 161, 164)));
        painter->drawRect(boundingRect());
        return;
    }
    if(is_start_node)
    {

        painter->setPen(QPen(QColor(105, 240, 174)));
        painter->setBrush(QBrush(QColor(105, 240, 174)));
        painter->drawRect(boundingRect());
        return;
    }
    if (is_end_node)
    {
        painter->setPen(QPen(QColor(255, 82, 82)));
        painter->setBrush(QBrush(QColor(255, 82, 82)));
        painter->drawRect(boundingRect());
        return;
    }
    if(is_path)
    {
        painter->setPen(QPen(QColor(255, 196, 0)));
        painter->setBrush(QBrush(QColor(255, 196, 0)));
        painter->drawRect(boundingRect());
        return;
    }
    if (is_visited)
    {
        painter->setPen(QPen(QColor(90, 91, 104)));
        painter->setBrush(QBrush(QColor(90, 91, 104)));
        painter->drawRect(boundingRect());
        return;
    }
    painter->setPen(QPen(QColor(70, 71, 84)));
    painter->setBrush(QBrush(QColor(70, 71, 84)));
    painter->drawRect(boundingRect());
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    is_obstacle = !is_obstacle;
    update();
}
