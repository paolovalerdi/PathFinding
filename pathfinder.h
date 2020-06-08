#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QGraphicsScene>
#include <QDebug>
#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include "node.h"

class PathFinder : public QObject
{
    Q_OBJECT
private:
    // Dimensions in px related to drawing.
    int map_size; // The actual window size (currently only squared windows are supported).
    int node_size; // The size a node will be drawn.
    int node_padding; // Amount of pixel not to draw around our node.
    int map_slots; // The amount of nodes that can fit in a row/colums;
    int graph_size; // The actual graph amount of nodes.

    // Graphics related stuff;
    QGraphicsScene *scene;

    // Graph related stuff;
    Node **graph; // An array of pointers to node objects.
    Node *startNode;
    Node *endNode;
    void init_graph();
    void draw_graph();

    // Key pressed related stuff
    bool was_E_pressed;
    bool was_S_pressed;

    int get_node_index(int y, int x);
    float distance(Node *a, Node *b);

public:
    PathFinder(QObject *parent, int map_size, int node_size, int node_padding);
    ~PathFinder();
    QGraphicsScene *get_scene();
    void solve();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // PATHFINDER_H
