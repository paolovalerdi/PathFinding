#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QGraphicsScene>
#include <QDebug>
#include "node.h"

class PathFinder
{
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
    void init_graph();
    void draw_graph();

    int get_node_index(int y, int x);

public:
    PathFinder(int map_size, int node_size, int node_padding);
    QGraphicsScene *get_scene();
};

#endif // PATHFINDER_H
