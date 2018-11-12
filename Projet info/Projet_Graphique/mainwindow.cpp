#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <typeinfo>
#include <string>
#include "Plain.h"


MainWindow::MainWindow(QWidget *parent, Game* game) : QMainWindow(parent), ui(new Ui::MainWindow){
    this->army[0] = army[0];
    this->game = game;
    ui->setupUi(this);
    //connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    this->army = game->getArmy();
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
    for(unsigned int i = 0; i<army->size(); i++){
        //infantry move

        if(army->at(i)->isMovable() && !army->at(i)->getDead()){
            showMove(army->at(i));

        }
    }

    for(unsigned int i = 0; i<army->size(); i++){
        if(!army->at(i)->getDead()){
            QRectF target(( army->at(i)->getX())*width()/x, (army->at(i)->getY())*height()/y, width()/x, height()/y);
            QRectF source(getXIm(army->at(i)->getID()), getYIm(army->at(i)->getID()), 16, 16);
            if(army->at(i)->getTeam() == game->getPlayer1()){
                QImage image("../advance wars sprites/Orange_Star");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(army->at(i)->getHealth())));
            }else {
                QImage image("../advance wars sprites/Blue_Moon");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(army->at(i)->getHealth())));
            }


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
    switch(event->key()){
    case Qt::Key_P: {
        game->endTurn();
        break;
    }

    case Qt::Key_Space: {
        this->close();
        break;
    }
    }
    update();
}

void MainWindow::unitMove(QMouseEvent *event){
    for(unsigned int i = 0; i<army->size(); i++){
        if(army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead() && army->at(i)->getTeam() == game->getActive()){
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

        if(army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead() && army->at(i)->getTeam() == game->getActive()){

            if(army->at(i)->isMovable()){
                int amtMove = army->at(i)->getMP();
                int wx = width()/x;
                int hy = height()/y;
                if(std::abs(floor(event->x()/wx - army->at(i)->getX())) + std::abs(floor(event->y()/hy) - army->at(i)->getY()) <= amtMove && std::abs(floor(event->x()/wx - army->at(i)->getX())) + std::abs(floor(event->y()/hy) - army->at(i)->getY()) > 0){
                    std::cout << floor(event->x()/wx) << "," << floor(event->y()/hy) << std::endl;

                    army->at(i)->setX(floor(event->x()/wx));
                    army->at(i)->setY(floor(event->y()/hy));

                    game->checkFusion(army->at(i));
                    army->at(i)->setMovable(false);
                    game->setActiveUnit(nullptr);


               }
            }
        }
    }
}

void MainWindow::showMove(Unit* unit){
    int amtMove = unit->getMP();
    QPainter painter(this);
    for(int i = -amtMove; i<=amtMove; i++){
        for(int j = -amtMove; j<=amtMove; j++){
            if(std::abs(i) + std::abs(j) <= amtMove){

                painter.fillRect((unit->getX()*width()/x) + (i*std::abs(width()/x)), (unit->getY()*height()/y) + (j*std::abs(height()/y)), width()/x, height()/y, QBrush(QColor(230, 128, 128, 128)));

            }
        }

    }
}

void MainWindow::showMenu(Building b, Unit u){
    QRectF target(11*this->width()/18, this->height()/12, this->width()/5,this->height()/3);
    QRectF source(0,0,41,62);
    QImage image("../advance wars sprites/menu");
    QPainter painter(this);
    painter.drawImage(target, image, source);

}

void MainWindow::tick(){
    update();
}

int MainWindow::getXIm(int ID){
    switch(ID){
    case 0:{
        return 21;
    }
    case 1:{
        return 21;
    }
    case 2:{
        return 40;
    }
    case 3:{
        return 59;
    }
    case 4:{
        return 55;
    }
    case 5:{
        return 40;
    }
    case 6:{
        return 36;
    }
    case 7:{
        return 40;
    }
    case 8:{
        return 3;
    }
    case 9:{
        return 20;
    }
    case 10:{
        return 76;
    }
    default: {
        return 21;
    }
    }
}

int MainWindow::getYIm(int ID){
    switch(ID){
    case 0:{
        return 73;
    }
    case 1:{
        return 113;
    }
    case 2:{
        return 113;
    }
    case 3:{
        return 113;
    }
    case 4:{
        return 36;
    }
    case 5:{
        return 74;
    }
    case 6:{
        return 35;
    }
    case 7:{
        return 74;
    }
    case 8:{
        return 73;
    }
    case 9:{
        return 37;
    }
    case 10:{
        return 58;
    }
    default: {
        return 73;
    }
    }
}
