#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QPen>
#include <QDebug>
#include <iostream>
#include <mysquare.h>

#define SQUARE_HEIGHT 40
#define MAP_SIZE 600

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600,600);
    this->setCentralWidget(ui->graphicsView);

    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    // Create every node.
    int graphSize = MAP_SIZE / SQUARE_HEIGHT;
    graph = new Node*[graphSize * graphSize];
    for (int x = 0; x < MAP_SIZE; x += SQUARE_HEIGHT)
    {
        for (int y = 0; y < MAP_SIZE; y += SQUARE_HEIGHT)
        {
            int node_index = (y * graphSize + x) / SQUARE_HEIGHT;
            qDebug() << "Current node at: (" << x << "," << y << ") ->" << "[" << node_index << "]";
            qDebug() << "With neigbours at:";
            if (x > 0)
            {
                int neighbour_x = x - SQUARE_HEIGHT;
                int neigbour_index = (y * graphSize + (neighbour_x)) / SQUARE_HEIGHT;
                qDebug() << "LEFT: (" << x - SQUARE_HEIGHT << "," << y<< ")->[" << neigbour_index << "]";
            }
            if (y > 0)
            {
                qDebug() << "TOP: (" << x << "," << y  - SQUARE_HEIGHT << ")";
            }
            if (x < MAP_SIZE - SQUARE_HEIGHT)
            {
                qDebug() << "RIGHT: (" << x + SQUARE_HEIGHT<< "," << y << ")";
            }
            if (y < MAP_SIZE - SQUARE_HEIGHT)
            {
                qDebug() << "BOTTOM: (" << x << "," << y  + SQUARE_HEIGHT << ")";
            }
            //graph[node_index] = new Node(x, y, 5, SQUARE_HEIGHT);
            //qDebug() << "(" << x << "," << y << ") ->" << "[" << (x * 15 + y) / SQUARE_HEIGHT << "]";
            //scene->addRect(x + 5, y + 5, SQUARE_HEIGHT - 10, SQUARE_HEIGHT - 10, QPen(Qt::blue), QBrush(Qt::blue));
            //scene->addItem(graph[node_index]);
            qDebug() << "##############################";
        }
    }
    /*for (int x = 0; x < MAP_SIZE; x += SQUARE_HEIGHT)
    {
        QPen pen = QPen(QColor(70, 71, 84));
        pen.setWidthF(2);
        QLineF line = QLineF(x + (SQUARE_HEIGHT / 2), 6, x + (SQUARE_HEIGHT / 2), MAP_SIZE - 5);
        scene->addLine(line, pen);
    }

    for (int y = 0; y < MAP_SIZE; y += SQUARE_HEIGHT)
    {
        QPen pen = QPen(QColor(70, 71, 84));
        pen.setWidthF(2);
        QLineF line = QLineF(6, y + (SQUARE_HEIGHT / 2), MAP_SIZE - 5, y + (SQUARE_HEIGHT / 2));
        scene->addLine(line, pen);
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
