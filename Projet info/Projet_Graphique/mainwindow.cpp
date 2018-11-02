#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <typeinfo>
#include "Plain.h"


MainWindow::MainWindow(QWidget *parent, Game* game) : QMainWindow(parent), ui(new Ui::MainWindow){
    this->army[0] = army[0];
    this->game = game;
    ui->setupUi(this);
    //connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
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


    for(unsigned int j = 0; j<y; j++){
        for(unsigned int i = 0; i<x; i++){
            QRectF target(i*width()/x, j*height()/y, width()/x, height()/y);
            QRectF source((t[j][i]-1)*16, 15, 16, 16);
            QImage image("../advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }
    }

    //infantry
    for(int i = 0; i<army->size(); i++){
        QRectF target(( army->at(i)->getX())*width()/x, (army->at(i)->getY())*height()/y, width()/x, height()/y);
        QRectF source(0, 0, 16, 16);
        QImage image("../advance wars sprites/player");
        QPainter painter(this);
        painter.drawImage(target, image, source);

        //infantry move

        if(army->at(i)->isMovable()){
            showMove(i);
        }
    }


    // infantry action
    for(int i = 0; i<army->size(); i++){
        if(game->check(army->at(i)) != nullptr){
           //showMenu(*game->check(army->at(i)),*army->at(i));
            QRectF target(11*this->width()/18, this->height()/12, this->width()/4,this->height()/4);
            //QRectF source(865, 1446, 42, 63);
            //QImage image("../Projet info/advance wars sprites/all sprites");
            QRectF source(0,0,41,62);
            QImage image("../Gaspard/Desktop/github/Qt-projet/Projet info/advance wars sprites/menu");
            QPainter painter(this);
            painter.drawImage(target, image, source);
            painter.fillRect(0,0, this->width()/4,this->height()/4,Qt::red);
        }
      }
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    for(int i = 0; i<army->size(); i++){
        if(!army->at(i)->isMovable() && game->getActiveUnit() == nullptr){
            if(event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x) &&
                    event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                army->at(i)->setMovable(true);
                game->setActiveUnit(army->at(i));
            }


        }else if(army->at(i)->isMovable() && game->getActiveUnit() == army->at(i)){
            if(event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x) &&
                    event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                game->setActiveUnit(nullptr);
                army->at(i)->setMovable(false);
            }

        }

        //droite
        if(army->at(i)->isMovable()){
            if(event->x() > (army->at(i)->getX()*this->width()/x+ this->width()/x) && event->x() < (army->at(i)->getX()*this->width()/x + 2*this->width()/x) &&
                    event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                        army->at(i)->setX(army->at(i)->getX()+1);
                        army->at(i)->setMovable(false);
                        game->setActiveUnit(nullptr);
            }
        }

        //gauche
        if(army->at(i)->isMovable()){
            if(event->x() < (army->at(i)->getX()*this->width()/x) && event->x() > (army->at(i)->getX()*this->width()/x - 1*this->width()/x) &&
                    event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                        army->at(i)->setX(army->at(i)->getX()-1);
                        army->at(i)->setMovable(false);
                        game->setActiveUnit(nullptr);
            }
        }

        //bas
        if(army->at(i)->isMovable()){
            if(event->y() > (army->at(i)->getY()*this->height()/y+ this->height()/y) && event->y() < (army->at(i)->getY()*this->height()/y + 2*this->height()/y) &&
                    event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x)){
                        army->at(i)->setY(army->at(i)->getY()+1);
                        army->at(i)->setMovable(false);
                        game->setActiveUnit(nullptr);
            }
        }

        //haut
        if(army->at(i)->isMovable()){
            if(event->y() < (army->at(i)->getY()*this->height()/y) && event->y() > (army->at(i)->getY()*this->height()/y - 1*this->height()/y) &&
                    event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x)){
                        army->at(i)->setY(army->at(i)->getY()-1);
                        army->at(i)->setMovable(false);
                        game->setActiveUnit(nullptr);
            }
        }

    }
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
}

void MainWindow::showMove(int i)
{
    QPainter painter(this);
    painter.fillRect(army->at(i)->getX()*this->width()/x+this->width()/x, army->at(i)->getY()*this->height()/y, this->width()/x, this->height()/y, Qt::red);
    painter.fillRect(army->at(i)->getX()*this->width()/x-this->width()/x, army->at(i)->getY()*this->height()/y, this->width()/x, this->height()/y, Qt::red);
    painter.fillRect(army->at(i)->getX()*this->width()/x, army->at(i)->getY()*this->height()/y+this->height()/y, this->width()/x, this->height()/y, Qt::red);
    painter.fillRect(army->at(i)->getX()*this->width()/x, army->at(i)->getY()*this->height()/y-this->height()/y, this->width()/x, this->height()/y, Qt::red);

}

void MainWindow::showMenu(Building b, Unit u){
    std::cout << "menu" << std::endl;
    //QRectF target(11/18*this->width(), 1/12*this->height(), 1/3*this->width(),1/3*this->height());
    QRectF target(0,0, this->width(),this->height());
    QRectF source(865, 1446, 42, 63);
    QImage image("../advance wars sprites/all sprites");
    QPainter painter(this);
    painter.drawImage(target, image, source);

}

void MainWindow::tick(){
    update();
}


