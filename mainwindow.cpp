#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SQUARE_HEIGHT 30
#define MAP_SIZE 600

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // this->setCentralWidget(ui->graphicsView);

    path_finder = new PathFinder(this, MAP_SIZE, SQUARE_HEIGHT, 5);
    this->installEventFilter(path_finder);

    ui->graphicsView->setScene(path_finder->get_scene());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    path_finder->solve();
}
