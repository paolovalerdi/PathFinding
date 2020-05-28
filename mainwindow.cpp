#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SQUARE_HEIGHT 40
#define MAP_SIZE 600

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 600);
    this->setCentralWidget(ui->graphicsView);

    path_finder = new PathFinder(MAP_SIZE, SQUARE_HEIGHT, 5);
    ui->graphicsView->setScene(path_finder->get_scene());
}

MainWindow::~MainWindow()
{
    delete ui;
}
