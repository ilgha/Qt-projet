#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
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
            QRectF target(i*this->width()/x, j*this->height()/y, this->width()/x, this->height()/y);
            QRectF source((t[j][i]-1)*16, 15, 16, 16);
            QImage image("C:/Users/Gaspard/Desktop/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }
    }

    //player

    QRectF target(8*this->width()/x, 3*this->height()/y, this->width()/x, this->height()/y);
    QRectF source(0, 0, 16, 16);
    QImage image("C:/Users/Gaspard/Desktop/advance wars sprites/player");
    QPainter painter(this);
    painter.drawImage(target, image, source);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPainter painter(this);
    painter.fillRect(0,0,this->width()/x, this->height()/y,Qt::blue);
    std::cout << event->x() << "," << event->y() << std::endl;

    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
}

void MainWindow::tick(){
    std::cout << this->width() << "," << this->height() << a << std::endl;


    update();
}


