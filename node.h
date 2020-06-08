#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QPainter>

#include <algorithm>

class Node : public QGraphicsItem
{
private:
    bool is_start_node;
    bool is_end_node;
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
   bool is_path = false;
   void update_is_path() {
       is_path = true;
       update();
   }
   int get_x();
   int get_y();
   void add_neighbour(Node *neighbour);
   std::vector<Node*> get_neighbours_list();
   void mark_as_start(bool marked);
   void mark_as_end(bool marked);
   void restart();
   void set_local_goal(float value);
   float get_local_goal();
   bool get_is_visited();
   void set_global_goal(float value);
   float get_global_goal();
   void set_visited(bool value);

   bool get_is_obstacle() {
       return is_obstacle;
   }
   void set_parent(Node *value) {
       parent = value;
   }

   Node *get_parent(){return parent;}
   QRectF boundingRect() const override;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
protected:
   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // NODE_H
