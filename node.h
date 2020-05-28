#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>

#include <algorithm>

class Node : public QGraphicsItem
{
private:
    bool is_obstacle;
    bool is_visited;
    float global_goal;
    float local_goal;

    int x;
    int y;
    int padding;
    int size;
    QRectF rect;

    std::vector<Node*> neighbours;
    Node *parent;
public:

   Node();
   Node(int x, int y, int padding, int size);
   ~Node();

   QRectF boundingRect() const override;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
};

#endif // NODE_H
