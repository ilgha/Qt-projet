#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent, Player* player, Game* game) : QMainWindow(parent), ui(new Ui::MainWindow){
    this->player = player;
    this->game = game;
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    this->army = game->getArmy();
    //timer.start(10);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::paintEvent(QPaintEvent *event){

    //map

    int t[12][18] = {{1,1,1,1,1,1,1,1,44,1,44,1,1,1,1,1,34,3},
                     {1,1,15,15,15,15,15,15,15,47,1,43,1,1,1,1,1,34},
                     {1,1,1,1,34,35,34,1,34,1,43,1,1,1,1,1,34,1},
                     {35,1,1,2,1,1,1,3,1,43,1,1,3,34,1,35,1,2},
                     {34,1,1,34,2,1,3,1,1,3,1,1,1,1,3,1,1,1},
                     {1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1},
                     {28,35,1,1,1,1,1,1,1,3,2,1,3,1,1,34,1,34},
                     {28,28,27,28,28,28,28,3,28,3,3,3,1,1,1,1,1,1},
                     {1,1,1,1,1,35,28,28,28,28,3,3,1,1,34,1,35,1},
                     {1,1,1,1,1,34,1,26,1,1,2,1,34,1,34,1,1,1},
                     {1,1,1,1,1,1,1,34,28,28,1,1,1,1,34,1,3,1},
                     {1,1,1,1,1,1,34,28,28,3,3,1,3,34,1,3,34,3}};


    for(int j = 0; j<y; j++){
        for(int i = 0; i<x; i++){
            QRectF target(i*width()/x, j*height()/y, width()/x, height()/y);
            QRectF source((t[j][i]-1)*16, 15, 16, 16);
            QImage image("C:/Users/Gaspard/Desktop/github/Qt-projet/Projet info/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }
    }

    //infantry
    QRectF target(( army[0].getX())*width()/x, (army[0].getY())*height()/y, width()/x, height()/y);
    QRectF source(0, 0, 16, 16);
    QImage image("C:/Users/Gaspard/Desktop/github/Qt-projet/Projet info/advance wars sprites/player");
    QPainter painter(this);
    painter.drawImage(target, image, source);
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    std::cout << event->x() << "," << event->y() << std::endl;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
}

void MainWindow::tick(){
    std::cout << width() << "," << height() << a << std::endl;


    update();
}


