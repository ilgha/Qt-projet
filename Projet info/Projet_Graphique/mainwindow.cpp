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
            QImage image("../Projet info/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }
    }

    //infantry
    for(unsigned int i = 0; i<army->size(); i++){
        QRectF target(( army->at(i)->getX())*width()/x, (army->at(i)->getY())*height()/y, width()/x, height()/y);
        QRectF source(0, 0, 16, 16);
        QImage image("../Projet info/advance wars sprites/player");
        QPainter painter(this);
        painter.drawImage(target, image, source);

        //infantry move
        if(army->at(i)->isMovable()){
            showMove(i);
        }
    }


    // infantry action To set in a separated function
    for(unsigned int i = 0; i<army->size(); i++){
        if(game->check(army->at(i)) != nullptr){
            showMenu(*game->check(army->at(i)),*army->at(i));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    unitMove(event);
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
    for(unsigned int i = 0; i<army->size(); i++){
        if(game->check(army->at(i)) != nullptr){

        }
      }
}

void MainWindow::unitMove(QMouseEvent *event){
    for(unsigned int i = 0; i<army->size(); i++){
        if(army->at(i)->getTeam() == game->getActive()){
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
        }
    }

    for(unsigned int i = 0; i<army->size(); i++){
        if(army->at(i)->getTeam() == game->getActive()){
            //droite
            if(army->at(i)->isMovable()){
                if(event->x() > (army->at(i)->getX()*this->width()/x+ this->width()/x) && event->x() < (army->at(i)->getX()*this->width()/x + 2*this->width()/x) &&
                        event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                            army->at(i)->setX(army->at(i)->getX()+1);
                            game->checkFusion(army->at(i));
                            army->at(i)->setMovable(false);
                            game->setActiveUnit(nullptr);
                            std::cout<<army->at(i)->getHealth()<<std::endl;
                            std::cout<<i<<std::endl;
                }
                //gauche
                else if(event->x() < (army->at(i)->getX()*this->width()/x) && event->x() > (army->at(i)->getX()*this->width()/x - 1*this->width()/x) &&
                        event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                            army->at(i)->setX(army->at(i)->getX()-1);
                            game->checkFusion(army->at(i));
                            army->at(i)->setMovable(false);
                            game->setActiveUnit(nullptr);
                            std::cout<<army->at(i)->getHealth()<<std::endl;
                            std::cout<<i<<std::endl;
                }
                //bas
                else if(event->y() > (army->at(i)->getY()*this->height()/y+ this->height()/y) && event->y() < (army->at(i)->getY()*this->height()/y + 2*this->height()/y) &&
                        event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x)){
                            army->at(i)->setY(army->at(i)->getY()+1);
                            game->checkFusion(army->at(i));
                            army->at(i)->setMovable(false);
                            game->setActiveUnit(nullptr);
                            std::cout<<army->at(i)->getHealth()<<std::endl;
                            std::cout<<i<<std::endl;
                }
                //haut
                if(event->y() < (army->at(i)->getY()*this->height()/y) && event->y() > (army->at(i)->getY()*this->height()/y - 1*this->height()/y) &&
                        event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x)){
                            army->at(i)->setY(army->at(i)->getY()-1);
                            game->checkFusion(army->at(i));
                            army->at(i)->setMovable(false);
                            game->setActiveUnit(nullptr);
                            std::cout<<army->at(i)->getHealth()<<std::endl;
                            std::cout<<i<<std::endl;
                }
            }
        }
    }
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
    QRectF target(11*this->width()/18, this->height()/12, this->width()/5,this->height()/3);
    QRectF source(0,0,41,62);
    QImage image("C:/Users/Gaspard/Desktop/github/Qt-projet/Projet info/advance wars sprites/menu");
    QPainter painter(this);
    painter.drawImage(target, image, source);

}

void MainWindow::tick(){
    update();
}


