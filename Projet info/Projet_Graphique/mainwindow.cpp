#include "mainwindow.h"
#include <QMediaPlayer>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <string>
#include "Plain.h"



MainWindow::MainWindow(QWidget *parent, Game* game) : QMainWindow(parent), ui(new Ui::MainWindow){
    this->army[0] = army[0];
    this->game = game;
    ui->setupUi(this);
    this->army = game->getArmy();
    music();

    server = new QTcpServer();

    if(! server->listen(QHostAddress::Any, 8123)) {
        std::cout << "I am a client" << std::endl;
        other = new QTcpSocket();
        connect(other, SIGNAL(connected()), this, SLOT(onConnected()));
        other->connectToHost("127.0.0.1", 8123);
        connect(other, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    } else {
        std::cout << "I am the server" << std::endl;
        other = nullptr;
    }
    
    std::cout << server->nextPendingConnection() << std::endl;
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));


}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::onNewConnection() {
    std::cout << "A new client is connecting !" << std::endl;
    other = server->nextPendingConnection();
    connect(other, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(other, SIGNAL(readyRead()), this, SLOT(onData()));


    QJsonObject info;
    for(unsigned int i = 0; i<army->size(); i++){
        posX = army->at(i)->getX();
        posY = army->at(i)->getY();
        info["x"] = posX;
        info["y"] = posY;
    }


    isConfigured = true;
    myTurn = false;

    sendJson(info);
    update();
    }

void MainWindow::onConnected() {
    std::cout << "I am connected" << std::endl;
    connect(other, SIGNAL(readyRead()), this, SLOT(onData()));
}

void MainWindow::onDisconnected() {
    std::cout << "The other guy just disconnected" << std::endl;
}

void MainWindow::onData() {
    std::cout << "Some data !" << std::endl;
    if(currentSize == 0) {
            if(other->bytesAvailable() < 4)
                return;
             QDataStream in(other);
            in >> currentSize;
        }
         if(other->bytesAvailable() < currentSize)
            return;

    QByteArray data = other->read(currentSize);
    std::cout << data.toStdString() << std::endl;
    currentSize = 0;

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();


    for(unsigned int i = 0; i<army->size(); i++){
        if(! isConfigured) {
            posY = json["y"].toInt();
            posX = json["x"].toInt();
            update();
            isConfigured = true;
            myTurn = true;
            } else {
            int oldX = json["oldX"].toInt();
            int oldY = json["oldY"].toInt();
            int newX = json["newX"].toInt();
            int newY = json["newY"].toInt();
            posX = newX;
            posY = newY;
            army->at(i)->setX(posX);
            army->at(i)->setY(posY);
            myTurn = true;
        }




        update();
    }
}


void MainWindow::sendJson(QJsonObject obj) {
    QByteArray data = QJsonDocument(obj).toJson();
    QDataStream out(other);
    out << (quint32) data.length();
    other->write(data);
     std::cout << "Sending " << data.toStdString() << std::endl;
}


void MainWindow::paintEvent(QPaintEvent *event){


    //map

    for(unsigned int j = 0; j<y; j++){
        for(unsigned int i = 0; i<x; i++){
            t[j][i] = game->getMap().getValue(j, i);
        }
    }


    for(unsigned int j = 0; j<x; j++){
        for(unsigned int i = 0; i<y; i++){
            QRectF target(j*width()/x, i*height()/y, width()/x, height()/y);
            QRectF source((t[i][j]-1)*16, 15, 16, 16);
            QImage image(":/sprt/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
            painter.setPen(QPen(Qt::white));
            painter.setFont(QFont("Times", 20, QFont::Bold));
            painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(game->getMap().getTile(j,i).getMoved("tr"))));
        }
    }
    for(unsigned int u = 0; u < game->getBuildings().size(); u++){
        if(game->getBuildings().at(u).getTeam() == game->getPlayer2()){
            QRectF target(game->getBuildings().at(u).getX()*width()/x, game->getBuildings().at(u).getY()*height()/y, width()/x, height()/y);
            QRectF source((t[game->getBuildings().at(u).getY()][game->getBuildings().at(u).getX()]+3)*16, 15, 16, 16);
            QImage image(":/sprt/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }else if(game->getBuildings().at(u).getTeam() == game->getPlayer1()){
            QRectF target(game->getBuildings().at(u).getX()*width()/x, game->getBuildings().at(u).getY()*height()/y, width()/x, height()/y);
            QRectF source((t[game->getBuildings().at(u).getY()][game->getBuildings().at(u).getX()]+8)*16, 15, 16, 16);
            QImage image(":/sprt/advance wars sprites/tileset projet");
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
            QRectF target( army->at(i)->getX()*width()/x, army->at(i)->getY()*height()/y, width()/x, height()/y);
            QRectF source(getXIm(army->at(i)->getID()), getYIm(army->at(i)->getID()), 16, 16);
            if(army->at(i)->getTeam() == game->getPlayer1()){
                QImage image(":/sprt/advance wars sprites/Orange_Star");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(army->at(i)->getHealth())));
            }else {
                QImage image(":/sprt/advance wars sprites/Blue_Moon");
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
        //if(game->checkBuildings(army->at(i)) != nullptr){
            showMenu(game->checkBuildings(army->at(i)->getX(),army->at(i)->getY()),army->at(i));
        //}



    //test réseau

    QPainter painter(this);
//    painter.fillRect(posX, posY, 20, 40, Qt::red);
    painter.drawText(10, 250, QString("myTurn: ") + (myTurn ? "true" : "false"));


    }
}



void MainWindow::mousePressEvent(QMouseEvent *event){

    createUnit(event);

    //réseau
    if(! myTurn)
           return;

    sendJson(unitMove(event));
    update();

    for(unsigned int i = 0; i<army->size(); i++){
        if(!army->at(i)->isMovable()){
            myTurn = false;
        }
    }

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

QJsonObject MainWindow::unitMove(QMouseEvent *event){

    QJsonObject move;

    for(unsigned int i = 0; i<army->size(); i++){


        if(army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead()){
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

        int oldX = army->at(i)->getX();
        int oldY = army->at(i)->getY();

        move["oldX"] = oldX;
        move["oldY"] = oldY;

        if(army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead()){

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
        move["newX"] = army->at(i)->getX();
        move["newY"] = army->at(i)->getY();
    }

    return move;
}


void MainWindow::showMove(Unit* unit){
    /*
     *Legacy
     *
     * int amtMove = unit->getMP();
     * QPainter painter(this);
     * for(int i = -amtMove; i<=amtMove; i++){
     *    for(int j = -amtMove; j<=amtMove; j++){
     *        if(std::abs(i) + std::abs(j) <= amtMove){
     *          painter.fillRect((unit->getX()*width()/x) + (i*std::abs(width()/x)), (unit->getY()*height()/y) + (j*std::abs(height()/y)), width()/x, height()/y, QBrush(QColor(230, 128, 128, 128)));
     *          }
     *      }
     *  }*/

    moveUnit(unit, unit->getX(), unit->getY(), unit->getMP());
    QPainter painter(this);
    for(unsigned int i = 0; i<cases.size(); i++){
        painter.fillRect(cases.at(i).first*width()/x, cases.at(i).second*height()/y, width()/x, height()/y, QBrush(QColor(230, 128, 128, 128)));
    }
    cases.clear();
}

void MainWindow::showMenu(Building* b, Unit* u){
    if(b != nullptr){

        QRectF target(11*this->width()/18, this->height()/12, this->width()/5,this->height()/3);
        QRectF source(0,0,41,62);
        QImage image(":/sprt/advance wars sprites/menu");
        QPainter painter(this);
        painter.drawImage(target, image, source);
    }

    if(this->game->ennemyNear(u)){
        std::cout << "combat" << std::endl;
        QRectF target(11*this->width()/18, this->height()/12, this->width()/5,this->height()/3);
        QRectF source(0,42,41,62);
        QImage image(":/sprt/advance wars sprites/menu");
        QPainter painter(this);
        painter.drawImage(target, image, source);
    }

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
        return 143;
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
        return 47;
    }
    }
}

void MainWindow::moveUnit(Unit* unit, int x, int y, int MP)
{
    int i = 0;
    int j = 1;
    IntPair pos = std::make_pair(x+i,y+j);
    MP -= game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());

    bool present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }

    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);

        moveUnit(unit, x+i, y+j, MP);
    }

    MP += game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());;
    i = 0;
    j = -1;

    pos = std::make_pair(x+i,y+j);
    MP -= game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }
    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }

    MP += game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());;
    i = 1;
    j = 0;
    pos = std::make_pair(x+i,y+j);
    MP -= game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }
    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }

    MP += game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());;
    i = -1;
    j = 0;

    pos = std::make_pair(x+i,y+j);
    MP -= game->getMap().getTile(x+i, y+j).getMoved(unit->getMT());
    present = false;
    for(unsigned int u = 0; u<cases.size(); u++){
        if(pos.first == cases.at(u).first && pos.second == cases.at(u).second){
            present = true;
            if( depl.at(u) < MP){
                cases.erase(cases.begin()+u);
                present = false;
            }
        }
    }
    if(MP >= 0 && !present){
        cases.push_back(pos);
        depl.push_back(MP);
        moveUnit(unit, x+i, y+j, MP);
    }
}

QJsonObject MainWindow::createUnit(QMouseEvent* event){
    for(unsigned int i=0; i<game->getBuildings().size();i++){
        if(game->checkBuildings(event->x(),event->y()) != nullptr ){
          QMessageBox::information(this, "Test", "Ceci est un bâtiment");
        }
    }


}

void MainWindow::music(){
    QMediaPlayer* mus = new QMediaPlayer;
    mus->setMedia(QUrl::fromLocalFile(QFileInfo("../advance wars sprites/take.mp3").absoluteFilePath()));
    mus->setVolume(50);
    mus->play();
}
