#include "pathfinder.h"
#include <algorithm>

PathFinder::PathFinder(
        QObject *parent,
        int map_size,
        int node_size,
        int node_padding
        ) : QObject(parent)
{
    this->map_size = map_size;
    this->node_size = node_size;
    this->node_padding = node_padding;
    this->map_slots = map_size / node_size;
    this->graph_size = map_slots * map_slots;

    was_E_pressed = false;
    was_S_pressed = false;

    scene = new QGraphicsScene();

    startNode = nullptr;
    endNode = nullptr;
    init_graph();
}

PathFinder::~PathFinder()
{

}

void PathFinder::init_graph()
{
    /*
    * Creaes an array of (map_slots^2) pointers
    * in order to store all the nodes
    * that can fit in the window.
    */
    graph = new Node*[graph_size];

    /*
     * Stores the current node in the graph the following way.
     * (This loop travels slots "like colums")
     *
     * x = map_size - node_size
     * y = map_size - node_size
     * n = (map_slots)^2
     *
     *
     * [ 0 ][ 1 ]...[ map_slots - 1]
     * .............................
     * ....................[ n - 1 ]
     *
     * Where each node's coordinate starts at the top left corner
     * so the very first node coordinates will be (0,0) at slot 0
     * and node coordinates at slot n - 1 will be (x, y).
     */
    for (int x = 0; x < map_size; x += node_size)
    {
        for (int y = 0; y < map_size; y += node_size)
        {
            graph[get_node_index(y,x)] = new Node(x, y, node_padding, node_size);
            //qDebug() << "Node: (" << x << "," << y << ")->[" << get_node_index(y,x) << "]";
        }
    }

    /*
    * Once the nodes are stored in the graph find each node neigbours.
    * A neigbour is any of the left, top, right, bottom nodes.
    *                  N = node
    *                  n = neigbour
    *
    *                    [][x][]
    *                   [x][N][x]
    *                    [][x][]
    *
    * There's four exceptions
    *     [N][x][]        [x][N][x]    [][x][N]      [][][x]
    *     [x][][]          [][x][]      [][][x]     [][x][N]
    *      No left          No top      No right     No bottom.
    */
    for (int x = 0; x < map_size; x += node_size)
    {
        for (int y = 0; y < map_size; y += node_size)
        {
            //qDebug() << "Current node: (" << x << "," << y << ")->[" << get_node_index(y, x) << "]";
            if (x > 0)
            {
                graph[get_node_index(y, x)]->add_neighbour(graph[get_node_index(y, x - node_size)]);
                //qDebug() << "Left neigbourh: (" << x - node_size << "," << y << ")->[" << get_node_index(y,x - node_size) << "]";
            }
            if (y > 0)
            {
                graph[get_node_index(y, x)]->add_neighbour(graph[get_node_index(y - node_size, x)]);
                //qDebug() << "Top neigbourh: (" << x << "," << y - node_size << ")->[" << get_node_index(y - node_size ,x) << "]";
            }
            if (x < map_size - node_size)
            {
                graph[get_node_index(y, x)]->add_neighbour(graph[get_node_index(y, x + node_size)]);
                // qDebug() << "Right neigbourh: (" << x + node_size << "," << y << ")->[" << get_node_index(y, x + node_size) << "]";
            }
            if (y < map_size - node_size)
            {
                graph[get_node_index(y, x)]->add_neighbour(graph[get_node_index(y + node_size, x)]);
                //qDebug() << "Bottom neigbourh: (" << x << "," << y + node_size << ")->[" << get_node_index(y + node_size ,x) << "]";
            }
            //qDebug() << "############################";
        }
    }
    draw_graph();
}

void PathFinder::draw_graph()
{
    // First draw connections.
    for (int x = 0; x < map_size; x += node_size)
    {
        for (int y = 0; y < map_size; y += node_size)
        {
            for (auto n : graph[get_node_index(y, x)]->get_neighbours_list())
            {
                QPen pen = QPen(QColor(70, 71, 84));
                pen.setWidthF(2);
                QLineF line = QLineF(x + node_size / 2, y + node_size / 2, n->get_x() + node_size / 2, n->get_y() + node_size / 2);
                scene->addLine(line, pen);
            }
        }
    }

    //Then draw the nodes.
    for (int i = 0; i < graph_size; i++)
    {
        scene->addItem(graph[i]);
    }
}

int PathFinder::get_node_index(int y, int x)
{
    return (y * map_slots + x) / node_size;
}

float PathFinder::distance(Node *a, Node *b)
{
    return sqrtf((a->get_x() - b->get_x()) * (a->get_x() - b->get_x()) + (a->get_y() - b->get_y()) * (a->get_y() - b->get_y()));
}

QGraphicsScene *PathFinder::get_scene()
{
    return scene;
}

void PathFinder::solve()
{
    for (int x = 0; x < map_size; x += node_size)
    {
        for (int y = 0; y < map_size; y += node_size)
        {
            graph[get_node_index(y,x)]->restart();
        }
    }

    Node *current = startNode;
    startNode->set_local_goal(0.0f);
    startNode->set_global_goal(distance(startNode, endNode));
    std::list<Node*> not_visited_node;
    not_visited_node.push_back(startNode);
    while (!not_visited_node.empty() && current != endNode)
    {
        not_visited_node.sort([]( Node* lhs,  Node* rhs){ return lhs->get_local_goal() < rhs->get_local_goal(); } );
        while(!not_visited_node.empty() && not_visited_node.front()->get_is_visited())
        {
            not_visited_node.pop_front();
        }
        if(not_visited_node.empty())
        {
            break;
        }
        current = not_visited_node.front();
        current->set_visited(true);
        for(auto neigbour : current->get_neighbours_list())
        {
            if(!neigbour->get_is_visited() && !neigbour->get_is_obstacle())
            {
                not_visited_node.push_back(neigbour);
            }
            float lowest = current->get_local_goal() + distance(current, neigbour);
            if(lowest < neigbour->get_local_goal()) {
                neigbour->set_parent(current);
                neigbour->set_local_goal(lowest);
                neigbour->set_global_goal(neigbour->get_local_goal() + distance(neigbour, endNode));
            }
        }
    }
    if(endNode != nullptr)
    {
        Node *parent = endNode;
        while(parent->get_parent() != nullptr) {
            parent->update_is_path();
            parent = parent->get_parent();
        }
    }
}

bool PathFinder::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch(keyEvent->key())
        {
        case Qt::Key_S:
        {
            qDebug() << "Pressed S";
            was_E_pressed = false;
            was_S_pressed = true;
            break;
        }
        case Qt::Key_E:
        {
            qDebug() << "Pressed E";
            was_S_pressed= false;
            was_E_pressed = true;
            break;
        }
        }
        return true;
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
        Node *item = dynamic_cast<Node*>(scene->itemAt(QPointF(keyEvent->x(), keyEvent->y()), QTransform()));
        if (item != nullptr) {
            Node *clickedNode = graph[get_node_index(item->get_y(), item->get_x())];
            if(was_E_pressed) {
                if (endNode != nullptr)
                {
                    endNode->mark_as_end(false);
                }
                endNode = clickedNode;
                endNode->mark_as_end(true);
            } else if (was_S_pressed) {
                if (startNode != nullptr)
                {
                    startNode->mark_as_start(false);
                }
                startNode = clickedNode;
                startNode->mark_as_start(true);
            }
            was_E_pressed = false;
            was_S_pressed = false;
        }
        return true;
    }
    return QObject::eventFilter(watched, event);
}
